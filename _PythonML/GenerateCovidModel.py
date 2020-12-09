import numpy as np
import pandas as pd
from sklearn import neighbors, metrics
from sklearn.model_selection import train_test_split
from joblib import dump, load
from datetime import datetime

def GetTime():
    now = datetime.now()
    current_time = now.strftime("%H:%M:%S")
    return current_time

data = pd.read_csv('data/CleanedCovidMexico.csv')

#standards are: X == data; y == labels

X = data[['SEXO','TIPO_PACIENTE',
            'INTUBADO','NEUMONIA','EDAD','EMBARAZO',
            'DIABETES', 'EPOC',	'ASMA','INMUSUPR','HIPERTENSION','CARDIOVASCULAR','OBESIDAD','RENAL_CRONICA','TABAQUISMO',
            'UCI']]
y = data[['RESULTADO_LAB']]#what we want to predict

y = np.array(y)
y = np.ravel(y, order='C')
#create model

knn = neighbors.KNeighborsClassifier(n_neighbors=4, weights='uniform')

X_train, X_test, y_train, y_test = train_test_split(X,y, test_size=0.2)

print("made it past train_test_split " + GetTime())
knn.fit(X_train, y_train)
print("made it past fit " + GetTime())
dump(knn, 'data/covidModelKNN.joblib')
print("made it past dump " + GetTime())

