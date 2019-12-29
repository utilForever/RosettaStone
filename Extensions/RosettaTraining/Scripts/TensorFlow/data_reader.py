import os
import json

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