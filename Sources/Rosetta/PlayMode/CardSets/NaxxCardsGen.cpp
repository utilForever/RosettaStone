// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/NaxxCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void NaxxCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void NaxxCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void NaxxCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - DRUID
    // [FP1_019] Poison Seeds - COST:4
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: Destroy all minions and summon 2/2 Treants
    //       to replace them.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<CountTask>(EntityType::MINIONS));
    cardDef.power.AddPowerTask(
        std::make_shared<CountTask>(EntityType::ENEMY_MINIONS, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::ALL_MINIONS, true));
    cardDef.power.AddPowerTask(std::make_shared<EnqueueNumberTask>(
        TaskList{ std::make_shared<SummonTask>("FP1_019t") }));
    cardDef.power.AddPowerTask(std::make_shared<MathMultiplyTask>(0));
    cardDef.power.AddPowerTask(
        std::make_shared<MathNumberIndexTask>(0, 1, MathOperation::ADD));
    cardDef.power.AddPowerTask(std::make_shared<EnqueueNumberTask>(
        TaskList{ std::make_shared<SummonOpTask>("FP1_019t") }));
    cards.emplace("FP1_019", cardDef);
}

void NaxxCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - DRUID
    // [FP1_019t] Treant (*) - COST:1 [ATK:2/HP:2]
    // - Set: Naxx
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("FP1_019t", cardDef);
}

void NaxxCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - HUNTER
    // [FP1_011] Webspinner - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a random Beast card
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<RandomMinionTask>(
        TagValues{ { GameTag::CARDRACE, static_cast<int>(Race::BEAST),
                     RelaSign::EQ } }));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("FP1_011", cardDef);
}

void NaxxCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void NaxxCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------- SPELL - MAGE
    // [FP1_018] Duplicate - COST:3
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When a friendly minion dies,
    //       put 2 copies of it into your hand.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DEATH));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsHandNotFull())
    };
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(TaskList{
        std::make_shared<CopyTask>(EntityType::TARGET, ZoneType::HAND, 2) });
    cards.emplace("FP1_018", cardDef);
}

void NaxxCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void NaxxCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - PALADIN
    // [FP1_020] Avenge - COST:1
    // - Set: Naxx, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When one of your minions dies,
    //       give a random friendly minion +3/+2.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DEATH));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsFieldCount(2, RelaSign::GEQ)) };
    cardDef.power.GetTrigger()->tasks = { ComplexTask::ActivateSecret(
        ComplexTask::GiveBuffToRandomMinionInField("FP1_020e")) };
    cards.emplace("FP1_020", cardDef);
}

void NaxxCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [FP1_020e] Vengeance (*) - COST:0
    // - Set: Naxx
    // --------------------------------------------------------
    // Text: +3/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("FP1_020e"));
    cards.emplace("FP1_020e", cardDef);
}

void NaxxCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - PRIEST
    // [FP1_023] Dark Cultist - COST:3 [ATK:3/HP:4]
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give a random friendly minion
    //       +3 Health.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        ComplexTask::GiveBuffToRandomMinionInField("FP1_023e"));
    cards.emplace("FP1_023", cardDef);
}

void NaxxCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [FP1_023e] Power of the Ziggurat (*) - COST:0
    // - Set: Naxx
    // --------------------------------------------------------
    // Text: +3 Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("FP1_023e"));
    cards.emplace("FP1_023e", cardDef);
}

void NaxxCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - ROGUE
    // [FP1_026] Anub'ar Ambusher - COST:4 [ATK:5/HP:5]
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Return a random friendly minion
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::MINIONS, 1));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<ReturnHandTask>(EntityType::STACK));
    cards.emplace("FP1_026", cardDef);
}

void NaxxCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void NaxxCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - SHAMAN
    // [FP1_025] Reincarnate - COST:2
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: Destroy a minion,
    //       then return it to life with full Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET, true));
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::TARGET, ZoneType::PLAY));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("FP1_025", cardDef);
}

void NaxxCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void NaxxCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - WARLOCK
    // [FP1_022] Voidcaller - COST:4 [ATK:3/HP:4]
    // - Race: Demon, Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Put a random Demon
    //       from your hand into the battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddDeathrattleTask(std::make_shared<FilterStackTask>(
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::DEMON)) }));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddDeathrattleTask(std::make_shared<SummonStackTask>(true));
    cards.emplace("FP1_022", cardDef);
}

void NaxxCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void NaxxCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- WEAPON - WARRIOR
    // [FP1_021] Death's Bite - COST:4 [ATK:4/HP:0]
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 1 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<DamageTask>(EntityType::ALL_MINIONS, 1));
    cards.emplace("FP1_021", cardDef);
}

void NaxxCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void NaxxCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_001] Zombie Chow - COST:1 [ATK:2/HP:3]
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Restore 5 Health to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<HealTask>(EntityType::ENEMY_HERO, 5));
    cards.emplace("FP1_001", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_002] Haunted Creeper - COST:2 [ATK:1/HP:2]
    // - Race: Beast, Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon two 1/1 Spectral Spiders.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("FP1_002t", 2, SummonSide::DEATHRATTLE));
    cards.emplace("FP1_002", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_003] Echoing Ooze - COST:2 [ATK:1/HP:2]
    // - Set: Naxx, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon an exact copy
    //       of this minion at the end of the turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::SOURCE, GameTag::CUSTOM_KEYWORD_EFFECT, 1));
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::SOURCE, GameTag::TAG_SCRIPT_DATA_NUM_1, 1));
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::SOURCE, GameTag::MULTIPLY_BUFF_VALUE, 1));
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsTagValue(GameTag::CUSTOM_KEYWORD_EFFECT, 1)) };
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<SetGameTagTask>(EntityType::SOURCE,
                                         GameTag::CUSTOM_KEYWORD_EFFECT, 0),
        std::make_shared<SummonCopyTask>(EntityType::SOURCE, false, false,
                                         SummonSide::RIGHT)
    };
    cardDef.power.GetTrigger()->removeAfterTriggered = true;
    cards.emplace("FP1_003", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_004] Mad Scientist - COST:2 [ATK:2/HP:2]
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Put a <b>Secret</b>
    //       from your deck into the battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(ComplexTask::CastSecretFromDeck());
    cards.emplace("FP1_004", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_005] Shade of Naxxramas - COST:3 [ATK:2/HP:2]
    // - Set: Naxx, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Stealth.</b>
    //       At the start of your turn, gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "FP1_005e", EntityType::SOURCE) };
    cards.emplace("FP1_005", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_007] Nerubian Egg - COST:2 [ATK:0/HP:2]
    // - Set: Naxx, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 4/4 Nerubian.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("FP1_007t", SummonSide::DEATHRATTLE));
    cards.emplace("FP1_007", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_008] Spectral Knight - COST:5 [ATK:4/HP:6]
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("FP1_008", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_009] Deathlord - COST:3 [ATK:2/HP:8]
    // - Set: Naxx, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt. Deathrattle:</b> Your opponent
    //       puts a minion from their deck into the battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(ComplexTask::SummonOpMinionFromDeck());
    cards.emplace("FP1_009", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_010] Maexxna - COST:6 [ATK:2/HP:8]
    // - Race: Beast, Set: Naxx, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - POISONOUS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("FP1_010", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_012] Sludge Belcher - COST:5 [ATK:3/HP:5]
    // - Set: Naxx, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt Deathrattle:</b> Summon a 1/2 Slime
    //       with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("FP1_012t", SummonSide::DEATHRATTLE));
    cards.emplace("FP1_012", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_013] Kel'Thuzad - COST:8 [ATK:6/HP:8]
    // - Set: Naxx, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of each turn,
    //       summon all friendly minions that died this turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        ComplexTask::SummonAllFriendlyDiedThisTurn()
    };
    cardDef.power.GetTrigger()->eitherTurn = true;
    cards.emplace("FP1_013", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_014] Stalagg - COST:5 [ATK:7/HP:4]
    // - Set: Naxx, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> If Feugen also died this game,
    //       summon Thaddius.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<FuncNumberTask>([](Playable* playable) {
            Player* player = playable->player;
            bool isFeugenDead = false;

            const auto curGraveyard = player->GetGraveyardZone();
            const auto opGraveyard = player->opponent->GetGraveyardZone();

            for (const auto& minion : curGraveyard->GetAll())
            {
                if (minion->card->id == "FP1_015" && minion->isDestroyed)
                {
                    isFeugenDead = true;
                    break;
                }
            }

            for (const auto& minion : opGraveyard->GetAll())
            {
                if (minion->card->id == "FP1_015" && minion->isDestroyed)
                {
                    isFeugenDead = true;
                    break;
                }
            }

            if (isFeugenDead && !player->GetFieldZone()->IsFull())
            {
                const auto thaddius = Entity::GetFromCard(
                    player, Cards::FindCardByID("FP1_014t"));
                Generic::Summon(dynamic_cast<Minion*>(thaddius), -1, playable);
            }

            return 0;
        }));
    cards.emplace("FP1_014", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_015] Feugen - COST:5 [ATK:4/HP:7]
    // - Set: Naxx, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> If Stalagg also died this game,
    //       summon Thaddius.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<FuncNumberTask>([](Playable* playable) {
            Player* player = playable->player;
            bool isFeugenDead = false;

            const auto curGraveyard = player->GetGraveyardZone();
            const auto opGraveyard = player->opponent->GetGraveyardZone();

            for (const auto& minion : curGraveyard->GetAll())
            {
                if (minion->card->id == "FP1_014" && minion->isDestroyed)
                {
                    isFeugenDead = true;
                    break;
                }
            }

            for (const auto& minion : opGraveyard->GetAll())
            {
                if (minion->card->id == "FP1_014" && minion->isDestroyed)
                {
                    isFeugenDead = true;
                    break;
                }
            }

            if (isFeugenDead && !player->GetFieldZone()->IsFull())
            {
                const auto thaddius = Entity::GetFromCard(
                    player, Cards::FindCardByID("FP1_014t"));
                Generic::Summon(dynamic_cast<Minion*>(thaddius), -1, playable);
            }

            return 0;
        }));
    cards.emplace("FP1_015", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_016] Wailing Soul - COST:4 [ATK:3/HP:5]
    // - Set: Naxx, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry: Silence</b> your other minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SilenceTask>(EntityType::MINIONS_NOSOURCE));
    cards.emplace("FP1_016", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_017] Nerub'ar Weblord - COST:2 [ATK:1/HP:4]
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: Minions with <b>Battlecry</b> cost (2) more.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::HANDS, EffectList{ Effects::AddCost(2) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsBattlecryCard());
    }
    cards.emplace("FP1_017", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_024] Unstable Ghoul - COST:2 [ATK:1/HP:3]
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>.
    //       <b>Deathrattle:</b> Deal 1 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<DamageTask>(EntityType::ALL_MINIONS, 1));
    cards.emplace("FP1_024", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_027] Stoneskin Gargoyle - COST:3 [ATK:1/HP:4]
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       restore this minion to full Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<HealFullTask>(
        EntityType::SOURCE) };
    cards.emplace("FP1_027", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_028] Undertaker - COST:1 [ATK:1/HP:2]
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever you summon a minion with <b>Deathrattle</b>,
    //       gain +1 Attack.
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::SUMMON));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions = { std::make_shared<SelfCondition>(
        SelfCondition::IsDeathrattleCard()) };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "FP1_028e", EntityType::SOURCE) };
    cards.emplace("FP1_028", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_029] Dancing Swords - COST:3 [ATK:4/HP:4]
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Your opponent draws a card.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<DrawOpTask>(1));
    cards.emplace("FP1_029", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_030] Loatheb - COST:5 [ATK:5/HP:5]
    // - Set: Naxx, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Enemy spells cost (5) more next turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "FP1_030e", EntityType::ENEMY_PLAYER));
    cards.emplace("FP1_030", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_031] Baron Rivendare - COST:4 [ATK:1/HP:7]
    // - Set: Naxx, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your minions trigger their <b>Deathrattles</b> twice.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::PLAYER, EffectList{ std::make_shared<Effect>(
                              GameTag::EXTRA_MINION_DEATHRATTLES_BASE,
                              EffectOperator::SET, 1) }));
    cards.emplace("FP1_031", cardDef);
}

void NaxxCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_002t] Spectral Spider (*) - COST:1 [ATK:1/HP:1]
    // - Set: Naxx
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("FP1_002t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [FP1_005e] Consume (*) - COST:0
    // - Set: Naxx
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Effects::AttackHealthN(1)));
    cards.emplace("FP1_005e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_006] Deathcharger (*) - COST:1 [ATK:2/HP:3]
    // - Set: Naxx
    // --------------------------------------------------------
    // Text: <b>Charge. Deathrattle:</b> Deal 3 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_007t] Nerubian (*) - COST:4 [ATK:4/HP:4]
    // - Set: Naxx
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("FP1_007t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_012t] Putrid Slime (*) - COST:1 [ATK:1/HP:2]
    // - Set: Naxx
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("FP1_012t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_014t] Thaddius (*) - COST:10 [ATK:11/HP:11]
    // - Set: Naxx
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("FP1_014t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [FP1_028e] Darkness Calls (*) - COST:0
    // - Set: Naxx
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::AttackN(1)));
    cards.emplace("FP1_028e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [FP1_030e] Necrotic Aura (*) - COST:0
    // - Set: Naxx
    // --------------------------------------------------------
    // Text: Your spells cost (5) more this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::ENEMY_HAND, EffectList{ Effects::AddCost(5) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsSpell());
        aura->removeTrigger = { TriggerType::TURN_END,
                                std::make_shared<SelfCondition>(
                                    SelfCondition::IsEnemyTurn()) };
    }
    cards.emplace("FP1_030e", cardDef);
}

void NaxxCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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
}  // namespace RosettaStone::PlayMode