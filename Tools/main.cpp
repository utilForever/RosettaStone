/*************************************************************************
> File Name: main.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Main entry of Hearthstone++ tool.
> Created Time: 2018/08/18
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <clara.hpp>

#include <fstream>
#include <iostream>
#include <string>

inline std::string ToString(const clara::Opt& opt)
{
    std::ostringstream oss;
    oss << (clara::Parser() | opt);
    return oss.str();
}

inline std::string ToString(const clara::Parser& p)
{
    std::ostringstream oss;
    oss << p;
    return oss.str();
}

inline void ExportFile(const std::string& fileName)
{
    std::ofstream outputFile(fileName + ".md");
    if (outputFile)
    {
        // TODO: export card data
    }
    else
    {
        fprintf(stderr, "Failed to write file %s\n", fileName.c_str());
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[])
{
    // Parse command
    bool showHelp = false;
    std::string expansionNameA, expansionNameU, expansionNameI;

    // Parsing
    auto parser =
        clara::Help(showHelp) |
        clara::Opt(expansionNameA, "expansionName")["-a"]["--all"](
            "Export all card list to markdown format by grouping the "
            "expansion") |
        clara::Opt(expansionNameU, "expansionName")["-u"]["--unique"](
            "Export unique card list to markdown format by grouping the "
            "expansion") |
        clara::Opt(expansionNameI, "expansionName")["-i"]["--implemented"](
            "Export implemented card list to markdown format by "
            "grouping "
            "the expansion");

    auto result = parser.parse(clara::Args(argc, argv));
    if (!result)
    {
        std::cerr << "Error in command line: " << result.errorMessage() << '\n';
        exit(EXIT_FAILURE);
    }

    if (showHelp)
    {
        std::cout << ToString(parser) << '\n';
        exit(EXIT_SUCCESS);
    }

    if (!expansionNameA.empty())
    {
    }

    if (!expansionNameU.empty())
    {
    }

    if (!expansionNameI.empty())
    {
    }

    exit(EXIT_SUCCESS);
}