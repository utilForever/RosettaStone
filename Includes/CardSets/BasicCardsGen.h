/*************************************************************************
> File Name: BasicCardsGen.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: BasicCardsGen class that stores the power of basic cards.
> Created Time: 2018/06/23
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_BASIC_CARDS_GEN_H
#define HEARTHSTONEPP_BASIC_CARDS_GEN_H

#include <Enchants/Power.h>

#include <map>
#include <string>

namespace Hearthstonepp
{
class BasicCardsGen
{
 public:
    static void AddHeroes(std::map<std::string, Power>& cards);
    static void AddHeroPowers(std::map<std::string, Power>& cards);

    static void AddDruid(std::map<std::string, Power>& cards);
    static void AddDruidNonCollect(std::map<std::string, Power>& cards);

    static void AddHunter(std::map<std::string, Power>& cards);
    static void AddHunterNonCollect(std::map<std::string, Power>& cards);

    static void AddMage(std::map<std::string, Power>& cards);
    static void AddMageNonCollect(std::map<std::string, Power>& cards);

    static void AddPaladin(std::map<std::string, Power>& cards);
    static void AddPaladinNonCollect(std::map<std::string, Power>& cards);

    static void AddPriest(std::map<std::string, Power>& cards);
    static void AddPriestNonCollect(std::map<std::string, Power>& cards);

    static void AddRogue(std::map<std::string, Power>& cards);
    static void AddRogueNonCollect(std::map<std::string, Power>& cards);

    static void AddShaman(std::map<std::string, Power>& cards);
    static void AddShamanNonCollect(std::map<std::string, Power>& cards);

    static void AddWarlock(std::map<std::string, Power>& cards);
    static void AddWarlockNonCollect(std::map<std::string, Power>& cards);

    static void AddWarrior(std::map<std::string, Power>& cards);
    static void AddWarriorNonCollect(std::map<std::string, Power>& cards);

    static void AddNeutral(std::map<std::string, Power>& cards);
    static void AddNeutralNonCollect(std::map<std::string, Power>& cards);

    static void AddAll(std::map<std::string, Power>& cards);
};
}

#endif