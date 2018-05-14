/*************************************************************************
> File Name: CardLoader.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Card loader that loads data from cards.json.
> Created Time: 2017/08/13
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Loaders/CardLoader.h>
#include <Models/Entities/Enchantment.h>
#include <Models/Entities/Hero.h>
#include <Models/Entities/HeroPower.h>
#include <Models/Entities/Minion.h>
#include <Models/Entities/Spell.h>
#include <Models/Entities/Weapon.h>

#include <fstream>

namespace Hearthstonepp
{
	std::vector<Card*> CardLoader::Load() const
	{
		// Read card data from JSON file
		std::ifstream cardFile(RESOURCES_DIR "cards.json");
		json j;

		if (!cardFile.is_open())
		{
			throw std::runtime_error("Can't open cards.json");
		}

		cardFile >> j;

		std::vector<Card*> cards;
		cards.reserve(j.size());

		for (auto& card : j)
		{
			const std::string id = card["id"].get<std::string>();
			const Rarity rarity = card["rarity"].is_null() ? +Rarity::FREE : std::move(Rarity::_from_string(card["rarity"].get<std::string>().c_str()));
			const Faction faction = card["faction"].is_null() ? +Faction::NEUTRAL : std::move(Faction::_from_string(card["faction"].get<std::string>().c_str()));
			const CardSet cardSet = card["set"].is_null() ? +CardSet::NONE : std::move(CardSet::_from_string(card["set"].get<std::string>().c_str()));
			const CardClass cardClass = card["cardClass"].is_null() ? +CardClass::NEUTRAL : std::move(CardClass::_from_string(card["cardClass"].get<std::string>().c_str()));
			const CardType cardType = card["type"].is_null() ? +CardType::INVALID : std::move(CardType::_from_string(card["type"].get<std::string>().c_str()));
			const Race race = card["race"].is_null() ? +Race::INVALID : std::move(Race::_from_string(card["race"].get<std::string>().c_str()));

			const std::string name = card["name"].is_null() ? "" : card["name"]["enUS"].get<std::string>();
			const std::string text = card["text"].is_null() ? "" : card["text"]["enUS"].get<std::string>();

			const bool collectible = card["collectible"].is_null() ? false : card["collectible"].get<bool>();
			const int cost = card["cost"].is_null() ? -1 : card["cost"].get<int>();
			const int attack = card["attack"].is_null() ? -1 : card["attack"].get<int>();
			const int health = card["health"].is_null() ? -1 : card["health"].get<int>();
			const int durability = card["durability"].is_null() ? -1 : card["durability"].get<int>();

			std::vector<GameTag> mechanics;
			for (auto& mechanic : card["mechanics"])
			{
				mechanics.emplace_back(std::move(GameTag::_from_string(mechanic.get<std::string>().c_str())));
			}

			std::map<PlayReq, int> playRequirements;
			for (auto iter = card["playRequirements"].begin(); iter != card["playRequirements"].end(); ++iter)
			{
				playRequirements.try_emplace(std::move(PlayReq::_from_string(iter.key().c_str())), iter.value().get<int>());
			}

			std::vector<std::string> entourages;
			for (auto& entourage : card["entourage"])
			{
				entourages.emplace_back(entourage.get<std::string>());
			}

			Card* c;
			switch (cardType)
			{
			case CardType::HERO:
				c = new Hero(
					id, rarity, faction, cardSet, cardClass, cardType, race,
					name, text, collectible, cost, attack, health, durability,
					mechanics, playRequirements, entourages);
				break;
			case CardType::MINION:
				c = new Minion(
					id, rarity, faction, cardSet, cardClass, cardType, race,
					name, text, collectible, cost, attack, health, durability,
					mechanics, playRequirements, entourages);
				break;
			case CardType::SPELL:
				c = new Spell(
					id, rarity, faction, cardSet, cardClass, cardType, race,
					name, text, collectible, cost, attack, health, durability,
					mechanics, playRequirements, entourages);
				break;
			case CardType::ENCHANTMENT:
				c = new Enchantment(
					id, rarity, faction, cardSet, cardClass, cardType, race,
					name, text, collectible, cost, attack, health, durability,
					mechanics, playRequirements, entourages);
				break;
			case CardType::WEAPON:
				c = new Weapon(
					id, rarity, faction, cardSet, cardClass, cardType, race,
					name, text, collectible, cost, attack, health, durability,
					mechanics, playRequirements, entourages);
				break;
			case CardType::HERO_POWER:
				c = new HeroPower(
					id, rarity, faction, cardSet, cardClass, cardType, race,
					name, text, collectible, cost, attack, health, durability,
					mechanics, playRequirements, entourages);
				break;
			default:
				// TODO: Log invalid card type
				break;
			}

			cards.emplace_back(c);
		}

		cardFile.close();

		return cards;
	}
}