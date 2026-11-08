# MVP policy actions, version 1

`Includes/Rosetta/PlayMode/Actions/PolicyActions.hpp` implements the policy contract for [#1065](https://github.com/utilForever/RosettaStone/issues/1065). `PolicyActions(game)` snapshots `EnumerateActions(game)` once, maps its semantic values to fixed player-relative indices, and provides a binary legal-action mask. It does not execute tasks, advance the game, or consume randomness.

## API and lifetime

```cpp
const PolicyActions policy(game);
const auto& mask = policy.GetLegalMask();
const std::size_t index = policy.Encode(action);
const PlayerAction decoded = policy.Decode(index);
```

`Encode` accepts only an exact legal `PlayerAction`, including its unused-field sentinels. `Decode` accepts only an unmasked index and returns the original source ID, target ID, field position, Choose One option, and choice ID. Illegal actions, masked indices, and out-of-range indices throw `std::invalid_argument`.

The snapshot owns values and retains no game pointers. Rebuild it after any game mutation, including a change of acting player; an old snapshot still describes its original decision. Pass decoded actions through the existing task path or `ReplayGame::ApplyAction`, which checks current legality. Do not persist snapshot entity IDs as cross-game identifiers.

The mask is `std::array<std::uint8_t, 4846>`: `1` means legal, `0` means masked. Policy scores use the same index order. There is no default-enabled entry. If `EnumerateActions` returns no decisions (for example during mulligan, intermediate processing, or after game over), the mask is entirely zero and both conversions reject all inputs. Such a mask is not a playable model input; terminal outcomes remain in the replay API.

Python exposure is deferred alongside the game and observation APIs. The existing Python-visible `PlayerAction` value contract is unchanged. Future bindings must preserve these indices, mask values, errors, and round trips with parity tests.

## Fixed layout

Version 1 has **4,846 entries**, regardless of the number of legal actions. Indices are not ranks in the legal-action list and never depend on runtime entity ID ordering. Each block is dense and row-major, with the last axis varying fastest.

| Action         | Inclusive indices | Shape         | Index formula                                            |
| -------------- | ----------------- | ------------- | -------------------------------------------------------- |
| End turn       | 0                 | scalar        | `0`                                                      |
| Play card      | 1–4760            | `[10,17,7,4]` | `1 + ((hand * 17 + target) * 7 + position) * 4 + option` |
| Attack         | 4761–4824         | `[8,8]`       | `4761 + attacker * 8 + defender`                         |
| Hero power     | 4825–4841         | `[17]`        | `4825 + target`                                          |
| General choice | 4842–4845         | `[4]`         | `4842 + offer`                                           |

Slot meanings follow [observation schema v1](ObservationSchema.md):

- `hand`: actor hand slot `0..9`, in zone order. Duplicate card identities still have separate slots.
- `attacker` / `defender`: hero `0`, then board slots `1..7`. Attack sources belong to the actor and targets to the opponent. Heroes can attack with or without an equipped weapon; the weapon is not a separate source.
- `target`: `0` is no target; `1` is the actor's hero; `2..8` are actor board slots `0..6`; `9` is the opponent's hero; `10..16` are opponent board slots `0..6`. Missing slots remain masked.
- `position`: minion/location insertion position `0..6`. With at most six occupied board slots, these cover every legal placement; a full seven-slot board forbids another placement. Cards without placement use `0` here and retain `fieldPos=-1` in the semantic action. Their other position entries are masked.
- `option`: Choose One options `1..4` map to slots `0..3` in metadata order. Ordinary plays and Choose Both use slot `0` and retain semantic `chooseOne=0`. A given source in one decision cannot have both a default/Choose Both action and a Choose One action, so sharing slot `0` cannot merge legal actions. No unrequested option entries are enabled.
- `offer`: offered GENERAL choice order `0..3`, not sorted entity ID order. Equal card identities with distinct IDs remain distinct choices. If an ID is repeated in an offer list, only its first occurrence is enabled, matching the semantic enumerator's deduplication.

For example, index `1` plays hand slot 0 without a target at its first placement/default option. Index `5` uses the next insertion position. Index `4761` attacks the opposing hero with the actor's hero; `4834` uses the actor's hero power on the opposing hero. Untargeted hero powers use `4825`; an implicit target already resolved by the semantic enumerator is preserved.

The shared position and option slots avoid separate dimensions for mutually exclusive defaults. Action-specific blocks avoid allocating meaningless hand or placement axes to attacks, hero powers, and choices. No card-specific policy cases are needed. Legal actions are the only source of enabled entries; capacity overflow or a mapping collision throws rather than truncating or returning a partial mask.

## Supported boundary and versioning

`PolicySchema::VERSION=1` is paired with `PolicySchema::OBSERVATION_VERSION=1`. A compile-time assertion requires the declared observation version to match `ObservationSchema::VERSION`. Persist both version numbers and the pinned card-data version with model weights and datasets. The policy constants specify logical indices; C++ object bytes and the platform width of `std::size_t` are not a serialization format.

The layout covers Phase 1 card plays, attacks, hero powers, and single offered GENERAL choices. It preserves Phase 1 location placement and targeting, although observation v1 rejects visible locations. Likewise, representing a GENERAL choice does not establish that its context is supported by observation v1. A combined MVP input must successfully encode both the observation and the policy; this action mapper does not widen the observation contract.

The expansion ceiling is ten actor hand cards, seven board entities per player, four Choose One metadata options per hand card, and four offered choices. Unsupported capacities throw `std::invalid_argument`, including oversized hands/options whose excess entries are currently unplayable. Opponent hand identities, both decks, and hidden candidate pools are not inspected by the slot mapping. Legality remains the engine's responsibility through `EnumerateActions`.

Broader decks requiring more slots, additional target zones, multiple simultaneous selections, trading, location activation, or another semantic action type need a new policy version. Changing any index, axis order, slot meaning, mask dtype, or capacity also requires a version bump; consumers must not infer compatibility from vector length alone. Observation support for omitted mechanics/history must be revised separately before those decks become valid MVP inputs. Search behavior and a universal full-card-pool layout are outside this contract.

The [golden contract tests](ObservationSchema.md#golden-contract-tests) pin complete legal masks and readable slot-based actions alongside observations for six representative states and both absolute seats. Updating those expectations requires an explicit observation/policy schema-version decision.
