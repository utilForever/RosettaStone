"""
Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

We are making my contributions/submissions to this project solely in our
personal capacity and are not conveying any rights to any intellectual
property of any third parties.
"""

import pyRosetta

def test_constructors():
    player1 = pyRosetta.AccountInfo()

    assert player1.email() == 'anonymous@gmail.com'
    assert player1.nickname() == 'Anonymous'

    player2 = pyRosetta.AccountInfo('1', 'name1')

    assert player2.email() == '1'
    assert player2.nickname() == 'name1'

    player3 = pyRosetta.AccountInfo('2', 'name2', [])

    assert player3.email() == '2'
    assert player3.nickname() == 'name2'
    assert player3.num_of_deck() == 0

def test_deck_control():
    player = pyRosetta.AccountInfo()

    player.show_deck_list()
    assert player.create_deck('deck1', pyRosetta.CardClass.INVALID) is False

    player.create_deck('deck2', pyRosetta.CardClass.DREAM)
    player.create_deck('deck3', pyRosetta.CardClass.DRUID)
    
    assert player.num_of_deck() == 2
    player.show_deck_list()

    player.delete_deck(0)
    assert player.num_of_deck() == 1
    assert player.deck(0).name() == 'deck3'

    assert player.num_of_deck() == 1
