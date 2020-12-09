#!/usr/bin/env python
from joblib import load
import socket

def cleanQuery(query):
    temp = ""
    for byte in query:
        if byte == 44 or 48 <=  byte <= 57:
            temp += chr(byte)
    temp = temp.strip()
    temp = temp.split(',')
    cleaned = []
    if (len(temp) <= 1): return []
    for val in temp:
        cleaned.append(int(val))
    return cleaned

def validateQuery(query, idealLength = -1):#tests
    if len(query) != idealLength:
        return False
    for val in query:
        if not (0 <= val <= 100):
            return False
    return True

def KNNPrediction(model, query):
    print(query)
    query = [query]
    predicted = model.predict(query)
    return predicted


TCP_IP = '127.0.0.1'
TCP_PORT = 54000
BUFFER_SIZE = 50  # Normally 1024, but we want fast response
knn = load('data/covidModelKNN.joblib')

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)

conn, addr = s.accept()
print('Connection address:', addr)
while 1:
    data = conn.recv(BUFFER_SIZE)
    if not data: break
    print("received data:", data)
    query = cleanQuery(data)
    if (validateQuery(query, 16)):
        predict = KNNPrediction(knn, query)
        predict = bytes(str(predict[0]), 'utf-8')
        print(predict)
        conn.send(predict)  # echo

conn.close()