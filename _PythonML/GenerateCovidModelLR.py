import numpy as np
import pandas as pd
from sklearn import preprocessing
from datetime import datetime
from sklearn.metrics import confusion_matrix
from sklearn.metrics import classification_report
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier

from joblib import dump, load

def GetTime():
    now = datetime.now()
    current_time = now.strftime("%H:%M:%S")
    return current_time


# helper method to print basic model metrics
def metrics(y_true, y_pred):
    print('Confusion matrix:\n', confusion_matrix(y_true, y_pred))
    print('\nReport:\n', classification_report(y_true, y_pred))


data = pd.read_csv('data/CleanedCovidMexico.csv')

#standards are: X == data; y == labels

feautures_cat = ['INTUBADO','NEUMONIA','EDAD','EMBARAZO',
          'DIABETES','ASMA','CARDIOVASCULAR','OBESIDAD', 'UCI']


print("starting " + GetTime())

X = data[feautures_cat] #'PAIS_ORIGEN'
y = data[['RESULTADO_LAB']]#what we want to predict


scaled = preprocessing.scale(X)
print(scaled)
X_num_proc = pd.DataFrame(scaled, columns=feautures_cat)
X_num_proc.head()

X = X_num_proc
X = X.fillna(0)#It replaces not numbers with 0.

X_train, X_TEMP, y_train, y_TEMP = train_test_split(X, y, test_size=0.30) # split out into training 70% of our data
X_validation, X_test, y_validation, y_test = train_test_split(X_TEMP, y_TEMP, test_size=0.50) # split out into validation 15% of our data and test 15% of our data
print(X_train.shape, X_validation.shape, X_test.shape) # print data shape to check the sizing is correct
print("made it past train_test_split " + GetTime())
#model = LogisticRegression(solver='lbfgs').fit(X_train, y_train) # first fit (train) the model
RFC = RandomForestClassifier()
RFC.fit(X_train, y_train)
print("made it past fit " + GetTime())
dump(RFC, 'data/covidModelRFC.joblib')
print("made it past dump " + GetTime())
y_pred = RFC.predict(X_validation) # next get the model's predictions for a sample in the validation set
print(y_pred)
metrics(y_validation, y_pred) # finally evaluate performance
print("made it past prediction " + GetTime())

