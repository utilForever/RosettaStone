# Reinforcement learning with RosettaRL

RosettaRL trains a policy-value model on PlayMode observations using Monte Carlo tree search (MCTS) visit distributions and final game outcomes. Run the commands below from the repository root after setting up the [Quick Start prerequisites](../README.md#prerequisites).

## Build with LibTorch

`BUILD_RL` and `BUILD_RL_PYTHON` default to `OFF`. The core simulator and `pyRosetta` do not require LibTorch. To build the shared policy-value model and its tests, provide an existing [LibTorch installation](https://docs.pytorch.org/cppdocs/installing.html).

```bash
cmake -S . -B build/rl \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
  -DBUILD_RL=ON \
  -DCMAKE_PREFIX_PATH=/absolute/path/to/libtorch
cmake --build build/rl --config Release --target RosettaRL RosettaRLTests
ctest --test-dir build/rl -C Release -R '^RosettaRL(Tests|TrainCLI)?$' --output-on-failure
```

Alternatively, set `Torch_DIR` to `/absolute/path/to/libtorch/share/cmake/Torch`. Use a LibTorch build compatible with your compiler and C++ ABI. On Windows,
match Debug or Release with the LibTorch distribution; the RL targets copy their runtime DLLs beside the executables. On Linux, use the C++11 ABI distribution
with the default GCC ABI. A CPU-only distribution is sufficient; CMake does not download LibTorch or configure CUDA for you.

Torch headers, compiler options, and libraries are confined to `Extensions/RosettaRL`. `RosettaRLModel` provides the C++ model and trainer. Running `RosettaRL` without arguments runs the CPU tensor smoke test. `RosettaRLTests` checks observation packing, batched outputs, value bounds, gradients, seeded initialization, native archives, tiny-batch training, and device moves (CUDA checks run only when available).

## Policy-value model

`RosettaStone::RL::PolicyValueNetwork` is defined once as a `torch::nn::Module` in `<RosettaRL/PolicyValueNetwork.hpp>`. `EncodeObservationBatch` copies a span of [observation v1](ObservationSchema.md) records into an owning CPU `int32[B,444]` tensor, including `schemaVersion`, in canonical member/row-major order. `forward` accepts that tensor on the model's device and rejects incorrect shapes, dtypes, or versions. Empty batches are supported. Inputs must come from the observation encoder; the model does not revalidate game-state semantics.

The fixed MVP architecture applies `sign(x) * log1p(abs(x))` in float32, then converts the normalized features to the parameter dtype. This keeps large IDs and flags from dominating and avoids overflow with float16 parameters. A shared `Linear(444,128)` + ReLU feeds two registered linear heads. IDs and flags remain scalar features for this fixed-deck baseline. Outputs are a pair of unmasked [policy v1](PolicyActions.md) logits `[B,4846]` and tanh values `[B]` in `[-1,1]`, relative to the observation's acting player (`+1` win, `0` draw, `-1` loss). Both outputs are float32 by default. Apply legal-action masking and softmax outside the model; `BatchedEvaluator` expects nonnegative weights, not logits.

Call `torch::manual_seed(seed)` before construction for reproducible CPU initialization. Fixed seeds reproduce parameters and outputs for the same CPU batch and LibTorch environment; cross-version or CPU/CUDA bitwise parity is not promised. Use normal `model->to(torch::kCUDA)` and move the input tensor to the same device. All layers participate in `parameters()` and native LibTorch archives.

## Native C++ training

`NativeTrainer` in `<RosettaRL/NativeTrainer.hpp>` updates the supplied model once per nonempty mini-batch. Pass the three tensors in replay row order.

| Tensor         | Shape and values for the default CPU model                                                                                                                                 |
| -------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Observations   | Raw `int32[B,444]` from `EncodeObservationBatch`                                                                                                                           |
| Policy targets | `float32[B,4846]` normalized MCTS visit probabilities in policy-index order. Each row sums to one within `1e-5`. The producer assigns zero probability to illegal actions. |
| Outcomes       | `float32[B]` final results from the acting player's perspective. Each entry must be +1 for a win, 0 for a draw or −1 for a loss.                                           |

The policy loss is mean cross-entropy against the visit distribution, using log-softmax over all 4,846 logits. The value loss is mean squared error. The total adds both losses and `1e-4 * sum(parameter²)` over every weight and bias. Each step uses plain SGD with learning rate `0.01` and zero momentum.

```cpp
using namespace RosettaStone::RL;
PolicyValueNetwork model;
NativeTrainer trainer(model);
const auto batch = EncodeObservationBatch(observations);
const auto result = trainer.TrainBatch(batch, policyTargets, outcomes);
trainer.SaveCheckpoint("weights.pt");
```

The CPU command reads one prepared mini-batch file per step, in argument order. Write each file with LibTorch's `torch::save(std::vector<torch::Tensor>{batch, policyTargets, outcomes}, "batch.pt")`.

```bash
./build/rl/bin/RosettaRL train weights.pt batch-1.pt batch-2.pt
```

The CLI starts a new `float32` model if the weights file is missing or resumes an existing `float32` checkpoint. To resume another dtype through the C++ API, call `model->to(dtype)` with the checkpoint's dtype, then `model->LoadWeights(path)` before constructing `NativeTrainer`.

When resuming through a symbolic link, the command loads and updates the target file and preserves the link. The command reports the run-local step count and pre-update policy, value and total losses. It writes the checkpoint once all supplied batches succeed. Plain SGD needs only those weights to reproduce the next update on the same batch.

## Shared model weights

Use `model->SaveWeights("weights.pt")` and `model->LoadWeights("weights.pt")` for weight exchange. Both operations live in the shared C++ model. C++ accepts `std::filesystem::path`; Python accepts Unicode strings, including Korean filenames and directories on Windows. The artifact is a LibTorch `OutputArchive` with these required attributes:

| Attribute             | Version 1 value                                              |
| --------------------- | ------------------------------------------------------------ |
| `format`              | String `RosettaStone.PolicyValueNetwork`                     |
| `artifact_version`    | Integer `1`                                                  |
| `model_version`       | Integer `1` (the fixed architecture and normalization above) |
| `observation_version` | Integer `1`                                                  |
| `policy_version`      | Integer `1`                                                  |
| `weights`             | Dictionary from parameter name to detached CPU tensor        |

The six tensor names/shapes are `shared.weight [128,444]`, `shared.bias [128]`, `policy.weight [4846,128]`, `policy.bias [4846]`, `value.weight [1,128]`, and `value.bias [1]`. Their original floating-point dtypes are preserved. Set the destination model to the same dtype before loading; dtype conversion is deliberately explicit. Saved device placement is always CPU, so the file can move between CPU and CUDA runtimes.

Loading checks metadata, the complete parameter set, shapes, dtypes, dense layouts, and finite values before changing any parameter. Device transfers and allocations finish before parameter storage is replaced. A failed load preserves the active weights and outputs; a successful load preserves parameter handles, device, dtype, inference state, and training/evaluation mode. Loading inside `torch.inference_mode()` leaves an existing trainable model trainable. Do not load concurrently with forward/backward or in the middle of an outstanding autograd graph. Optimizer/scheduler state, gradients, RNG state, and experiment data are not stored or restored. Native `torch::save(model, ...)` archives and Python `state_dict` files are not this versioned format. Use trusted artifacts and matching PyTorch/LibTorch installations; arbitrary future architectures and library-version migration are outside this contract.

## Python bindings

To expose the same model and weight operations to Python, opt into `BUILD_RL_PYTHON` using the installed PyTorch package as the LibTorch source (PyTorch and pytest must already be installed in the selected interpreter):

```bash
cmake -S . -B build/rl-python \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
  -DBUILD_RL=ON -DBUILD_RL_PYTHON=ON \
  -DPython_EXECUTABLE="$(python -c 'import sys; print(sys.executable)')" \
  -DCMAKE_PREFIX_PATH="$(python -c 'import torch; print(torch.utils.cmake_prefix_path)')"
cmake --build build/rl-python --config Release \
  --target RosettaRLTests pyRosettaRL RosettaRLWeightInterop
ctest --test-dir build/rl-python -C Release \
  -R '^RosettaRL(Tests|WeightInterop)$' --output-on-failure
```

Add the directory containing the built `pyRosettaRL` module to `PYTHONPATH` (`build/rl-python/lib` for a single-configuration build; append `Release` for a multi-configuration build). On Windows, use explicit paths for the interpreter and its Torch CMake prefix. The optional binding uses PyTorch's C++ module wrapper, so the model is a `torch.nn.Module` backed by the same C++ parameters and forward implementation:

```python
import torch
from pyRosettaRL import PolicyValueNetwork

model = PolicyValueNetwork()
model.load_weights("weights.pt")
batch = torch.zeros((2, 444), dtype=torch.int32)
batch[:, 0] = 1  # Observation schema version; real batches use the encoder.
logits, values = model(batch)
model.save_weights("python-weights.pt")
```

The cross-runtime test saves in a separate native C++ process, loads and changes weights through Python, then loads the Python result in C++. Fixed CPU batch outputs are compared with `rtol=1e-5, atol=1e-6`. Corrupt, incomplete, and incompatible artifact tests also check that rejected loads leave every parameter unchanged.
