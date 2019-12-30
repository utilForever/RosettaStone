#!/usr/bin/python3

import os
import json
import tensorflow as tf

import data_reader


kOutputNodeName = 'final_argmax'

class NextInputGetter:
  def __init__(self, data):
    self._idx = 0
    self._data = data

  def get_next_slice(self, size):
    ret = tf.slice(self._data, [0, self._idx], [-1, size])
    self._idx = self._idx + size
    return ret

  def get_rest(self):
    return tf.slice(self._data, [0, self._idx], [-1, -1])

class Model:
  def __init__(self):
    self._mode = None

    self.kEnableCardIdEmbed = False
    self.kEnableHandCardIdEmbed = False
    self.kCardIdDimension = 3

    self.kMinionConvolutionHidden1 = 10

    self.kHeroConvolutionHidden1 = 2

    self.kHandConvolutionHidden1 = 2

    self.kResidualBlockFeatures = 50
    self.kResidualBlocks = 3

  def _model_hero(self, input_getter):
    inputs = input_getter.get_next_slice(data_reader.kHeroFeatures)

    hero1 = tf.layers.dense(
        name='hero1',
        inputs=inputs,
        units=self.kHeroConvolutionHidden1,
        reuse=tf.AUTO_REUSE,
        activation=tf.nn.relu)

    return [hero1]

  def _get_embedded_onboard_card_id(self, card_id):
    if not self.kEnableCardIdEmbed:
      return None

    card_id = tf.to_int32(card_id, name='card_id_to_int32')
    with tf.variable_scope("onboard", reuse=tf.AUTO_REUSE):
      card_id_matrix = tf.get_variable(
          'card_embed_matrix',
          [data_reader.kMaxCardId, self.kCardIdDimension],
          initializer=tf.zeros_initializer())
    card_id_embed = tf.nn.embedding_lookup(
      card_id_matrix, card_id, name='card_id_embed')
    card_id_embed = tf.reshape(card_id_embed, [-1, self.kCardIdDimension])
    return card_id_embed

  def _model_minion(self, input_getter):
    inputs = []

    card_id = input_getter.get_next_slice(1)
    card_id_embed = self._get_embedded_onboard_card_id(card_id)
    if card_id_embed is not None:
      inputs.append(card_id_embed)

    features = input_getter.get_next_slice(data_reader.kMinionFeatures)
    inputs.append(features)

    minion1 = tf.layers.dense(
        name='minion1',
        inputs=tf.concat(inputs, 1),
        units=self.kMinionConvolutionHidden1,
        reuse=tf.AUTO_REUSE,
        activation=tf.nn.relu)

    return minion1

  def _model_minions(self, input_getter):
    features = []
    for _ in range(data_reader.kMinions):
      features.append(self._model_minion(input_getter))

    return features

  def _get_embedded_hand_card_id(self, card_id):
    if not self.kEnableHandCardIdEmbed:
      return None

    card_id = tf.to_int32(card_id, name='card_id_to_int32')
    with tf.variable_scope("current_hand", reuse=tf.AUTO_REUSE):
      card_id_matrix = tf.get_variable(
          'card_embed_matrix',
          [data_reader.kMaxCardId, self.kCardIdDimension],
          initializer=tf.zeros_initializer())
    card_id_embed = tf.nn.embedding_lookup(
      card_id_matrix, card_id, name='card_id_embed')
    card_id_embed = tf.reshape(card_id_embed, [-1, self.kCardIdDimension])
    return card_id_embed

  def _model_current_hand_card(self, input_getter):
    outputs = []

    card_id = input_getter.get_next_slice(1)
    card_id_embed = self._get_embedded_hand_card_id(card_id)
    if card_id_embed is not None:
      outputs.append(card_id_embed)

    card_features = input_getter.get_next_slice(
        data_reader.kCurrentHandCardFeatures)
    card1 = tf.layers.dense(
        name='hand_card_1',
        inputs=card_features,
        units=self.kHandConvolutionHidden1,
        reuse=tf.AUTO_REUSE,
        activation=tf.nn.relu)
    outputs.append(card1)

    return outputs

  def _model_current_hand(self, input_getter):
    outputs = []
    outputs.append(
        input_getter.get_next_slice(data_reader.kCurrentHandFeatures))

    for _ in range(data_reader.kCurrentHandCards):
      outputs.extend(self._model_current_hand_card(input_getter))

    return outputs

  def _model_board_features(self, input_getter):
    return [input_getter.get_rest()]

  def _residual_block_unit(self, scope, inputs, hidden, add_input=None):
    with tf.variable_scope(scope):
      output = tf.contrib.layers.fully_connected(
          inputs,
          hidden,
          activation_fn=None,
          scope='dense')

      if add_input is not None:
        output = tf.add(output, add_input)

      output = tf.nn.relu(output, 'relu')

      return output

  def _residual_block(self, idx, inputs, hidden):
    name = 'residual_' + str(idx)

    dense1 = self._residual_block_unit(
        name + '_1',
        inputs,
        hidden)

    dense2 = self._residual_block_unit(
        name + '_2',
        dense1,
        hidden,
        add_input=inputs)

    return dense2

  def set_mode(self, mode):
    self._mode = mode

  def get_model(self, features, labels):
    feature = features["x"]
    feature = tf.to_float(feature)

    input_getter = NextInputGetter(feature)

    inputs = []

    inputs.extend(self._model_hero(input_getter))  # current hero
    inputs.extend(self._model_hero(input_getter))  # opponent hero
    inputs.extend(self._model_minions(input_getter))  # current minions
    inputs.extend(self._model_minions(input_getter))  # opponent minions
    inputs.extend(self._model_current_hand(input_getter))  # current hand
    inputs.extend(self._model_board_features(input_getter))  # board features

    inputs = tf.concat(inputs, 1)

    dense1 = tf.layers.dense(
        name='dense1',
        inputs=inputs,
        units=self.kResidualBlockFeatures,
        activation=tf.nn.relu)

    prev = dense1
    for i in range(0, self.kResidualBlocks):
      prev = self._residual_block(i+1, prev, self.kResidualBlockFeatures)

    final = tf.layers.dense(
        name='final',
        inputs=prev,
        units=1,
        activation=None)
		
    final_argmax = tf.argmax(
        name=kOutputNodeName,
        input=final,
        axis=1)

    predictions = {
        "classes": final_argmax,
        "probabilities": tf.nn.softmax(final, name="softmax_tensor")}

    if self._mode == tf.estimator.ModeKeys.PREDICT:
      return tf.estimator.EstimatorSpec(
          mode=self._mode, predictions=final,
          export_outputs={"y": tf.estimator.export.PredictOutput({"y": final})})
    
    labels = tf.reshape(labels, [-1, 1])
    loss = tf.losses.mean_squared_error(
        labels=labels,
        predictions=final)

    if self._mode == tf.estimator.ModeKeys.TRAIN:
      train_step = tf.train.AdamOptimizer(1e-4).minimize(
          loss,
          global_step=tf.train.get_global_step())

      return tf.estimator.EstimatorSpec(
          mode=self._mode,
          loss=loss,
          train_op=train_step)

    else:  # EVAL mode
      binary_labels = tf.equal(labels, data_reader.kLabelIfFirstPlayerWin)
      predictions = tf.greater(final,
          data_reader.kLabelFirstPlayerWinIfGreaterThan)
      eval_metric_ops = {
          "accuracy": tf.metrics.accuracy(
            labels=binary_labels,
            predictions=predictions)}

      return tf.estimator.EstimatorSpec(
          mode=self._mode, loss=loss,
          eval_metric_ops=eval_metric_ops)
