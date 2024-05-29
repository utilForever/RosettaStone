// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "Console.hpp"

#include <lyra/lyra.hpp>

using namespace RosettaStone;

int main(int argc, char* argv[])
{
    // Splash logo
    std::cout << R"(
    .#####....####....####...######..######..######...####....####....####...##..##...####....####...##......######.
    .##..##..##..##..##......##........##......##....##..##..##..##..##..##..###.##..##......##..##..##......##.....
    .#####...##..##...####...####......##......##....######..##......##..##..##.###...####...##..##..##......####...
    .##..##..##..##......##..##........##......##....##..##..##..##..##..##..##..##......##..##..##..##......##.....
    .##..##...####....####...######....##......##....##..##...####....####...##..##...####....####...######..######.
    ................................................................................................................)";
    std::cout << "\n\n";

    int mode = 0;
    bool showHelp = false;

    // Process CLI
    const auto cli =
        lyra::cli() | lyra::help(showHelp) |
        lyra::opt(mode, "mode")["-m"]["--mode"](
            "The game mode. (1 - Standard, 2 - Wild, 3 - Battlegrounds");
    const auto result = cli.parse({ argc, argv });

    if (!result)
    {
        std::cerr << "Error in command line: " << result.message() << '\n';
        std::cerr << cli << '\n';
        return EXIT_FAILURE;
    }

    if (showHelp)
    {
        std::cout << cli << '\n';
        return EXIT_SUCCESS;
    }

    if (mode < 1 || mode > 3)
    {
        std::cerr << "Invalid game mode.\n";
        return EXIT_FAILURE;
    }

    Console console{ static_cast<Console::Mode>(mode) };
    console.ProcessGame();

    return EXIT_SUCCESS;
}