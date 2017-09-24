/*************************************************************************
> File Name: CardLoader.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Card loader that loads data from cards.json.
> Created Time: 2017/08/13
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Enums/StringToEnums.h>
#include <Loaders/CardLoader.h>
#include <Models/Card.h>
#include <Models/Entities/Enchantment.h>
#include <Models/Entities/Hero.h>
#include <Models/Entities/HeroPower.h>
#include <Models/Entities/Minion.h>
#include <Models/Entities/Spell.h>
#include <Models/Entities/Weapon.h>

#include <fstream>

namespace Hearthstonepp
{
	void CardLoader::Load()
	{
		// Read card data from JSON file
		std::ifstream cardFile("cards.json");
		json j;

		if (!cardFile.is_open())
		{
			throw std::runtime_error("Can't open cards.json");
		}

		cardFile >> j;

		Parse(j);

		cardFile.close();
	}

	void CardLoader::Parse(json& j)
	{
		std::vector<Card*> cards;
		cards.reserve(j.size());

		Card* c = nullptr;

		for (auto& card : j)
		{
			c = nullptr;

			if (card["type"] == "HERO")
			{
				c = new Hero();
			}
			else if (card["type"] == "MINION")
			{
				c = new Minion();
			}
			else if (card["type"] == "SPELL")
			{
				c = new Spell();
			}
			else if (card["type"] == "ENCHANTMENT")
			{
				c = new Enchantment();
			}
			else if (card["type"] == "WEAPON")
			{
				c = new Weapon();
			}
			else if (card["type"] == "HERO_POWER")
			{
				c = new HeroPower();
			}
			else
			{
				std::cout << "Invalid card type: " << card["type"] << std::endl;
				continue;
			}

			c->ID = std::move(card["id"].get<std::string>());
			c->rarity = card["rarity"].is_null() ? Rarity::FREE : std::move(ConverterFromStringToRarity.at(card["rarity"].get<std::string>()));
			c->faction = card["faction"].is_null() ? Faction::NEUTRAL : std::move(ConverterFromStringToFaction.at(card["faction"].get<std::string>()));
			c->cardSet = card["set"].is_null() ? CardSet::NONE : std::move(ConverterFromStringToCardSet.at(card["set"].get<std::string>()));
			c->cardClass = card["cardClass"].is_null() ? CardClass::NEUTRAL : std::move(ConvertFromStringToCardClass.at(card["cardClass"].get<std::string>()));
			c->cardType = card["type"].is_null() ? CardType::INVALID : std::move(ConverterFromStringToCardType.at(card["type"].get<std::string>()));
			c->race = card["race"].is_null() ? Race::INVALID : std::move(ConverterFromStringToRace.at(card["race"].get<std::string>()));

			c->name = card["name"].is_null() ? "" : std::move(card["name"]["enUS"].get<std::string>());
			c->text = card["text"].is_null() ? "" : std::move(card["text"]["enUS"].get<std::string>());

			c->collectible = card["collectible"].is_null() ? false : card["collectible"].get<bool>();
			c->cost = card["cost"].is_null() ? -1 : card["cost"].get<int>();
			c->attack = card["attack"].is_null() ? -1 : card["attack"].get<int>();
			c->health = card["health"].is_null() ? -1 : card["health"].get<int>();
			c->durability = card["durability"].is_null() ? -1 : card["durability"].get<int>();

			for (auto& mechanic : card["mechanics"])
			{
				c->mechanics.emplace_back(std::move(ConverterFromStringToGameTag.at(mechanic.get<std::string>())));
			}

			for (auto iter = card["playRequirements"].begin(); iter != card["playRequirements"].end(); ++iter)
			{
				c->playRequirements.try_emplace(std::move(ConverterFromStringToPlayReq.at(iter.key())), iter.value().get<int>());
			}

			for (auto& entourage : card["entourage"])
			{
				c->entourages.emplace_back(std::move(entourage.get<std::string>()));
			}

			cards.push_back(c);
		}
	}
}