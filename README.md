# RosettaStone

<p align="center">
  <picture>
    <img src="./Medias/Logos/Logo.png" width="400" alt="RosettaStone logo" />
  </picture>
</p>
<p align="center">
  <b>A C++17 Hearthstone simulator with C++, Python, console, and tooling interfaces</b>
</p>
<p align="center">
  <a href="LICENSE"><img src="https://img.shields.io/badge/License-AGPL_v3-blue.svg" alt="License: AGPL v3" /></a>
  <a href="https://github.com/utilForever/RosettaStone/actions/workflows/windows.yml"><img src="https://github.com/utilForever/RosettaStone/actions/workflows/windows.yml/badge.svg?branch=main" alt="Windows" /></a>
  <a href="https://github.com/utilForever/RosettaStone/actions/workflows/ubuntu.yml"><img src="https://github.com/utilForever/RosettaStone/actions/workflows/ubuntu.yml/badge.svg?branch=main" alt="Ubuntu" /></a>
  <a href="https://github.com/utilForever/RosettaStone/actions/workflows/macos.yml"><img src="https://github.com/utilForever/RosettaStone/actions/workflows/macos.yml/badge.svg?branch=main" alt="macOS" /></a>
  <br />
  <a href="https://github.com/utilForever/RosettaStone/actions/workflows/ubuntu-codecov.yml"><img src="https://github.com/utilForever/RosettaStone/actions/workflows/ubuntu-codecov.yml/badge.svg?branch=main" alt="Code Coverage" /></a>
  <a href="https://codecov.io/gh/utilForever/RosettaStone"><img src="https://codecov.io/gh/utilForever/RosettaStone/branch/main/graph/badge.svg" alt="Codecov" /></a>
  <a href="https://github.com/utilForever/RosettaStone/actions/workflows/ubuntu-sonarcloud.yml"><img src="https://github.com/utilForever/RosettaStone/actions/workflows/ubuntu-sonarcloud.yml/badge.svg?branch=main" alt="Static Analysis" /></a>
  <a href="https://sonarcloud.io/summary/new_code?id=RosettaStone"><img src="https://sonarcloud.io/api/project_badges/measure?project=RosettaStone&metric=alert_status" alt="Quality Gate Status" /></a>
  <a href="https://sonarcloud.io/summary/new_code?id=RosettaStone"><img src="https://sonarcloud.io/api/project_badges/measure?project=RosettaStone&metric=ncloc" alt="Lines of Code" /></a>
  <br />
  <a href="https://sonarcloud.io/summary/new_code?id=RosettaStone"><img src="https://sonarcloud.io/api/project_badges/measure?project=RosettaStone&metric=sqale_rating" alt="Maintainability Rating" /></a>
  <a href="https://sonarcloud.io/summary/new_code?id=RosettaStone"><img src="https://sonarcloud.io/api/project_badges/measure?project=RosettaStone&metric=reliability_rating" alt="Reliability Rating" /></a>
  <a href="https://sonarcloud.io/summary/new_code?id=RosettaStone"><img src="https://sonarcloud.io/api/project_badges/measure?project=RosettaStone&metric=security_rating" alt="Security Rating" /></a>
  <a href="https://sonarcloud.io/summary/new_code?id=RosettaStone"><img src="https://sonarcloud.io/api/project_badges/measure?project=RosettaStone&metric=bugs" alt="Bugs" /></a>
  <a href="https://sonarcloud.io/summary/new_code?id=RosettaStone"><img src="https://sonarcloud.io/api/project_badges/measure?project=RosettaStone&metric=vulnerabilities" alt="Vulnerabilities" /></a>
  <a href="https://sonarcloud.io/summary/new_code?id=RosettaStone"><img src="https://sonarcloud.io/api/project_badges/measure?project=RosettaStone&metric=sqale_index" alt="Technical Debt" /></a>
</p>

RosettaStone models Hearthstone's normal play mode and Battlegrounds. The core simulator is shared by the C++ API, the `pyRosetta` Python extension, and the console and utility programs.

## What This Project Does

- Provides a reusable C++17 Hearthstone simulator library.
- Models cards, entities, zones, tasks, triggers, auras, and game flow.
- Keeps normal play and Battlegrounds in separate simulator trees.
- Exposes the simulator to Python through pybind11.
- Includes console and utility executables, card data, and C++ and Python tests.

For deeper design details, see [ARCHITECTURE.md](ARCHITECTURE.md). For coding-agent rules, see [AGENTS.md](AGENTS.md).

## Quick Start

### Prerequisites

