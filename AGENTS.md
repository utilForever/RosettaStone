# AGENTS.md

Guidance for AI coding agents (Codex, Claude Code, etc.) working in this repository. Humans should start with [README.md](README.md); this file puts the project rules in the order an agent usually needs them.

## What this repository is

This is **RosettaStone**, a C++17 Hearthstone simulator with console tooling, generated card/task implementations, and a Python API exposed through pybind11.

It is not just a single C++ library:

- The core simulator is in `Includes/Rosetta/` and `Sources/Rosetta/`.
- Battlegrounds has its own simulator tree under `Includes/Rosetta/Battlegrounds/` and `Sources/Rosetta/Battlegrounds/`.
- The Python extension under `Extensions/RosettaPython/` exposes the C++ API through pybind11.
- Console and utility entry points live in `Extensions/RosettaConsole/` and `Extensions/RosettaTool/`.
- Card data and test fixtures live in `Resources/` and `Datas/`.
- Project documentation lives in `Documents/`.

Upstream lives at <https://github.com/utilForever/RosettaStone.git>.

## Golden rules (read before any change)

1. **Keep C++ and Python-visible behavior in sync.** If you change public types, enums, cards, tasks, zones, game flow, or other core behavior, check whether `Extensions/RosettaPython/` and `Tests/PythonTests/` need matching updates.
2. **Treat generated files as generated.** `Includes/Rosetta/RosettaStone.hpp` is produced by `Scripts/header_gen.py` during the CMake build. Change headers under `Includes/Rosetta/` or the generator, not the aggregate header by hand.
3. **Use CMake targets as the source of truth.** Before adding or moving C++ files, read the relevant `CMakeLists.txt`. Most source lists use `GLOB_RECURSE`, but target ownership and compile definitions still live there.
4. **Preserve C++17 portability.** CI builds on Ubuntu, macOS, and Windows with several compilers. Avoid compiler-specific assumptions unless they are isolated or guarded by CMake.
5. **Do not add dependencies casually.** Prefer the standard library and existing vendored libraries. If Python dependencies change, update `requirements.txt` and verify the Python tests.
6. **Run the smallest relevant check.** Documentation-only changes usually do not need a build. Code or API changes should run the focused C++ and/or Python tests below.

## Common task flow

1. Find the public API in `Includes/Rosetta/` and the implementation in `Sources/Rosetta/`.
2. Check callers with `rg` before changing shared behavior.
3. For Python-visible behavior, inspect `Extensions/RosettaPython/` before editing.
4. Add or update doctest coverage in `Tests/UnitTests/` for C++ behavior changes.
5. Add or update pytest coverage in `Tests/PythonTests/` for Python-visible behavior changes.
6. Rebuild and run only the tests needed for the change.

## Hearthstone model

RosettaStone models Hearthstone's normal play mode: two players use mana to play cards, build a board, attack with minions or weapons, and win by reducing the opposing hero to zero Health. Keep that game model in mind before translating card text into tasks.

