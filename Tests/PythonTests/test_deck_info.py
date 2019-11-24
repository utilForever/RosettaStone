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
    mage_cards = pyRosetta.Cards.find_card_by_class(pyRosetta.CardClass.HUNTER)

    deck = pyRosetta.DeckInfo('Ice Magician', pyRosetta.CardClass.MAGE)
    deck.show_card_list()
    assert deck.add_card(mage_cards[0].id, 1) == True
