from joblib import load

knn = load('data/covidModelKNN.joblib')

b = [[2,2,2,1,49,97,2,2,2,2,2,2,2,2,2,2]]
predicted = knn.predict(b)
print("predicted value: ", predicted) #we use the predict to try the model out

