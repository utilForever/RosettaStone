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