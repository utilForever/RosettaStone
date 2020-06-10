"""
Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

We are making my contributions/submissions to this project solely in our
personal capacity and are not conveying any rights to any intellectual
property of any third parties.
"""

import pyRosetta

def test_all_cards():
	cards = pyRosetta.Cards.all_cards()

	assert len(cards) == pyRosetta.NUM_ALL_CARDS

def test_all_standard_cards():
	cards = pyRosetta.Cards.all_standard_cards()

	for card in cards:
		assert card.is_standard_set() is True

def test_all_wild_cards():
	cards = pyRosetta.Cards.all_wild_cards()

	for card in cards:
		assert card.is_wild_set() is True

def test_find_card_by_id():
	card1 = pyRosetta.Cards.find_card_by_id('AT_001')
	card2 = pyRosetta.Cards.find_card_by_id('')

	assert card1.id == 'AT_001'
	assert card2.id == ''

def test_find_card_by_dbf_id():
	card1 = pyRosetta.Cards.find_card_by_dbf_id(559)
	card2 = pyRosetta.Cards.find_card_by_dbf_id(-999)

	assert card1.dbf_id == 559
	assert card1.id == 'EX1_116'
	assert card2.dbf_id == 0
	assert card2.id == ''

def test_find_card_by_rarity():
	cards1 = pyRosetta.Cards.find_card_by_rarity(pyRosetta.Rarity.COMMON)
	cards2 = pyRosetta.Cards.find_card_by_rarity(pyRosetta.Rarity.RARE)
	cards3 = pyRosetta.Cards.find_card_by_rarity(pyRosetta.Rarity.EPIC)
	cards4 = pyRosetta.Cards.find_card_by_rarity(pyRosetta.Rarity.LEGENDARY)
	cards5 = pyRosetta.Cards.find_card_by_rarity(pyRosetta.Rarity.FREE)
	cards6 = pyRosetta.Cards.find_card_by_rarity(pyRosetta.Rarity.INVALID)

	assert cards1[0].rarity() == pyRosetta.Rarity.COMMON
	assert cards2[0].rarity() == pyRosetta.Rarity.RARE
	assert cards3[0].rarity() == pyRosetta.Rarity.EPIC
	assert cards4[0].rarity() == pyRosetta.Rarity.LEGENDARY
	assert cards5[0].rarity() == pyRosetta.Rarity.FREE
	assert cards6[0].rarity() == pyRosetta.Rarity.INVALID

def test_find_card_by_class():
	cards1 = pyRosetta.Cards.find_card_by_class(pyRosetta.CardClass.DEATHKNIGHT)
	cards2 = pyRosetta.Cards.find_card_by_class(pyRosetta.CardClass.DREAM)
	cards3 = pyRosetta.Cards.find_card_by_class(pyRosetta.CardClass.DRUID)
	cards4 = pyRosetta.Cards.find_card_by_class(pyRosetta.CardClass.HUNTER)
	cards5 = pyRosetta.Cards.find_card_by_class(pyRosetta.CardClass.MAGE)
	cards6 = pyRosetta.Cards.find_card_by_class(pyRosetta.CardClass.NEUTRAL)
	cards7 = pyRosetta.Cards.find_card_by_class(pyRosetta.CardClass.PALADIN)
	cards8 = pyRosetta.Cards.find_card_by_class(pyRosetta.CardClass.PRIEST)
	cards9 = pyRosetta.Cards.find_card_by_class(pyRosetta.CardClass.INVALID)

	assert cards1[0].card_class() == pyRosetta.CardClass.DEATHKNIGHT
	assert cards2[0].card_class() == pyRosetta.CardClass.DREAM
	assert cards3[0].card_class() == pyRosetta.CardClass.DRUID
	assert cards4[0].card_class() == pyRosetta.CardClass.HUNTER
	assert cards5[0].card_class() == pyRosetta.CardClass.MAGE
	assert cards6[0].card_class() == pyRosetta.CardClass.NEUTRAL
	assert cards7[0].card_class() == pyRosetta.CardClass.PALADIN
	assert cards8[0].card_class() == pyRosetta.CardClass.PRIEST
	assert cards9[0].card_class() == pyRosetta.CardClass.INVALID

