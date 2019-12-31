import json
import os

LABEL_IF_PLAYER1_WIN = 1
LABEL_IF_PLAYER1_LOSS = -1

kLabelIfFirstPlayerLoss = -1
kLabelIfFirstPlayerWin = 1
kLabelFirstPlayerWinIfGreaterThan = 0

kHeroFeatures = 1
kMinionFeatures = 7  # exclude card id
kMinions = 7

kCurrentHandCards = 10
kCurrentHandCardFeatures = 1  # exclude card id
kCurrentHandFeatures = 1

kMaxCardId = 1860

class DynamicMapper:
    def __init__(self, start_index = 0):
        self.dict_v_to_index = {}
        self.dict_index_to_v = {}
        self.next_index = start_index

    def add_map(self, v):
        idx = self.next_index
        self.next_index = idx + 1

        self.dict_v_to_index[v] = idx
        self.dict_index_to_v[idx] = v

    def get_index(self, v):
        if v not in self.dict_v_to_index:
            self.add_map(v)
        return self.dict_v_to_index[v]

    def get_index_to_v_dict(self):
        return self.dict_index_to_v

class DataReader:
    def __init__(self, dirname):
        self.dirname = dirname
        self.data = []
        self.hand_card_mapper = DynamicMapper(1)

    @classmethod
    def from_bool(cls, v):
        if v is True:
            return 1.0
        else:
            return -1.0

    def read_hero_data(self, data):
        health = data['hero']['health']
        armor = data['hero']['armor']

        self.data.extend([health + armor])

    def add_minion_data_placeholder(self):
        self.data.extend([
            0, 0, 0, 0,
            -1.0, -1.0, -1.0, -1.0
        ])

    def add_minion_data(self, minion):
        attackable = False
        try:
            attackable = minion['attackable']
        except Exception as _:
            attackable = False

        self.data.extend([
            minion['card_id'],
            minion['health'],
            minion['max_health'],
            minion['attack'],
            self.from_bool(attackable),
            self.from_bool(minion['taunt']),
            self.from_bool(minion['divine_shield']),
            self.from_bool(minion['stealth'])
        ])

    def read_minions_data(self, minions):
        if minions is None:
            minions = []

        count = len(minions)

        for idx in range(0, 7):
            if idx < count:
                self.add_minion_data(minions[idx])
            else:
                self.add_minion_data_placeholder()

    def add_mana_crystal(self, mana_crystal):
        self.data.extend([
            mana_crystal['remaining'],
            mana_crystal['total'],
            mana_crystal['overload_owed']
        ])

    def add_current_hand(self, hand):
        if hand is None:
            hand = {}

        playable = 0
        for card in hand:
            if card['playable']:
                playable = playable + 1
        self.data.append(playable)

        def add_data(card_id, cost):
            mapped_card_id = self.hand_card_mapper.get_index(card_id)
            self.data.append(mapped_card_id)
            self.data.append(cost)

        for card in hand:
            card_id = card['card_id']
            cost = card['cost']
            add_data(card_id, cost)
        for _ in range(10 - len(hand)):
            card_id = 0
            cost = -1
            add_data(card_id, cost)

    def add_opponent_hand(self, hand):
        if hand is None:
            hand = {}
        
        self.data.extend([
            len(hand)
        ])

    def add_hero_power(self, hero_power):
        self.data.extend([
            self.from_bool(hero_power['playable'])
        ])

    def read_field(self, board):
        self.data.clear()

        self.read_hero_data(board['current_player'])
        self.read_hero_data(board['opponent_player'])
        self.read_minions_data(board['current_player']['minions'])
        self.read_minions_data(board['opponent_player']['minions'])
        self.add_current_hand(board['current_player']['hand'])
        self.add_opponent_hand(board['opponent_player']['hand'])

        self.add_mana_crystal(board['current_player']['mana_crystal'])
        self.add_hero_power(board['current_player']['hero_power'])

        return list(self.data)

    def get_label(self, current_player, player1_win):
        player1_string = 'Player1'
        player2_string = 'Player2'

        if current_player == player1_string:
            current_player_is_player1 = True
        elif current_player == player2_string:
            current_player_is_player1 = False
        else:
            assert False

        assert player1_win is not None
        if current_player_is_player1 is player1_win:
            return LABEL_IF_PLAYER1_WIN
        else:
            return LABEL_IF_PLAYER1_LOSS

    def win_or_loss(self, result):
        win_string = 'PLAYER1_WIN'
        loss_string = 'PLAYER2_WIN'

        if result == win_string:
            return True

        assert result == loss_string
        return False

    def read_one_json(self, all_data, all_label, json_data):
        player1_win = None
        for block_data in json_data:
            action_type = block_data['type']
            if action_type == 'END':
                player1_win = self.win_or_loss(block_data['result'])
        assert player1_win is not None

        for block_data in json_data:
            action_type = block_data['type']
            if action_type == 'MAIN_ACTION':
                field = block_data['field']
                data = self.read_field(field)
                label = self.get_label(field['current_player_id'], player1_win)

                all_data.append(data)
                all_label.append(label)
    
    def parse(self):
        data = []
        label = []

        for (dirpath, _, filenames) in os.walk(self.dirname):
            for idx, filename in enumerate(filenames):
                fullpath = os.path.join(dirpath, filename)
                print("Reading file (%d / %d): %s " % (idx+1, len(filenames), fullpath))
                with open(fullpath) as data_file:
                    try:
                        json_data = json.load(data_file)
                    except Exception:
                        print("Skipped file %s: Failed to read json" % fullpath)
                        continue
                    self.read_one_json(data, label, json_data)
            break

        return data, label, self.hand_card_mapper.get_index_to_v_dict()