- A C++17 compiler
- CMake 3.31.6 or later
- [vcpkg](https://vcpkg.io/) with `VCPKG_ROOT` set
- Python 3.12 or later for the Python API and tests
- Git

### 1. Clone

```bash
git clone https://github.com/utilForever/RosettaStone.git --recursive
cd RosettaStone
```

### 2. Build

```bash
cmake -S . -B build \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
cmake --build build --config Release
```

### 3. Run the C++ Tests

macOS, Linux, and WSL:

```bash
./build/bin/UnitTests
```

Windows release builds:

```powershell
.\build\bin\Release\UnitTests.exe
```

### 4. Install and Test the Python API

```bash
python -m pip install -r requirements.txt
python -m pip install .
python -m pytest Tests/PythonTests/
```

## Architecture at a Glance

| Area                | Paths                                                               | Purpose                                               |
| ------------------- | ------------------------------------------------------------------- | ----------------------------------------------------- |
| Core C++ API        | `Includes/Rosetta/`                                                 | Public simulator headers and models                   |
| Core implementation | `Sources/Rosetta/`                                                  | Game flow, loaders, tasks, cards, auras, and triggers |
| Battlegrounds       | `Includes/Rosetta/Battlegrounds/`, `Sources/Rosetta/Battlegrounds/` | Battlegrounds-specific simulation                     |
| Python API          | `Extensions/RosettaPython/`                                         | pybind11 bindings for `pyRosetta`                     |
| Applications        | `Extensions/RosettaConsole/`, `Extensions/RosettaTool/`             | Console and utility executables                       |
| Tests               | `Tests/UnitTests/`, `Tests/PythonTests/`                            | C++ doctest and Python pytest coverage                |
| Data                | `Resources/`, `Datas/`                                              | Card metadata and fixtures                            |
| Documentation       | `Documents/`                                                        | Build, API, card, task, and contribution guides       |

The full [architecture guide](ARCHITECTURE.md) explains game flow, the runtime model, card loading, effect timing, module boundaries, and Python API synchronization.

## Card Implementation

Implementation details and current support are tracked in:

- [Ability list](Documents/AbilityList.md)
- [Standard card list](Documents/CardList%20-%20Standard.md)
- [Wild card list](Documents/CardList%20-%20Wild.md)
- [Classic card list](Documents/CardList%20-%20Classic.md)
- [Task list](Documents/TaskList.md)

## Development

Use CMake targets as the source of truth and run the narrowest checks that cover a change. The CI workflows build on Ubuntu, macOS, and Windows, run the C++ unit tests, install `pyRosetta`, and run the Python tests.

When changing public C++ behavior, keep `Extensions/RosettaPython/` and `Tests/PythonTests/` in sync. Treat `Includes/Rosetta/RosettaStone.hpp` as generated output.

See [AGENTS.md](AGENTS.md) for the repository workflow and [Documents/Contributing.md](Documents/Contributing.md) for contribution guidelines.

## Documentation

- [Architecture](ARCHITECTURE.md)
- [Installation](Documents/Install.md)
- [How to add a card](Documents/HowToAddCard.md)
- [How to add a task](Documents/HowToAddTask.md)
- [API reference](https://utilforever.github.io/RosettaStone/)

## Related Repository

- [RosettaStone GUI](https://github.com/utilForever/RosettaStone-GUI)

## Presentations and Media

- [TFCON 2018 Poster Session](Medias/Presentations/TFCON%202018%20-%20Hearthstone%2B%2B%2C%20Hearthstone%20Simulator%20with%20Reinforcement%20Learning.pdf)
- [NDC 2019 presentation](Medias/Presentations/NDC%202019%20-%20Development%20Process%20of%20Hearthstone%20Reinforcement%20Learning%20Environment%20%28Korean%29.pdf)
- [NDC 2019 video](https://www.youtube.com/watch?v=yO9QRinXosE)

## Sponsor

[![CppDepend](Medias/Logos/CppDepend.png)](https://www.cppdepend.com/)

## License

RosettaStone is licensed under the [GNU Affero General Public License v3.0](LICENSE).

RosettaStone is based on part of SabberStone's code.

Copyright &copy; 2017-2021 SabberStone Team, darkfriend77, and rnilva<br />
Copyright &copy; 2017-2026 [Chris Ohk](https://github.com/utilForever)

Hearthstone is an interactive game of Blizzard Entertainment, Inc. and all rights are reserved. Hearthstone is a registered trademark of Blizzard Entertainment, Inc. in the U.S. and/or other countries. This project is not affiliated with Blizzard Entertainment.
