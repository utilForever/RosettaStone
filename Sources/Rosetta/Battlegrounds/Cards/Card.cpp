// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Cards/Card.hpp>

namespace RosettaStone::Battlegrounds
{
CardType Card::GetCardType() const
{
    return static_cast<CardType>(gameTags.at(GameTag::CARDTYPE));
}

int Card::GetTier() const
{
    if (gameTags.find(GameTag::TECH_LEVEL) == gameTags.end())
    {
        return 0;
    }

    return gameTags.at(GameTag::TECH_LEVEL);
}

bool Card::IsTier1MinionInPool() const
{
    // Tier 1 minion list (dbfID)
    // Alleycat (40426)
    // Dire Wolf Alpha (985)
    // Dragonspawn Lieutenant (60628)
    // Fiendish Servant (56112)
    // Mecharoo (48886)
    // Micro Machine (60055)
    // Murloc Tidecaller (475)
    // Murloc Tidehunter (976)
    // Righteous Protector (42467)
    // Red Whelp (59968)
    // Rockpool Hunter (41245)
    // Selfless Hero (38740)
    // Vulgar Homunculus (43121)
    // Wrath Weaver (59670)
    if (dbfID == 40426 || dbfID == 985 || dbfID == 60628 || dbfID == 56112 ||
        dbfID == 48886 || dbfID == 60055 || dbfID == 475 || dbfID == 976 ||
        dbfID == 42467 || dbfID == 59968 || dbfID == 41245 || dbfID == 38740 ||
        dbfID == 43121 || dbfID == 59670)
    {
        return true;
    }

    return false;
}

bool Card::IsTier2MinionInPool() const
{
    // Tier 2 minion list (dbfID)
    // Glyph Guardian (61029)
    // Harvest Golem (778)
    // Imprisoner (59937)
    // Kaboom Bot (49279)
    // Kindly Grandmother (39481)
    // Metaltooth Leaper (2016)
    // Murloc Warleader (1063)
    // Nathrezim Overseer (59186)
    // Old Murk-Eye (736)
    // Pogo-Hopper (48471)
    // Rat Pack (40428)
    // Scavenging Hyena (1281)
    // Spawn of N'Zoth (38797)
    // Steward of Time (60621)
    // Unstable Ghoul (1808)
    // Waxrider Togwaggle (60559)
    // Zoobot (39839)
    if (dbfID == 61029 || dbfID == 778 || dbfID == 59937 || dbfID == 49279 ||
        dbfID == 39481 || dbfID == 2016 || dbfID == 1063 || dbfID == 59186 ||
        dbfID == 736 || dbfID == 48471 || dbfID == 40428 || dbfID == 1281 ||
        dbfID == 38797 || dbfID == 60621 || dbfID == 1808 || dbfID == 60559 ||
        dbfID == 39839)
    {
        return true;
    }

    return false;
}

bool Card::IsTier3MinionInPool() const
{
    // Tier 3 minion list (dbfID)
    // Bronze Warden (60558)
    // Coldlight Seer (453)
    // Crystalweaver (40391)
    // Crowd Favorite (2518)
    // Deflect-o-Bot (61930)
    // Felfin Navigator (56393)
    // Hangry Dragon (60552)
    // Houndmaster (1003)
    // Imp Gang Boss (58582)
    // Infested Wolf (38734)
    // Khadgar (52502)
    // Pack Leader (59940)
    // Piloted Shredder (60048)
    // Replicating Menace (48536)
    // Screwjank Clunker (2023)
    // Shifter Zerus (38475)
    // Soul Juggler (59660)
    // The Beast (962)
    // Twilight Emissary (60626)
    if (dbfID == 60558 || dbfID == 453 || dbfID == 40391 || dbfID == 2518 ||
        dbfID == 61930 || dbfID == 56393 || dbfID == 60552 || dbfID == 1003 ||
        dbfID == 58582 || dbfID == 38734 || dbfID == 52502 || dbfID == 59940 ||
        dbfID == 60048 || dbfID == 48536 || dbfID == 2023 || dbfID == 38475 ||
        dbfID == 59660 || dbfID == 962 || dbfID == 60626)
    {
        return true;
    }

    return false;
}

bool Card::IsTier4MinionInPool() const
{
    // Tier 4 minion list (dbfID)
    // Annoy-o-Module (48993)
    // Bolvar, Fireblood (45392)
    // Cave Hydra (43358)
    // Cobalt Scalebane (42442)
    // Defender of Argus (763)
    // Drakonid Enforcer (61072)
    // Floating Watcher (2068)
    // Herald of Flame (60498)
    // Iron Sensei (1992)
    // Mechano-Egg (49169)
    // Menagerie Magician (39269)
    // Savannah Highmane (1261)
    // Security Rover (48100)
    // Siegebreaker (54835)
    // Toxfin (52277)
    // Virmen Sensei (40641)
    if (dbfID == 48993 || dbfID == 45392 || dbfID == 43358 || dbfID == 42442 ||
        dbfID == 763 || dbfID == 61072 || dbfID == 2068 || dbfID == 60498 ||
        dbfID == 1992 || dbfID == 49169 || dbfID == 39269 || dbfID == 1261 ||
        dbfID == 48100 || dbfID == 54835 || dbfID == 52277 || dbfID == 40641)
    {
        return true;
    }

    return false;
}

bool Card::IsTier5MinionInPool() const
{
    // Tier 5 minion list (dbfID)
    // Annihilan Battlemaster (59714)
    // Baron Rivendare (1915)
    // Brann Bronzebeard (2949)
    // Goldrinn, the Great Wolf (59955)
    // Ironhide Direhorn (49973)
    // Junkbot (2074)
    // King Bagurgle (60247)
    // Lightfang Enforcer (59707)
    // Mal'Ganis (1986)
    // Murozond (51108)
    // Primalfin Lookout (41478)
    // Razorgore, the Untamed (60561)
    // Sneed's Old Shredder (2082)
    // Strongshell Scavenger (43022)
    // Voidlord (46056)
    if (dbfID == 59714 || dbfID == 1915 || dbfID == 2949 || dbfID == 59955 ||
        dbfID == 49973 || dbfID == 2074 || dbfID == 60247 || dbfID == 59707 ||
        dbfID == 1986 || dbfID == 51108 || dbfID == 41478 || dbfID == 60561 ||
        dbfID == 2082 || dbfID == 43022 || dbfID == 46056)
    {
        return true;
    }

    return false;
}

bool Card::IsTier6MinionInPool() const
{
    // Tier 6 minion list (dbfID)
    // Foe Reaper 4000 (2081)
    // Kangor's Apprentice (59935)
    // Gentle Megasaur (56465)
    // Ghastcoiler (52041)
    // Holy Mackerel (61079)
    // Imp Mama (61028)
    // Kalecgos, Arcane Aspect (60630)
    // Maexxna (1791)
    // Mama Bear (60036)
    // Nadina the Red (60629)
    // Zapp Slywick (60040)
    if (dbfID == 2081 || dbfID == 59935 || dbfID == 56465 || dbfID == 52041 ||
        dbfID == 61079 || dbfID == 61028 || dbfID == 60630 || dbfID == 1791 ||
        dbfID == 60036 || dbfID == 60629 || dbfID == 60040)
    {
        return true;
    }

    return false;
}
}  // namespace RosettaStone::Battlegrounds
