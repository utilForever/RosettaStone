"""
Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

We are making my contributions/submissions to this project solely in our
personal capacity and are not conveying any rights to any intellectual
property of any third parties.
"""

import pyRosetta

def test_constructors():
    deck1 = pyRosetta.Deck()

    assert deck1.deck_class() == pyRosetta.CardClass.INVALID
    assert deck1.num_of_cards() == 0

    deck2 = pyRosetta.Deck(pyRosetta.FormatType.STANDARD, pyRosetta.CardClass.MAGE)

    assert deck2.format_type() == pyRosetta.FormatType.STANDARD
    assert deck2.deck_class() == pyRosetta.CardClass.MAGE
    assert deck2.num_of_cards() == 0

def test_card_control():
    druid_cards = pyRosetta.Cards.find_card_by_class(pyRosetta.CardClass.DRUID)
    mage_cards = pyRosetta.Cards.find_card_by_class(pyRosetta.CardClass.MAGE)

    deck = pyRosetta.Deck(pyRosetta.FormatType.WILD, pyRosetta.CardClass.MAGE)
    assert deck.add_card(mage_cards[0].id, 1) is True
    assert deck.card(0)[1] == 1
    assert deck.add_card(mage_cards[0].id, 1) is True
    assert deck.card(0)[1] == 2
    assert deck.add_card(mage_cards[0].id, 1) is False
    assert deck.add_card(mage_cards[1].id, 3) is False
    assert deck.add_card(druid_cards[0].id, 1) is False

    assert deck.unique_num_of_cards() == 1
    assert deck.num_of_cards() == 2

    assert deck.card(0)[1] == 2
    assert deck.delete_card(mage_cards[0].id, 1) is True
    assert deck.delete_card(mage_cards[0].id, 4) is False
    assert deck.delete_card(druid_cards[0].id, 1) is False

def test_num_card_in_deck():
    mage_cards = pyRosetta.Cards.find_card_by_class(pyRosetta.CardClass.MAGE)

    deck = pyRosetta.Deck(pyRosetta.FormatType.WILD, pyRosetta.CardClass.MAGE)
    deck.add_card(mage_cards[0].id, 1)

    deck_cards = deck.cards()
    assert deck_cards[0].id == mage_cards[0].id

def test_card_ids():
    INKEEPER_EXPERT_WARLOCK = 'AAEBAfqUAwAPMJMB3ALVA9AE9wTOBtwGkgeeB/sHsQjCCMQI9ggA'
    deck = pyRosetta.DeckCode.decode(INKEEPER_EXPERT_WARLOCK).card_ids()

    assert len(deck) == 30

    for card_id in deck:
        card = pyRosetta.Cards.find_card_by_id(card_id)

        assert (card.card_class() == pyRosetta.CardClass.WARLOCK or card.card_class() == pyRosetta.CardClass.NEUTRAL) is True
