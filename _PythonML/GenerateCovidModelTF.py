import numpy as np
import pandas as pd
from sklearn import datasets
import tensorflow as tf
tf.compat.v1.disable_eager_execution()
from datetime import datetime
import math


def GetTime():
    now = datetime.now()
    current_time = now.strftime("%H:%M:%S")
    return current_time

def train_test_split(X, y, test_size):
    len = X.shape[0]
    print(len)
    newSize = math.floor(len * test_size)
    X_train = X[:newSize]
    X_test = X[newSize:]
    y_train = y[:newSize]
    y_test = y[newSize:]
    return X_train, X_test, y_train, y_test

data = pd.read_csv('data/CleanedCovidMexico.csv')

# prepare data
X = data[['ORIGEN', 'SECTOR', 'ENTIDAD_UM', 'SEXO', 'ENTIDAD_NAC', 'ENTIDAD_RES', 'MUNICIPIO_RES', 'TIPO_PACIENTE',
          'INTUBADO','NEUMONIA','EDAD','NACIONALIDAD','EMBARAZO','HABLA_LENGUA_INDIG','INDIGENA',
          'DIABETES', 'EPOC',	'ASMA','INMUSUPR','HIPERTENSION','CARDIOVASCULAR','OBESIDAD','RENAL_CRONICA','TABAQUISMO',
          'OTRO_CASO','TOMA_MUESTRA','CLASIFICACION_FINAL','MIGRANTE', 'UCI']] #'PAIS_ORIGEN',
y = data[['RESULTADO_LAB']]#what we want to predict
y = np.array(y)
y = np.ravel(y, order='C')

np.random.seed(59)
train_indices = np.random.choice(len(X), round(len(X) * 0.8), replace=False)
test_indices =np.array(list(set(range(len(X))) - set(train_indices)))

X_train , X_test, y_train, y_test = train_test_split(X, y, 0.8)

k = 4


x_data_train = tf.compat.v1.placeholder(shape=X_train.shape, dtype=tf.float32)
y_data_train = tf.compat.v1.placeholder(shape=y_train.shape, dtype=tf.float32)
x_data_test = tf.compat.v1.placeholder(shape=X_test.shape, dtype=tf.float32)

# manhattan distance
distance = tf.reduce_sum(tf.abs(tf.subtract(x_data_train, tf.expand_dims(x_data_test, 1))), axis=2)
#
# # nearest k points
_, top_k_indices = tf.nn.top_k(tf.negative(distance), k=k)
top_k_label = tf.gather(y_data_train, top_k_indices)

sum_up_predictions = tf.reduce_sum(top_k_label, axis=1)
prediction = tf.argmax(sum_up_predictions, axis=1)


sess = tf.compat.v1.Session()
prediction_outcome = sess.run(prediction, feed_dict={x_data_train: X_train,
                                                     x_data_test: X_test,
                                                     y_data_train: y_train})

# evaluation
accuracy = 0
for pred, actual in zip(prediction_outcome, y_test):
    if pred == np.argmax(actual):
        accuracy += 1

print(accuracy / len(prediction_outcome))