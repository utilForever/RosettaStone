#include <hspp/CardSets/BasicCardsGen.h>
#include <hspp/Enchants/Effects.h>
#include <hspp/Tasks/BasicTasks/DestroyTask.h>
#include <hspp/Tasks/PowerTasks/AddEnchantmentTask.h>
#include <hspp/Tasks/PowerTasks/DiscardTask.h>
#include <hspp/Tasks/PowerTasks/HealFullTask.h>
#include <hspp/Tasks/PowerTasks/HealTask.h>

namespace Hearthstonepp
{
void BasicCardsGen::AddHeroes(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddHeroPowers(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddDruid(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddDruidNonCollect(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddHunter(std::map<std::string, Power*>& cards)
{
    // ----------------------------------------- MINION - HUNTER
    // [EX1_543] King Krush - COST:9 [ATK:8/HP:8]
    // - Race: beast, Set: expert1, Rarity: legendary
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cards.emplace("EX1_543", nullptr);
}

void BasicCardsGen::AddHunterNonCollect(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddMage(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddMageNonCollect(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddPaladin(std::map<std::string, Power*>& cards)
{
    (void)cards;

    // --------------------------------------- MINION - Paladin
    // [CS2_088] Guardian of Kings - COST:7
    // - Faction: Neutral, Set: Basic, Rarity: Free
    // --------------------------------------------------------
    // CtrlCVplz...
    // --------------------------------------------------------
    Power* p = new Power;
    p->powerTask.emplace_back(new PowerTask::HealTask(EntityType::MY_HERO, 6));
    cards.emplace("CS2_088", p);
}

void BasicCardsGen::AddPaladinNonCollect(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddPriest(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddPriestNonCollect(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddRogue(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddRogueNonCollect(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddShaman(std::map<std::string, Power*>& cards)
{
    // ----------------------------------------- SPELL - SHAMAN
    // [CS2_041] Ancestral Healing - COST:0
    // - Faction: Neutral, Set: Basic, Rarity: Free
    // --------------------------------------------------------
    // Text: Restore a minion
    //       to full Health and
    //       give it <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // Tag:
    // - TAUNT = 1
    // --------------------------------------------------------
    Power* p = new Power;
    p->powerTask.emplace_back(new PowerTask::HealFullTask(EntityType::TARGET));
    p->powerTask.emplace_back(
        new PowerTask::AddEnchantmentTask("CS2_041e", EntityType::TARGET));
    cards.emplace("CS2_041", p);
}

void BasicCardsGen::AddShamanNonCollect(std::map<std::string, Power*>& cards)
{
    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [CS2_041e] Ancestral Infusion (*) - COST:0
    // - Set: core,
    // --------------------------------------------------------
    // Text: Taunt.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    Power* p = new Power;
    p->enchant = new Enchant(Effects::Taunt);
    cards.emplace("CS2_041e", p);
}

void BasicCardsGen::AddWarlock(std::map<std::string, Power*>& cards)
{
    // --------------------------------------- MINION - NEUTRAL
    // [EX1_306] Succubus - COST:2 [ATK:4/HP:3]
    // - Fac: horde, Set: core, Rarity: free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Discard a random card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    Power* p = new Power;
    p->powerTask.emplace_back(new PowerTask::DiscardTask(EntityType::MY_HAND));
    cards.emplace("EX1_306", p);
}

void BasicCardsGen::AddWarlockNonCollect(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddWarrior(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddWarriorNonCollect(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddNeutral(std::map<std::string, Power*>& cards)
{
    // --------------------------------------- MINION - NEUTRAL
    // [EX1_066] Acidic Swamp Ooze - COST:2 [ATK:3/HP:2]
    // - Fac: alliance, Set: core, Rarity: free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy your opponent's weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    Power* p = new Power;
    p->powerTask.emplace_back(
        new BasicTasks::DestroyTask(EntityType::OPPONENT_WEAPON));
    cards.emplace("EX1_066", p);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_171] Stonetusk Boar - COST:1 [ATK:1/HP:1]
    // - Race: beast, Fac: neutral, Set: core, Rarity: free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cards.emplace("CS2_171", nullptr);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_201] Core Hound - COST:7 [ATK:9/HP:5]
    // - Race: beast
    // --------------------------------------------------------
    cards.emplace("CS2_201", nullptr);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_155] Archmage - COST:6 [ATK:4/HP:7]
    cards.emplace("CS2_155", nullptr);

    // [CS2_172] Bloodfen Raptor - COST:2 [ATK:3/HP:2]
    // - Race: beast, Fac: neutral, Set: core, Rarity: free
    // --------------------------------------------------------
    // Text: <b>"Kill 30 raptors." - Hemet Nesingwary</b>
    // --------------------------------------------------------
    // GameTag:
    //
    // --------------------------------------------------------
    cards.emplace("CS2_172", nullptr);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_179] Sen'jin Shieldmasta - COST:4 [ATK:3/HP:5]
    // - Race: troll, Fac: HORDE, Set: core, Rarity: free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - Taunt = 1
    // --------------------------------------------------------
    cards.emplace("CS2_179", nullptr);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_124] Wolfrider - COST:3 [ATK:3/HP:1]
    // - Set: core, Rarity: free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cards.emplace("CS2_124", nullptr);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_213] Reckless Rocketeer - COST:6 [ATK:5/HP:2]
    // - Set: core, Rarity: free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cards.emplace("CS2_213", nullptr);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_131] Stormwind Knight - COST:4 [ATK:2/HP:5]
    // - Set: core, Rarity: free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cards.emplace("CS2_131", nullptr);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_173] Bluegill Warrior - COST:2 [ATK:2/HP:1]
    // - Race: murloc, Set: core, Rarity: free
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cards.emplace("CS2_173", nullptr);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_118] Magma Rager - COST:3 [ATK:5/HP:1]
    // - Race: element, Fac: neutral, Set: core, Rarity: free
    // --------------------------------------------------------
    cards.emplace("CS2_118", nullptr);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_182] Chillwind Yeti - COST:4 [ATK:4/HP:5]
    // - Set: core, Rarity: free
    // --------------------------------------------------------
    // Text: <b></b>
    // --------------------------------------------------------
    // GameTag:
    // -
    // --------------------------------------------------------
    cards.emplace("CS2_182", nullptr);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_187] Booty Bay Bodyguard - COST:5 [ATK:5/HP:4]
    // - Set: core, Rarity: free
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - Taunt = 1
    // --------------------------------------------------------
    Power* p1 = new Power;
    p1->enchant = new Enchant(Effects::Taunt);
    cards.emplace("CS2_187", p1);
}

void BasicCardsGen::AddNeutralNonCollect(std::map<std::string, Power*>& cards)
{
    (void)cards;
}

void BasicCardsGen::AddAll(std::map<std::string, Power*>& cards)
{
    AddHeroes(cards);
    AddHeroPowers(cards);

    AddDruid(cards);
    AddDruidNonCollect(cards);

    AddHunter(cards);
    AddHunterNonCollect(cards);

    AddMage(cards);
    AddMageNonCollect(cards);

    AddPaladin(cards);
    AddPaladinNonCollect(cards);

    AddPriest(cards);
    AddPriestNonCollect(cards);

    AddRogue(cards);
    AddRogueNonCollect(cards);

    AddShaman(cards);
    AddShamanNonCollect(cards);

    AddWarlock(cards);
    AddWarlockNonCollect(cards);

    AddWarrior(cards);
    AddWarriorNonCollect(cards);

    AddNeutral(cards);
    AddNeutralNonCollect(cards);
}
}  // namespace Hearthstonepp