def test_find_card_by_set():
	cards1 = pyRosetta.Cards.find_card_by_set(pyRosetta.CardSet.CORE)
	cards2 = pyRosetta.Cards.find_card_by_set(pyRosetta.CardSet.EXPERT1)
	cards3 = pyRosetta.Cards.find_card_by_set(pyRosetta.CardSet.HOF)
	cards4 = pyRosetta.Cards.find_card_by_set(pyRosetta.CardSet.NAXX)
	cards5 = pyRosetta.Cards.find_card_by_set(pyRosetta.CardSet.GVG)
	cards6 = pyRosetta.Cards.find_card_by_set(pyRosetta.CardSet.BRM)
	cards7 = pyRosetta.Cards.find_card_by_set(pyRosetta.CardSet.TGT)
	cards8 = pyRosetta.Cards.find_card_by_set(pyRosetta.CardSet.LOE)
	cards9 = pyRosetta.Cards.find_card_by_set(pyRosetta.CardSet.OG)
	cards10 = pyRosetta.Cards.find_card_by_set(pyRosetta.CardSet.KARA)
	cards11 = pyRosetta.Cards.find_card_by_set(pyRosetta.CardSet.GANGS)
	cards12 = pyRosetta.Cards.find_card_by_set(pyRosetta.CardSet.UNGORO)
	cards13 = pyRosetta.Cards.find_card_by_set(pyRosetta.CardSet.ICECROWN)
	cards14 = pyRosetta.Cards.find_card_by_set(pyRosetta.CardSet.LOOTAPALOOZA)
	cards15 = pyRosetta.Cards.find_card_by_set(pyRosetta.CardSet.GILNEAS)
	cards16 = pyRosetta.Cards.find_card_by_set(pyRosetta.CardSet.BOOMSDAY)
	cards17 = pyRosetta.Cards.find_card_by_set(pyRosetta.CardSet.INVALID)

	assert cards1[0].card_set() == pyRosetta.CardSet.CORE
	assert cards2[0].card_set() == pyRosetta.CardSet.EXPERT1
	assert cards3[0].card_set() == pyRosetta.CardSet.HOF
	assert cards4[0].card_set() == pyRosetta.CardSet.NAXX
	assert cards5[0].card_set() == pyRosetta.CardSet.GVG
	assert cards6[0].card_set() == pyRosetta.CardSet.BRM
	assert cards7[0].card_set() == pyRosetta.CardSet.TGT
	assert cards8[0].card_set() == pyRosetta.CardSet.LOE
	assert cards9[0].card_set() == pyRosetta.CardSet.OG
	assert cards10[0].card_set() == pyRosetta.CardSet.KARA
	assert cards11[0].card_set() == pyRosetta.CardSet.GANGS
	assert cards12[0].card_set() == pyRosetta.CardSet.UNGORO
	assert cards13[0].card_set() == pyRosetta.CardSet.ICECROWN
	assert cards14[0].card_set() == pyRosetta.CardSet.LOOTAPALOOZA
	assert cards15[0].card_set() == pyRosetta.CardSet.GILNEAS
	assert cards16[0].card_set() == pyRosetta.CardSet.BOOMSDAY
	assert not cards17

def test_find_card_by_type():
	cards1 = pyRosetta.Cards.find_card_by_type(pyRosetta.CardType.WEAPON)
	cards2 = pyRosetta.Cards.find_card_by_type(pyRosetta.CardType.GAME)
	cards3 = pyRosetta.Cards.find_card_by_type(pyRosetta.CardType.HERO)
	cards4 = pyRosetta.Cards.find_card_by_type(pyRosetta.CardType.HERO_POWER)
	cards5 = pyRosetta.Cards.find_card_by_type(pyRosetta.CardType.ENCHANTMENT)
	cards6 = pyRosetta.Cards.find_card_by_type(pyRosetta.CardType.ITEM)
	cards7 = pyRosetta.Cards.find_card_by_type(pyRosetta.CardType.MINION)
	cards8 = pyRosetta.Cards.find_card_by_type(pyRosetta.CardType.PLAYER)
	cards9 = pyRosetta.Cards.find_card_by_type(pyRosetta.CardType.SPELL)
	cards10 = pyRosetta.Cards.find_card_by_type(pyRosetta.CardType.TOKEN)
	cards11 = pyRosetta.Cards.find_card_by_type(pyRosetta.CardType.INVALID)

	assert cards1[0].card_type() == pyRosetta.CardType.WEAPON
	assert cards3[0].card_type() == pyRosetta.CardType.HERO
	assert cards4[0].card_type() == pyRosetta.CardType.HERO_POWER
	assert cards5[0].card_type() == pyRosetta.CardType.ENCHANTMENT
	assert cards7[0].card_type() == pyRosetta.CardType.MINION
	assert cards9[0].card_type() == pyRosetta.CardType.SPELL
	assert not cards2
	assert not cards6
	assert not cards8
	assert not cards10
	assert not cards11

def test_find_card_by_race():
	cards = pyRosetta.Cards.find_card_by_race(pyRosetta.Race.INVALID)

	assert cards
	pyRosetta.Cards.find_card_by_race(pyRosetta.Race.ALL)

def test_find_card_by_name():
	card1 = pyRosetta.Cards.find_card_by_name('Flame Lance')
	assert card1.name == 'Flame Lance'

	card2 = pyRosetta.Cards.find_card_by_name('Invalid')
	assert not card2.name

def test_find_card_by_cost():
	cards1 = pyRosetta.Cards.find_card_by_cost(0, 1)
	cards2 = pyRosetta.Cards.find_card_by_cost(2, 1)

	assert cards1
	assert not cards2

