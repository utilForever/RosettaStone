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