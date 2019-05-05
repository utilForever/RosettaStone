"""
Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

We are making my contributions/submissions to this project solely in our
personal capacity and are not conveying any rights to any intellectual
property of any third parties.
"""

import pyRosetta

def test_init():
	card1 = pyRosetta.Card()
	card1.id = "cardTest1"
	card1.name = "card1"
	card1.text = "this is test card1"

	gameTag = dict()
	gameTag[pyRosetta.GameTag.RARITY] = int(pyRosetta.Rarity.COMMON)
	gameTag[pyRosetta.GameTag.FACTION] = int(pyRosetta.Faction.NEUTRAL)
	gameTag[pyRosetta.GameTag.CARD_SET] = int(pyRosetta.CardSet.NONE)
	gameTag[pyRosetta.GameTag.CLASS] = int(pyRosetta.CardClass.NEUTRAL)
	gameTag[pyRosetta.GameTag.CARDTYPE] = int(pyRosetta.CardType.MINION)
	gameTag[pyRosetta.GameTag.CARDRACE] = int(pyRosetta.Race.DRAGON)
	gameTag[pyRosetta.GameTag.COLLECTIBLE] = 1
	gameTag[pyRosetta.GameTag.COST] = 1
	card1.game_tags = gameTag

	card1.initialize()

	card2 = pyRosetta.Card()
	card2.id = "cardTest2"
	card2.name = "card2"
	card2.text = "this is test card2"

	gameTag = {}
	gameTag[pyRosetta.GameTag.RARITY] = int(pyRosetta.Rarity.LEGENDARY)
	gameTag[pyRosetta.GameTag.FACTION] = int(pyRosetta.Faction.NEUTRAL)
	gameTag[pyRosetta.GameTag.CARD_SET] = int(pyRosetta.CardSet.NONE)
	gameTag[pyRosetta.GameTag.CLASS] = int(pyRosetta.CardClass.NEUTRAL)
	gameTag[pyRosetta.GameTag.CARDTYPE] = int(pyRosetta.CardType.MINION)
	gameTag[pyRosetta.GameTag.CARDRACE] = int(pyRosetta.Race.DRAGON)
	gameTag[pyRosetta.GameTag.COLLECTIBLE] = 1
	gameTag[pyRosetta.GameTag.COST] = 1
	card2.game_tags = gameTag

	card2.initialize()

	assert card1.id == "cardTest1"
	assert card1.name == "card1"
	assert card1.text == "this is test card1"
	assert pyRosetta.Rarity(card1.rarity()) == pyRosetta.Rarity.COMMON
	assert pyRosetta.Faction(card1.faction()) == pyRosetta.Faction.NEUTRAL
	assert pyRosetta.CardSet(card1.card_set()) == pyRosetta.CardSet.NONE
	assert pyRosetta.CardClass(card1.card_class()) == pyRosetta.CardClass.NEUTRAL
	assert pyRosetta.CardType(card1.card_type()) == pyRosetta.CardType.MINION
	assert pyRosetta.Race(card1.race()) == pyRosetta.Race.DRAGON
	assert card1.game_tags[pyRosetta.GameTag.COLLECTIBLE] == 1
	assert card1.game_tags[pyRosetta.GameTag.COST] == 1
	assert card1.max_allowed_in_deck == 2

	assert card2.id == "cardTest2"
	assert card2.name == "card2"
	assert card2.text == "this is test card2"
	assert pyRosetta.Rarity(card2.rarity()) == pyRosetta.Rarity.LEGENDARY
	assert pyRosetta.Faction(card2.faction()) == pyRosetta.Faction.NEUTRAL
	assert pyRosetta.CardSet(card2.card_set()) == pyRosetta.CardSet.NONE
	assert pyRosetta.CardClass(card2.card_class()) == pyRosetta.CardClass.NEUTRAL
	assert pyRosetta.CardType(card2.card_type()) == pyRosetta.CardType.MINION
	assert pyRosetta.Race(card2.race()) == pyRosetta.Race.DRAGON
	assert card2.game_tags[pyRosetta.GameTag.COLLECTIBLE] == 1
	assert card2.game_tags[pyRosetta.GameTag.COST] == 1
	assert card2.max_allowed_in_deck == 1