#!/usr/bin/env python

import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
README = ROOT / "README.md"
START = "<!-- card-stats:start -->"
END = "<!-- card-stats:end -->"
FORMATS = ("Standard", "Wild", "Classic")


def collect(format_name):
    path = ROOT / f"Documents/CardList - {format_name}.md"
    sections = {}
    section = None

    for line in path.read_text(encoding="utf-8").splitlines():
        if line.startswith("## "):
            section = line[3:]
            continue

        cells = [cell.strip() for cell in line.split("|")]
        if section and len(cells) == 4 and cells[0] not in {"Set", ":---:"}:
            if cells[3] not in {"", "O"}:
                raise ValueError(f"Unknown implementation status in {path}: {cells[3]}")
            counts = sections.setdefault(section, [0, 0])
            counts[0] += cells[3] == "O"
            counts[1] += 1

    return sections


def percentage(implemented, total):
    return f"{implemented * 100 / total:.1f}".rstrip("0").rstrip(".") + "%"


def render():
    lines = []
    for format_name in FORMATS:
        sections = collect(format_name)
        link = f"Documents/CardList%20-%20{format_name}.md"
        lines += [
            f"### [{format_name} Format]({link})",
            "",
            "| Set | Implemented | Total | Progress |",
            "| --- | ---: | ---: | ---: |",
        ]
        for name, (implemented, total) in sections.items():
            lines.append(
                f"| {name} | {implemented} | {total} | {percentage(implemented, total)} |"
            )
        implemented = sum(counts[0] for counts in sections.values())
        total = sum(counts[1] for counts in sections.values())
        lines += [
            f"| **Total** | **{implemented}** | **{total}** | **{percentage(implemented, total)}** |",
            "",
        ]
    return "\n".join(lines).rstrip()


def main():
    if sys.argv[1:] not in ([], ["--check"]):
        raise SystemExit("usage: python Scripts/card_stats.py [--check]")

    current = README.read_text(encoding="utf-8")
    before, start, rest = current.partition(START)
    _, end, after = rest.partition(END)
    if not start or not end:
        raise SystemExit("README card statistics markers are missing")

    updated = f"{before}{START}\n{render()}\n{END}{after}"
    if sys.argv[1:]:
        if current != updated:
            raise SystemExit(
                "README card statistics are stale; run python Scripts/card_stats.py"
            )
    elif current != updated:
        with README.open("w", encoding="utf-8", newline="") as output:
            output.write(updated)


if __name__ == "__main__":
    main()
