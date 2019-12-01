"""
Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

We are making my contributions/submissions to this project solely in our
personal capacity and are not conveying any rights to any intellectual
property of any third parties.
"""

import pyRosetta

def test_constructors():
    deck1 = pyRosetta.DeckInfo()

    assert deck1.get_name() == 'Empty'
    assert deck1.get_class() == pyRosetta.CardClass.INVALID
    assert deck1.get_num_of_cards() == 0

    deck2 = pyRosetta.DeckInfo('Ice Magician', pyRosetta.CardClass.MAGE)
    
    assert deck2.get_name() == 'Ice Magician'
    assert deck2.get_class() == pyRosetta.CardClass.MAGE
    assert deck2.get_num_of_cards() == 0

def test_card_control():
    druid_cards = pyRosetta.Cards.find_card_by_class(pyRosetta.CardClass.DRUID)
    mage_cards = pyRosetta.Cards.find_card_by_class(pyRosetta.CardClass.MAGE)

    deck = pyRosetta.DeckInfo('Ice Magician', pyRosetta.CardClass.MAGE)
    deck.show_card_list()
    assert deck.add_card(mage_cards[0].id, 1) == True
    assert deck.get_card(0)[1] == 1
    assert deck.add_card(mage_cards[0].id, 1) == True
    assert deck.get_card(0)[1] == 2
    assert deck.add_card(mage_cards[0].id, 1) == False
    assert deck.add_card(mage_cards[1].id, 3) == False
    assert deck.add_card(druid_cards[0].id, 1) == False
    deck.show_card_list()

    assert deck.get_unique_num_of_cards() == 1
    assert deck.get_num_of_cards() == 2

    assert deck.get_card(0)[1] == 2
    assert deck.delete_card(mage_cards[0].id, 1) == True
    assert deck.delete_card(mage_cards[0].id, 4) == False
    assert deck.delete_card(druid_cards[0].id, 1) == False
    deck.show_card_list()
