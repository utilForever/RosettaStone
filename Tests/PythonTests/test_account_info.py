"""
Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

We are making my contributions/submissions to this project solely in our
personal capacity and are not conveying any rights to any intellectual
property of any third parties.
"""

import pyRosetta

def test_constructors():
    player1 = pyRosetta.AccountInfo()

    assert player1.get_email() == 'anonymous@gmail.com'
    assert player1.get_nickname() == 'Anonymous'

    player2 = pyRosetta.AccountInfo('1', 'name1')

    assert player2.get_email() == '1'
    assert player2.get_nickname() == 'name1'

    player3 = pyRosetta.AccountInfo('2', 'name2', [])

    assert player3.get_email() == '2'
    assert player3.get_nickname() == 'name2'
    assert player3.get_num_of_deck() == 0

def test_deck_control():
    player = pyRosetta.AccountInfo()

    player.show_deck_list()
    assert player.create_deck('deck1', pyRosetta.CardClass.INVALID) == False

    player.create_deck('deck2', pyRosetta.CardClass.DREAM)
    player.create_deck('deck3', pyRosetta.CardClass.DRUID)
    
    assert player.get_num_of_deck() == 2
    player.show_deck_list()

    player.delete_deck(0)
    assert player.get_num_of_deck() == 1
    assert player.get_deck(0).get_name() == 'deck3'

    assert player.get_num_of_deck() == 1