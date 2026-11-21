# Copyright (c) 2026 Chris Ohk

import os
import subprocess
import sys
from math import isclose
from pathlib import Path
from shutil import copyfile
from tempfile import TemporaryDirectory


def train(cli, checkpoint, *batches):
    output = subprocess.check_output(
        [cli, "train", checkpoint, *batches], cwd=checkpoint.parent, text=True
    )
    lines = output.splitlines()
    if len(lines) != len(batches):
        sys.exit(f"Expected {len(batches)} training steps, got {output!r}")

    fields = dict(field.split("=", 1) for field in lines[-1].split())
    if fields["step"] != str(len(batches)):
        sys.exit(f"Expected step {len(batches)}, got {lines[-1]!r}")
    loss_names = ("policy_loss", "value_loss", "total_loss")
    return tuple(float(fields[name]) for name in loss_names)


def check_failed_run(cli, checkpoint, *batches, expected_error, preexec_fn=None):
    original = checkpoint.read_bytes()
    result = subprocess.run(
        [cli, "train", checkpoint, *batches],
        cwd=checkpoint.parent,
        capture_output=True,
        text=True,
        errors="replace",
        preexec_fn=preexec_fn,
    )
    if (
        result.returncode <= 0
        or "step=1 " not in result.stdout
        or expected_error not in result.stderr
    ):
        sys.exit(
            f"Expected {expected_error!r} after the first step, got exit code "
            f"{result.returncode}.\n{result.stdout}{result.stderr}"
        )
    if checkpoint.read_bytes() != original:
        sys.exit(f"The failed run ({expected_error}) changed the existing checkpoint.")


def main():
    cli, fixture_writer = sys.argv[1:]
    with TemporaryDirectory() as directory:
        subprocess.run(
            [fixture_writer, "--write-training-batches"], cwd=directory, check=True
        )
        checkpoint = Path(directory) / "weights.pt"
        train(cli, checkpoint, "valid.pt")
        check_failed_run(
            cli, checkpoint, "valid.pt", "invalid.pt", expected_error="Outcomes must be"
        )

        if os.name == "posix":
            import resource
            import signal

            def limit_checkpoint_size():
                # Ignore SIGXFSZ so the CLI receives the write error.
                signal.signal(signal.SIGXFSZ, signal.SIG_IGN)
                resource.setrlimit(resource.RLIMIT_FSIZE, (32768, 32768))

            check_failed_run(
                cli,
                checkpoint,
                "valid.pt",
                expected_error="Failed to write weight artifact",
                preexec_fn=limit_checkpoint_size,
            )

        # Start both runs from the same saved weights.
        continuous = checkpoint.with_name("continuous.pt")
        copyfile(checkpoint, continuous)
        expected = train(cli, continuous, "valid.pt", "valid.pt")
        train(cli, checkpoint, "valid.pt")
        resumed = train(cli, checkpoint, "valid.pt")
        if not all(
            isclose(a, b, rel_tol=1e-5, abs_tol=1e-6) for a, b in zip(expected, resumed)
        ):
            sys.exit(f"Resumed losses {resumed} differ from step two {expected}.")


if __name__ == "__main__":
    main()
