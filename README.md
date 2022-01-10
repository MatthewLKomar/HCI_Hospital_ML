VR + KMeans Neural Network + Unreal Engine 4
A Matthew L. Komar VR Experience
Built for 05318 for CMU HCI 
See it in action: https://www.youtube.com/watch?v=VeK8viBRrBE&feature=youtu.be
The dataset is not on github because it's too big. Here's the google drive link to it instead: https://drive.google.com/drive/folders/1h6oWzvLv27ss_h0siIa_rexhqDrcOCLs?usp=sharing
I used the Anaconda Python 3.9 environment and Unreal Engine 4.26

**********If for some reason you'll use anything from here, I'd apreciate it if credit me**********

My python source code is in /_PythonML.
I simplified the COVID19 data set that I simplified and used is called 'GenerateCleanCSV.py'. 
Then I used it for training and saved it in GenerateCovidModel.py
Then I used it for prediction in UseCovidModel.py. 
UseCovidModel.py looks the different from your run of the mill SCIKIT tutorial, reason being is that I'm using a TCP-IP to recieve and transmit predicition input/output. UseCovidModel.py is both the predictor and the server.

Python libs used: 
Scikit,
Pandas,
Numpy,
Joblib,
Socket (built in)



Unreal Engine isn't running off any template, aside from the stuff normally generated for users.
All 3D models seen were made by me. Everything was programmed by me. 
The ML_REMOTE_Client is an Actor component that TCP/IPs to our Python server. It was written in C++, but is also made visible for blueprints programming. 
It's job is to convert and transmit a struct with a similar structure containing feature values to the python server. It is then supposed to recieve the response. 

If you want to try the COVIDULATOR out for yourself, download the whole thing and get the data folder. Put the data folder inside _PythonML. 
In Unreal Engine you want to go to a map called InteractionTest and you'll find the scene with the COVIDULATOR. It won't work if your python server isn't on though. 

All buttons/levers/sliders don't require you to grip anything, just overlap your index figure and move in the direction you want to interact with stuff in.

Have fun! 
