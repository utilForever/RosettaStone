
/*************************************************************************
> File Name: main.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Main entry of Hearthstone++ tool.
> Created Time: 2018/08/21
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
    bool exportAllCard = false;
    std::string cardSetName;

    // Parsing
    auto parser = clara::Help(showHelp) |
                  clara::Opt(exportAllCard)["-a"]["--all"](
                      "Export all card set list to markdown format") |
                  clara::Opt(cardSetName, "cardSet")["-c"]["--cardset"](
                      "Export specific card set list to markdown format");

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

    if (exportAllCard)
    {
         
    }
    else if (!cardSetName.empty())
    {
        
    }

    exit(EXIT_SUCCESS);
}