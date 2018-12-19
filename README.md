# Hearthstone++

<img src="https://github.com/utilForever/Hearthstonepp/blob/master/Medias/Logo.png" width=256 height=256 />

[![License](https://img.shields.io/badge/Licence-AGPLv3-blue.svg)](https://github.com/utilForever/Hearthstonepp/blob/master/LICENSE) [![Build Status](https://travis-ci.org/utilForever/Hearthstonepp.svg?branch=master)](https://travis-ci.org/utilForever/Hearthstonepp/branches) [![Build status](https://ci.appveyor.com/api/projects/status/github/utilForever/Hearthstonepp?branch=master&svg=true)](https://ci.appveyor.com/project/utilForever/Hearthstonepp/branch/master) [![Build Status](https://dev.azure.com/utilforever/Hearthstonepp/_apis/build/status/utilForever.Hearthstonepp)](https://dev.azure.com/utilforever/Hearthstonepp/_build/latest?definitionId=2)

[![codecov](https://codecov.io/gh/utilForever/Hearthstonepp/branch/master/graph/badge.svg)](https://codecov.io/gh/utilForever/Hearthstonepp)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/df6a02e1358f4e719e7bebb9a728d2ab)](https://www.codacy.com/app/utilForever/Hearthstonepp?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=utilForever/Hearthstonepp&amp;utm_campaign=Badge_Grade) [![Discord](https://img.shields.io/discord/483192043737186335.svg)](https://discord.gg/6R3UueR)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/utilForever/Hearthstonepp.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/utilForever/Hearthstonepp/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/utilForever/Hearthstonepp.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/utilForever/Hearthstonepp/context:cpp)

Hearthstone++ is Hearthstone simulator using C++ with some reinforcement learning. The code is built on C++17 and can be compiled with commonly available compilers such as g++, clang++, or Microsoft Visual Studio. Hearthstone++ currently supports macOS (10.12.6 or later), Ubuntu (17.04 or later), Windows (Visual Studio 2017 or later), and Windows Subsystem for Linux (WSL). Other untested platforms that support C++17 also should be able to build Hearthstone++.

## Related Repositories

- [Hearthstone++ GUI](https://www.github.com/utilforever/Hearthstonepp-GUI)

## Key Features

- Support C++17 based Hearthstone library
- Provide console and GUI simulator

## To-do Features

- Upgrade "The Innkeeper" to smart
- Recommend top-tier decks
- Deck tracker
- Web simulator
- Python API

## Card Sets

### Basic & Classic

- 24% Basic (33 of 133 Cards)
- 8% Classic (20 of 236 Cards)
- 0% Hall of Fame (0 of 10 Cards)

### Adventures

- 0% One Night in Karazhan (0 of 45 Cards)
- 0% The League of Explorers (0 of 45 Cards)
- 0% Blackrock Mountain (0 of 31 Cards)
- 0% Curse of Naxxramas (0 of 30 Cards)

### Expensions

- 0% The Boomsday Project (0 of 135 Cards)
- 0% The Witchwood (0 of 135 Cards)
- 0% Kobolds & Catacombs (0 of 135 Cards)
- 0% Knights of the Frozen Throne (0 of 135 Cards)
- 0% Journey to Un'Goro (0 of 135 Cards)
- 0% Mean Streets of Gadgetzan (0 of 132 Cards)
- 0% Whispers of the Old Gods (0 of 134 Cards)
- 0% The Grand Tournament (0 of 132 Cards)
- 0% Goblins vs Gnomes (0 of 123 Cards)

## Implementation List

- [Ability list](./Documents/AbilityList.md)
- [Card list](./Documents/CardList.md)
- [Task list](./Documents/TaskList.md)

## Quick Start

You will need CMake to build the code. If you're using Windows, you need Visual Studio 2017 in addition to CMake.

First, clone the code:

```
git clone https://github.com/utilForever/Hearthstonepp.git --recursive
cd Hearthstonepp
```

### C++ API

For macOS or Linux or Windows Subsystem for Linux (WSL):

```
mkdir build
cd build
cmake ..
make
```

For Windows:

```
mkdir build
cd build
cmake .. -G"Visual Studio 15 2017 Win64"
MSBuild Hearthstonepp.sln /p:Configuration=Release
```

Now run console simulator:

```
bin/HSppConsole
```

To run GUI simulator, please check out [Hearthstone++ GUI](https://www.github.com/utilforever/Hearthstonepp-GUI).

### More Instructions of Building the Code

To learn how to build, test, and install the SDK, please check out [Install.md](./Documents/Install.md).

## Documentation

All the documentations for the framework can be found from [the project website](https://utilforever.github.io/Hearthstonepp/) incluing the API reference.

## How To Contribute

Contributions are always welcome, either reporting issues/bugs or forking the repository and then issuing pull requests when you have completed some additional coding that you feel will be beneficial to the main project. If you are interested in contributing in a more dedicated capacity, then please check out [Contributing.md](./Documents/Contributing.md).

  * [Code of Conduct](./Documents/CodeOfConduct.md)
  * [Issues](./Documents/Issues.md)
    * [How to Contribute in Issues](./Issues.md#how-to-contribute-in-issues)
    * [Asking for General Help](./Issues.md#asking-for-general-help)
    * [Submitting a Bug Report](./Issues.md#submitting-a-bug-report)
    * [Triaging a Bug Report](./Issues.md#triaging-a-bug-report)
    * [Resolving a Bug Report](./Issues.md#resolving-a-bug-report)
  * [Pull request](./Documents/PullRequests.md)
    * [Setting up your local environment](./PullRequests.md#setting-up-your-local-environment)
    * [Making Changes](./PullRequests.md#making-changes)
    * [How to add card](./HowToAddCard.md)
    * [How to add task](./HowToAddTask.md)

## Contact

You can contact me via e-mail (utilForever at gmail.com). I am always happy to answer questions or help with any issues you might have, and please be sure to share any additional work or your creations with me, I love seeing what other people are making.

## Sponsors

[![CppDepend](https://github.com/utilForever/Hearthstonepp/blob/master/Medias/CppDepend.png)](http://www.cppdepend.com)

## License

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The class is licensed under the [Affero GPLv3 License](https://opensource.org/licenses/AGPL-3.0):

Hearthstone++, Hearthstone simulator using C++ with some reinforcement learning

Copyright (C) 2017-2018 Hearthstone++ Team

- [Chris Ohk](http://www.github.com/utilForever)
- [Youngjoong Kim](https://github.com/revsic)
- [SeungHyun Jeon](https://github.com/FuZer)
- [SungHyun Kim](https://github.com/devArtoria)
- [Hyeongchan Kim](https://github.com/kozistr)

Hearthstone++ is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License.
Hearthstone++ is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.