def test_find_card_by_attack():
	cards1 = pyRosetta.Cards.find_card_by_attack(0, 1)
	cards2 = pyRosetta.Cards.find_card_by_attack(2, 1)

	assert cards1
	assert not cards2

def test_find_card_by_health():
	cards1 = pyRosetta.Cards.find_card_by_health(0, 1)
	cards2 = pyRosetta.Cards.find_card_by_health(2, 1)

	assert cards1
	assert not cards2

def test_find_card_by_spell_power():
	cards1 = pyRosetta.Cards.find_card_by_spell_power(1, 1)
	cards2 = pyRosetta.Cards.find_card_by_spell_power(2, 1)

	assert cards1
	assert not cards2

def test_find_card_by_game_tag():
	tags1 = [pyRosetta.GameTag.CANT_ATTACK]
	tags2 = []

	cards1 = pyRosetta.Cards.find_card_by_game_tag(tags1)
	cards2 = pyRosetta.Cards.find_card_by_game_tag(tags2)
	game_tags = cards1[0].game_tags

	assert pyRosetta.GameTag.CANT_ATTACK in game_tags
	assert not cards2

def test_hero_card():
	assert pyRosetta.Cards.find_card_by_id('HERO_06').id == pyRosetta.Cards.hero_card(pyRosetta.CardClass.DRUID).id
	assert pyRosetta.Cards.find_card_by_id('HERO_05').id == pyRosetta.Cards.hero_card(pyRosetta.CardClass.HUNTER).id
	assert pyRosetta.Cards.find_card_by_id('HERO_08').id == pyRosetta.Cards.hero_card(pyRosetta.CardClass.MAGE).id
	assert pyRosetta.Cards.find_card_by_id('HERO_04').id == pyRosetta.Cards.hero_card(pyRosetta.CardClass.PALADIN).id
	assert pyRosetta.Cards.find_card_by_id('HERO_09').id == pyRosetta.Cards.hero_card(pyRosetta.CardClass.PRIEST).id
	assert pyRosetta.Cards.find_card_by_id('HERO_03').id == pyRosetta.Cards.hero_card(pyRosetta.CardClass.ROGUE).id
	assert pyRosetta.Cards.find_card_by_id('HERO_02').id == pyRosetta.Cards.hero_card(pyRosetta.CardClass.SHAMAN).id
	assert pyRosetta.Cards.find_card_by_id('HERO_07').id == pyRosetta.Cards.hero_card(pyRosetta.CardClass.WARLOCK).id
	assert pyRosetta.Cards.find_card_by_id('HERO_01').id == pyRosetta.Cards.hero_card(pyRosetta.CardClass.WARRIOR).id
	assert pyRosetta.Cards.find_card_by_id('HERO_10').id == pyRosetta.Cards.hero_card(pyRosetta.CardClass.DEMONHUNTER).id
	assert pyRosetta.Cards.hero_card(pyRosetta.CardClass.DEATHKNIGHT).id == ''

def test_default_hero_power():
	assert pyRosetta.Cards.find_card_by_id('HERO_06bp').id == pyRosetta.Cards.default_hero_power(pyRosetta.CardClass.DRUID).id
	assert pyRosetta.Cards.find_card_by_id('HERO_05bp').id == pyRosetta.Cards.default_hero_power(pyRosetta.CardClass.HUNTER).id
	assert pyRosetta.Cards.find_card_by_id('HERO_08bp').id == pyRosetta.Cards.default_hero_power(pyRosetta.CardClass.MAGE).id
	assert pyRosetta.Cards.find_card_by_id('HERO_04bp').id == pyRosetta.Cards.default_hero_power(pyRosetta.CardClass.PALADIN).id
	assert pyRosetta.Cards.find_card_by_id('HERO_09bp').id == pyRosetta.Cards.default_hero_power(pyRosetta.CardClass.PRIEST).id
	assert pyRosetta.Cards.find_card_by_id('HERO_03bp').id == pyRosetta.Cards.default_hero_power(pyRosetta.CardClass.ROGUE).id
	assert pyRosetta.Cards.find_card_by_id('HERO_02bp').id == pyRosetta.Cards.default_hero_power(pyRosetta.CardClass.SHAMAN).id
	assert pyRosetta.Cards.find_card_by_id('HERO_07bp').id == pyRosetta.Cards.default_hero_power(pyRosetta.CardClass.WARLOCK).id
	assert pyRosetta.Cards.find_card_by_id('HERO_01bp').id == pyRosetta.Cards.default_hero_power(pyRosetta.CardClass.WARRIOR).id
	assert pyRosetta.Cards.find_card_by_id('HERO_10bp').id == pyRosetta.Cards.default_hero_power(pyRosetta.CardClass.DEMONHUNTER).id
	assert pyRosetta.Cards.default_hero_power(pyRosetta.CardClass.DEATHKNIGHT).id == ''
