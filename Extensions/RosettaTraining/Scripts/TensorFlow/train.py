#!/usr/bin/python3

import argparse
import numpy
import random
import os
import shutil
import tempfile

import tensorflow as tf
from tensorflow.python.tools import freeze_graph
from tensorflow.python.tools import saved_model_utils
from tensorflow.python.saved_model import tag_constants
from tensorflow.python.framework import graph_util
from tensorflow.python.framework import importer
from tensorflow.python.saved_model import loader
from tensorflow.python.platform import gfile

import data_reader
import model

kTrainingPercent = 0.5
kThreads = 20


def _get_estimator():
  sess_config = tf.ConfigProto(
      intra_op_parallelism_threads=kThreads,
      inter_op_parallelism_threads=kThreads)
  estimator_config = tf.estimator.RunConfig(session_config=sess_config)
  
  training_model = model.Model()
  def model_fn(features, labels, mode):
    training_model.set_mode(mode)
    return training_model.get_model(features, labels)

  return tf.estimator.Estimator(
      model_fn=model_fn,
      model_dir="model_output",
      config=estimator_config)
	  
def train_model(data_dir):
  dr = data_reader.DataReader(data_dir)
  data, label, _ = dr.parse()

  data_label = list(zip(data, label))
  random.shuffle(data_label)
  data, label = zip(*data_label)

  data = numpy.array(data)
  label = numpy.array(label)

  rows = len(data)
  rows_training = int(rows * kTrainingPercent)
  data_training = data[:rows_training]
  label_training = label[:rows_training]
  data_validation = data[rows_training:]
  label_validation = label[rows_training:]

  estimator = _get_estimator()

  train_input_fn = tf.estimator.inputs.numpy_input_fn(
      x={"x": data_training},
      y=label_training,
      shuffle=True,
      num_epochs=None)
  train_spec = tf.estimator.TrainSpec(
      input_fn=train_input_fn,
      max_steps=5000000)

  evaluate_input_fn = tf.estimator.inputs.numpy_input_fn(
      x={"x": data_validation},
      y=label_validation,
      shuffle=False)
  eval_spec = tf.estimator.EvalSpec(
      input_fn=evaluate_input_fn,
      throttle_secs=30)

  tf.estimator.train_and_evaluate(estimator, train_spec, eval_spec)

def export_saved_model():
  batch = 1
  input_dim = 140
  freezed_output = "./freezed"

  estimator = _get_estimator()
  feature = {"x": tf.placeholder(dtype=tf.float32, shape=[batch, input_dim])}

  export_dir = tempfile.mkdtemp()
  saved_model = estimator.export_savedmodel(
      export_dir,
      tf.estimator.export.build_raw_serving_input_receiver_fn(feature))

  graph_def = saved_model_utils.get_meta_graph_def(
      saved_model, tag_constants.SERVING).graph_def

  _ = importer.import_graph_def(graph_def, name="")

  with tf.Session() as sess:
    loader.load(sess, [tag_constants.SERVING], saved_model)
    output_graph_def = graph_util.convert_variables_to_constants(
        sess, graph_def, [model.kOutputNodeName])

  with gfile.GFile(freezed_output, "wb") as f:
    f.write(output_graph_def.SerializeToString())

  shutil.rmtree(export_dir)

def main():
  parser = argparse.ArgumentParser(description="Train Model")
  parser.add_argument('-d', '--data', nargs='?', required=True, help="Data folder name")
  parser.add_argument('--export', action='store_true', help="Export and freeze model")
  try:
    args = parser.parse_args()
  except Exception:
    parser.print_help()
    sys.exit(0)

  if args.export:
    export_saved_model()
  else:
    train_model(args.data)

if __name__ == "__main__":
  tf.logging.set_verbosity(tf.logging.INFO)
  main()