For card metadata, prefer the checked-in `Resources/cards.json` and `Resources/cards.collectible.json` first. When those need a patch update or verification, use [HearthstoneJSON](https://hearthstonejson.com/); it publishes UTF-8 JSON files by game build and locale, with `/v1/latest/` redirecting to the latest build. Some upstream card data is wrong or incomplete, so manual additions, corrections, or exclusions may be needed. For game rules, card rulings, and mechanic explanations, prefer [Hearthstone Wiki](https://hearthstone.wiki.gg/).

Use this domain checklist when reading a card:

1. **Card type:** minion, spell, weapon, hero, hero power, enchantment, token, or location. Check `CardType.def` and nearby cards before assuming support for newer types.
2. **Class, subtype, school, and format:** card class, minion type (`Race`), spell school, and Standard/Wild/Classic format affect legal pools, Discover/random generation, and tests.
3. **Timing:** Battlecry, Deathrattle, Combo, Secret, trigger, aura, choose option, outcast, spellburst, frenzy, honorable kill, and casts-when-drawn happen at different points in the turn flow.
4. **Targeting:** Hearthstone card text says what can be targeted; RosettaStone usually enforces that with `PlayReq` and `TargetingPredicates`, not inside the effect task.
5. **Stats and zones:** Attack, Health, Armor, Durability, Cost, hand, deck, battlefield, graveyard, secret, and setaside all map to existing tags/zones. Prefer those tags over one-off state.
6. **Temporary vs persistent effects:** One-turn buffs, enchantments, auras, cost changes, and copied/transformed entities are different mechanics. Match the existing pattern from a similar card.
7. **Generated pieces:** Tokens, choice cards, enchantments, weapons, quest rewards, and linked entities usually need their own non-collectible card entries.

Do not implement the English text literally line by line. First identify the Hearthstone mechanic, then find the closest existing RosettaStone implementation and copy that shape.

Mechanic mapping notes:

- Keyword stats such as Taunt, Rush, Charge, Divine Shield, Windfury, Stealth, Poisonous, Lifesteal, Spell Damage, Overload, and Tradeable are often loaded from HearthstoneJSON `mechanics` or scalar fields into `GameTag`; do not add per-card tasks unless the card text does extra work.
- Battlecry, Combo, Deathrattle, Outcast, Spellburst, Frenzy, Honorable Kill, and casts-when-drawn are timing hooks. Put the effect in the matching `Power` task list instead of simulating the timing in a test or caller.
- Secrets, quests, questlines, dormant cards, choose options, infused/corrupted forms, tokens, weapons, and enchantments usually need linked non-collectible card IDs. Check `entourage`, `referencedTags`, `playRequirements`, and nearby card blocks before inventing IDs.
- If HearthstoneJSON data and Hearthstone Wiki text disagree, keep JSON as the baseline and use the wiki to understand intent; document any local correction near the loader or card block. Existing `CardLoader.cpp` card-specific fixes are the pattern for bad upstream metadata.

## Card logic implementation

Card behavior usually belongs in the generated-looking card set files under `Sources/Rosetta/PlayMode/CardSets/`, with matching tests under `Tests/UnitTests/PlayMode/CardSets/`. Despite the `*CardsGen.cpp` names, these files are the checked-in source for implemented card logic.

Battlegrounds card logic is separate. Put Battlegrounds-only cards, tavern/combat behavior, tasks, and tests under `Sources/Rosetta/Battlegrounds/`, `Includes/Rosetta/Battlegrounds/`, and `Tests/UnitTests/Battlegrounds/`; do not mix it into PlayMode unless the shared type already exists outside both trees.

When adding or fixing a card:

1. Find the card's set and class in `Resources/cards.json`, `Resources/cards.collectible.json`, or the card list documents.
2. Edit the matching `*CardsGen.cpp` function, such as `AddDruid`, `AddMageNonCollect`, or `AddNeutral`.
3. Start each card block with `cardDef.ClearData()`, then set `cardDef.power` and `cardDef.property`.
4. Add the card with `cards.emplace("CARD_ID", cardDef)` and keep the existing comment format.
5. Add a focused scenario test in the matching `*CardsGenTests.cpp` file.

Use the existing building blocks before writing new engine code:

- Play effects go in `cardDef.power.AddPowerTask(...)`.
- Ongoing board or hand effects use `AddAura(...)` or an existing `Aura`/`AdaptiveCostEffect`.
- Buffs and enchantment cards use `AddEnchantmentTask("ENCHANT_ID", ...)` plus a non-collectible entry whose `power` calls `AddEnchant(...)`.
- Triggered effects use `AddTrigger(...)` or `cardDef.power.GetTrigger()->tasks`, following nearby cards. Set `triggerSource` and `triggerActivation` when the trigger cares about who caused it or whether it works from play, hand, deck, or both.
- Choose One cards usually set `cardDef.property.chooseCardIDs` and use the option cards for the actual effects.
- Discover/random pools, Colossal appendages, Corrupt/Infuse forms, quest progress, and replacement hero powers usually belong in `cardDef.property` fields such as `entourages`, `appendages`, `corruptCardID`, `infusedCardID`, `numMinionsToInfuse`, `questProgressTotal`, and `heroPowerDbfID`.
- Targeting rules belong in `cardDef.property.playReqs`, not in ad hoc task guards.

Before adding a new task, search `Includes/Rosetta/PlayMode/Tasks/`, `Sources/Rosetta/PlayMode/Tasks/`, and `Documents/TaskList.md`. A short task chain with existing `IncludeTask`, `FilterStackTask`, `ConditionTask`, `FlagTask`, `AddEnchantmentTask`, `DamageTask`, `DrawTask`, `SummonTask`, or `ComplexTask` is usually enough.

Card tests should drive the game the way a player would: create `GameConfig`, set `config.formatType` to the card's format, call `game.Start()`, `game.ProcessUntil(Step::MAIN_ACTION)`, draw cards with `Generic::DrawCard`, play them with `PlayCardTask`, then assert board, hand, hero, weapon, enchantment, or trigger results with `CHECK_EQ`. Pass `FormatType` to `Cards::FindCardByName` when a name exists in more than one format. Prefer one clear scenario over broad setup helpers.

Useful docs:

- [HowToAddCard.md](Documents/HowToAddCard.md)
- [HowToAddTask.md](Documents/HowToAddTask.md)
- [AbilityList.md](Documents/AbilityList.md)
- [TaskList.md](Documents/TaskList.md)
- [HearthstoneJSON](https://hearthstonejson.com/)
- [Hearthstone Wiki](https://hearthstone.wiki.gg/)

## Repository map

| Area                    | Paths                                                                                                                           | What to check                                                  |
| ----------------------- | ------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------- |
| Core C++ API            | `Includes/Rosetta/`                                                                                                             | Public headers, enums, models, tasks, zones, card definitions  |
| Core C++ implementation | `Sources/Rosetta/`                                                                                                              | Game behavior, task execution, loaders, cards, auras, triggers |
| Battlegrounds           | `Includes/Rosetta/Battlegrounds/`, `Sources/Rosetta/Battlegrounds/`, `Tests/UnitTests/Battlegrounds/`                           | Battlegrounds cards, tavern/combat behavior, and tests         |
| Python binding          | `Extensions/RosettaPython/`                                                                                                     | pybind11 module and Python-facing API                          |
| Console/tool apps       | `Extensions/RosettaConsole/`, `Extensions/RosettaTool/`                                                                         | CLI entry points and utility behavior                          |
| C++ tests               | `Tests/UnitTests/`                                                                                                              | doctest coverage for core behavior                             |
| Python tests            | `Tests/PythonTests/`                                                                                                            | pytest coverage for Python-facing behavior                     |
| Data and fixtures       | `Resources/`, `Datas/`                                                                                                          | Card JSON data and small test data                             |
| Build configuration     | `CMakeLists.txt`, `Sources/Rosetta/CMakeLists.txt`, `Tests/UnitTests/CMakeLists.txt`, `Extensions/RosettaPython/CMakeLists.txt` | Target wiring, compile definitions, generated header behavior  |
| Python packaging        | `Builds/setup.py.in`, generated `setup.py`, `requirements.txt`                                                                  | pybind11 build settings and Python dependencies                |
| Tooling                 | `Scripts/`, `Builds/CMake/`                                                                                                     | Header generation and CMake helpers                            |
| CI                      | `.github/workflows/`                                                                                                            | Platform matrix and required build/test sequence               |
| Docs and media          | `Documents/`, `Medias/`                                                                                                         | User-facing documentation, logos, presentations, images        |

## Build and validation

Configure and build:

```sh
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
```

Run C++ unit tests after building:

```sh
./build/bin/UnitTests
```

On Windows release builds, the executable is usually:

```bat
build\bin\Release\UnitTests.exe
```

Run Python tests after installing the package:

```sh
python -m pip install -r requirements.txt
python -m pip install .
python -m pytest Tests/PythonTests/
```

For coverage work, CI configures a Debug build with `-DBUILD_COVERAGE=ON`, runs `UnitTests`, collects coverage with lcov, and uploads the cleaned report to Codecov.

## CI expectations

The main GitHub Actions workflows build on Ubuntu, macOS, and Windows. They configure CMake, build the C++ project, run `UnitTests`, install Python requirements, install the Python package, and run `pytest` against `Tests/PythonTests/`.

Treat those workflows as the compatibility contract. A change that only works on the local platform is not complete.

## Commit conventions

- Use focused commits with conventional prefixes where they fit: `feat:`, `fix:`, `refactor:`, `test:`, `docs:`, or `chore:`.
- Keep generated or Python binding updates in the same commit as the source change that requires them.
- Do not mix documentation, dependency, and behavior changes unless they are part of the same logical fix.
- For agent-assisted commits, it is fine to include an `Assisted-by:` trailer if the maintainer wants that recorded.

## Leave alone unless asked

- Large media files under `Medias/`.
- Vendored libraries under `Libraries/`.
- Generated aggregate headers, unless the generator output is the actual target.
- CI matrix entries and platform versions, unless the task is about CI support.
