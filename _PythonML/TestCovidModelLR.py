import pandas as pd
from joblib import load
from sklearn import preprocessing
from sklearn.model_selection import train_test_split
from datetime import datetime
import numpy as np

def GetTime():
    now = datetime.now()
    current_time = now.strftime("%H:%M:%S")
    return current_time


LR = load('data/covidModelLR.joblib')



data = pd.read_csv('data/CleanedCovidMexico.csv')
feautures_cat = ['INTUBADO','NEUMONIA','EDAD','EMBARAZO',
          'DIABETES','ASMA','CARDIOVASCULAR','OBESIDAD', 'UCI']


print("starting " + GetTime())

X = data[feautures_cat] #'PAIS_ORIGEN'
y = data[['RESULTADO_LAB']]#what we want to predict


scaled = preprocessing.scale(X)
X_num_proc = pd.DataFrame(scaled, columns=feautures_cat)
X_num_proc.head()

X = X_num_proc
X = X.fillna(0)#It replaces not numbers with 0.

print("Get past set up " + GetTime())

X_train, X_TEMP, y_train, y_TEMP = train_test_split(X, y, test_size=0.30) # split out into training 70% of our data
X_validation, X_test, y_validation, y_test = train_test_split(X_TEMP, y_TEMP, test_size=0.50) # split out into validation 15% of our data and test 15% of our data
print("Past to train_test_split " + GetTime())

a = [X_validation.iloc[1]]
print("orig")
print(X_validation.iloc[1])
# a = np.array(a)
# a = a.reshape(-1,1)
print("a")
print(a)

predicted = LR.predict(a)
print("predicted value: ", predicted) #we use the predict to try the model out
print("Going to predicted value " + GetTime())

