# Hearthstone++

<img src="https://github.com/utilForever/Hearthstonepp/blob/master/Logo.png" align="center" width=256 height=256 />

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/ffcbfe61470e4f9da7131db3abb34487)](https://app.codacy.com/app/utilForever/Hearthstonepp?utm_source=github.com&utm_medium=referral&utm_content=utilForever/Hearthstonepp&utm_campaign=badger)
[![License](https://img.shields.io/badge/Licence-MIT-blue.svg)](https://github.com/utilForever/Hearthstonepp/blob/master/LICENSE) [![Build Status](https://travis-ci.org/utilForever/Hearthstonepp.svg?branch=master)](https://travis-ci.org/utilForever/Hearthstonepp/branches) [![Build status](https://ci.appveyor.com/api/projects/status/github/utilForever/Hearthstonepp?branch=master&svg=true)](https://ci.appveyor.com/project/utilForever/Hearthstonepp/branch/master) [![codecov](https://codecov.io/gh/utilForever/Hearthstonepp/branch/master/graph/badge.svg)](https://codecov.io/gh/utilForever/Hearthstonepp)

Hearthstone++ is hearthstone simulator using C++ with some reinforcement learning. The code is built on C++17 and can be compiled with commonly available compilers such as g++, clang++, or Microsoft Visual Studio. Hearthstone++ currently supports macOS (10.12.6 or later), Ubuntu (17.04 or later), Windows (Visual Studio 2017 or later), and Windows Subsystem for Linux (WSL). Other untested platforms that support C++17 also should be able to build Hearthstone++.

## Key Features

- JSON-based hearthstone card data
- Console, GUI, web-based simulator
- Reinforcement learning to "The Innkeeper" smart
- C++ and Python API

## Card Ability

- [ ] Adapt
- [ ] Auto-Attack
- [ ] Auto-cast
- [ ] Battlecry
- [ ] Cast spell
- [ ] Charge
- [ ] Choose One
- [ ] Choose Twice
- [ ] Combo
- [ ] Copy
- [ ] Deal damage
- [ ] Deathrattle
- [ ] Destroy
- [ ] Discard
- [ ] Discover
- [ ] Divine Shield
- [ ] Draw cards
- [ ] Echo
- [ ] Elusive
- [ ] Enrage
- [ ] Equip
- [ ] Forgetful
- [ ] Freeze
- [ ] Gain Armor
- [ ] Generate
- [ ] Immune
- [ ] Inspire
- [ ] Joust
- [ ] Lifesteal
- [ ] Mega-Windfury
- [ ] Modify cost
- [ ] Overload
- [ ] Permanent
- [ ] Poisonous
- [ ] Put into battlefield
- [ ] Put into hand
- [ ] Quest
- [ ] Recruit
- [ ] Refresh Mana
- [ ] Remove from deck
- [ ] Replace
- [ ] Rush
- [ ] Restore Health
- [ ] Return to hand
- [ ] Secret
- [ ] Shuffle into deck
- [ ] Silence
- [ ] Spell Damage
- [ ] Spend mana
- [ ] Start of Game
- [ ] Stealth
- [ ] Summon
- [ ] Taunt
- [ ] Take control
- [ ] Transform
- [ ] Unlimited attacks
- [ ] Upgradable
- [ ] Windfury

## Card Sets

### Basic & Classic

- 0% Basic (142 Cards)
- 0% Classic (239 Cards)
- 0% Hall of Fame (10 Cards)

### Adventures

- 0% One Night in Karazhan (45 Cards)
- 0% The League of Explorers (45 Cards)
- 0% Blackrock Mountain (31 Cards)
- 0% Curse of Naxxramas (30 Cards)

### Expensions

- 0% The Witchwood (135 Cards)
- 0% Kobolds & Catacombs (135 Cards)
- 0% Knights of the Frozen Throne (135 Cards)
- 0% Journey to Un'Goro (135 Cards)
- 0% Mean Streets of Gadgetzan (132 Cards)
- 0% Whispers of the Old Gods (134 Cards)
- 0% The Grand Tournament (132 Cards)
- 0% Goblins vs Gnomes (123 Cards)

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

Now run simulators, such as:

```
bin/HSppConsole
```

### Python API

TBA

### More Instructions of Building the Code

To learn how to build, test, and install the SDK, please check out [INSTALL.md](https://github.com/utilForever/Hearthstonepp/blob/master/INSTALL.md).

## Documentation

All the documentations for the framework can be found from [the project website](https://utilforever.github.io/Hearthstonepp/) incluing the API reference.

## How To Contribute

Contributions are always welcome, either reporting issues/bugs or forking the repository and then issuing pull requests when you have completed some additional coding that you feel will be beneficial to the main project. If you are interested in contributing in a more dedicated capacity, then please contact me.

## Contact

You can contact me via e-mail (utilForever at gmail.com). I am always happy to answer questions or help with any issues you might have, and please be sure to share any additional work or your creations with me, I love seeing what other people are making.

## License

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The class is licensed under the [MIT License](http://opensource.org/licenses/MIT):

Copyright &copy; 2018 [Chris Ohk](http://www.github.com/utilForever), [Youngjoong Kim](https://github.com/revsic), [SeungHyun Jeon](https://github.com/FuZer), [SungHyun Kim](https://github.com/devArtoria) and [JunYoung Park](https://github.com/ChalkPE).

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.