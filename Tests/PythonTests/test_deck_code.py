"""
Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

We are making my contributions/submissions to this project solely in our
personal capacity and are not conveying any rights to any intellectual
property of any third parties.
"""

import pyRosetta
import pytest

def test_decode():
	with pytest.raises(Exception):
		pyRosetta.DeckCode.decode('AAECAR8I')
	with pytest.raises(Exception):
		pyRosetta.DeckCode.decode('AQECAR8IxwOHBMkErgaggAOnggObhQPWmQMLngGoArUDxQj+DJjwAu/xAvWJA+aWA/mWA76YAwA=')
	with pytest.raises(Exception):
		pyRosetta.DeckCode.decode('AAICAR8IxwOHBMkErgaggAOnggObhQPWmQMLngGoArUDxQj+DJjwAu/xAvWJA+aWA/mWA76YAwA=')
	with pytest.raises(Exception):
		pyRosetta.DeckCode.decode('AAESAR8IxwOHBMkErgaggAOnggObhQPWmQMLngGoArUDxQj+DJjwAu/xAvWJA+aWA/mWA76YAwA=')
	with pytest.raises(Exception):
		pyRosetta.DeckCode.decode('AAECAh8FCMcDhwTJBK4GoIADp4IDm4UD1pkDC54BqAK1A8UI/gyY8ALv8QL1iQPmlgP5lgO+mAMA')
	with pytest.raises(Exception):
		pyRosetta.DeckCode.decode('AAECAQAIxwOHBMkErgaggAOnggObhQPWmQMLngGoArUDxQj+DJjwAu/xAvWJA+aWA/mWA76YAwA=')

	info = pyRosetta.DeckCode.decode('AAECAR8IxwOHBMkErgaggAOnggObhQPWmQMLngGoArUDxQj+DJjwAu/xAvWJA+aWA/mWA76YAwA=')

	assert info.deck_class() == pyRosetta.CardClass.HUNTER
	assert info.num_of_cards() == 30
	assert info.num_card_in_deck('EX1_080') == 2
	assert info.num_card_in_deck('EX1_610') == 1
	assert info.num_card_in_deck('EX1_611') == 1
	assert info.num_card_in_deck('GIL_577') == 2
	assert info.num_card_in_deck('EX1_554') == 1
	assert info.num_card_in_deck('EX1_609') == 1
	assert info.num_card_in_deck('DAL_086') == 2
	assert info.num_card_in_deck('NEW1_031') == 2
	assert info.num_card_in_deck('EX1_617') == 2
	assert info.num_card_in_deck('EX1_536') == 2
	assert info.num_card_in_deck('EX1_539') == 2
	assert info.num_card_in_deck('TRL_530') == 2
	assert info.num_card_in_deck('DAL_558') == 1
	assert info.num_card_in_deck('GIL_622') == 2
	assert info.num_card_in_deck('DAL_371') == 2
	assert info.num_card_in_deck('BOT_573') == 1
	assert info.num_card_in_deck('BOT_548') == 1
	assert info.num_card_in_deck('DAL_378') == 2
	assert info.num_card_in_deck('TRL_065') == 1

	info2 = pyRosetta.DeckCode.decode('AAECAR8IxwOHBMkErgaggAOnggObhQPWmQMAC54BAqgCArUDAsUIAv4MApjwAgLv8QIC9YkDAuaWAwL5lgMCvpgDAg==')

	assert info2.deck_class() == pyRosetta.CardClass.HUNTER
	assert info2.num_of_cards() == 30
	assert info2.num_card_in_deck('EX1_080') == 2
	assert info2.num_card_in_deck('EX1_610') == 1
	assert info2.num_card_in_deck('EX1_611') == 1
	assert info2.num_card_in_deck('GIL_577') == 2
	assert info2.num_card_in_deck('EX1_554') == 1
	assert info2.num_card_in_deck('EX1_609') == 1
	assert info2.num_card_in_deck('DAL_086') == 2
	assert info2.num_card_in_deck('NEW1_031') == 2
	assert info2.num_card_in_deck('EX1_617') == 2
	assert info2.num_card_in_deck('EX1_536') == 2
	assert info2.num_card_in_deck('EX1_539') == 2
	assert info2.num_card_in_deck('TRL_530') == 2
	assert info2.num_card_in_deck('DAL_558') == 1
	assert info2.num_card_in_deck('GIL_622') == 2
	assert info2.num_card_in_deck('DAL_371') == 2
	assert info2.num_card_in_deck('BOT_573') == 1
	assert info2.num_card_in_deck('BOT_548') == 1
	assert info2.num_card_in_deck('DAL_378') == 2
	assert info2.num_card_in_deck('TRL_065') == 1
