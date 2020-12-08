// Fill out your copyright notice in the Description page of Project Settings.


#include "RemoteML_Client.h"
#include <string>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

// Sets default values for this component's properties
URemoteML_Client::URemoteML_Client()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URemoteML_Client::BeginPlay()
{
	Super::BeginPlay();
	
	//sock = MakeSocket(); // make our socket
	//
	//sockaddr_in hint = SetUpAddress(ipAddress, port); //Set up the address values

	//ConnectToServer(sock, hint);
	
	//FString Response = SendToServer(TEXT("Test"));
	//UE_LOG(LogTemp, Error, TEXT("Server> %s"), *Response);
	//CloseSocket(sock);
}


// Called every frame
void URemoteML_Client::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

SOCKET URemoteML_Client::MakeSocket()
{
	//init winsock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	ensure(wsResult == 0);
	//creat socket
	SOCKET Sock = socket(AF_INET, SOCK_STREAM, 0);
	ensure(Sock != INVALID_SOCKET);
	return Sock;
}

void URemoteML_Client::CloseSock()
{
	CloseSocket(sock);
}


void URemoteML_Client::CloseSocket(SOCKET Sock)
{
	//gracefully close down everything once we're done
	closesocket(Sock);
	WSACleanup();
	return;
}

sockaddr_in URemoteML_Client::SetUpAddress(FString IpAddress, int Port)
{//TODO: make this take AF_INET type as a param.
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(Port);
	string ip = string(TCHAR_TO_UTF8(*IpAddress));
	inet_pton(AF_INET, ip.c_str(), &hint.sin_addr);
	return hint;
}

bool URemoteML_Client::ConnectToServer(SOCKET Sock, sockaddr_in addr)
{
	int connResult = connect(Sock, (sockaddr*)&addr, sizeof(addr));
	if (connResult == SOCKET_ERROR)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't connect to server!"));
		CloseSocket(Sock);
		return false;
	}
	return true;
}

void URemoteML_Client::OpenSock()
{
	sock = MakeSocket(); // make our socket

	sockaddr_in hint = SetUpAddress(ipAddress, port); //Set up the address values

	ConnectToServer(sock, hint);
}

FString URemoteML_Client::BtItF(bool val) {
	return FString::FromInt(int(val) + 1);
}

FString URemoteML_Client::ConvertDataSetToString(FDataSet dataSet)
{//this code will look ugly
	//dataSet.Hospitalized = false will map to 1, true maps 2 
	FString Messege = TEXT("");
	Messege += BtItF(dataSet.Sex) + ',';
	Messege += BtItF(dataSet.Hospitalized) + ',';
	Messege += BtItF(dataSet.Intubed) + ',';
	Messege += BtItF(dataSet.Pneuomonia) + ',';
	Messege += FString::FromInt(dataSet.Age) + ',';
	Messege += BtItF(dataSet.Pregnant) + ',';
	Messege += BtItF(dataSet.Diabetes) + ',';
	Messege += BtItF(dataSet.Epoc) + ',';
	Messege += BtItF(dataSet.Asthma) + ',';
	Messege += BtItF(dataSet.Immunosuppression) + ',';
	Messege += BtItF(dataSet.Hypertension) + ',';
	Messege += BtItF(dataSet.Cardiovascular) + ',';
	Messege += BtItF(dataSet.Obese) + ',';
	Messege += BtItF(dataSet.ChronicRenal) + ',';
	Messege += BtItF(dataSet.Smokes);
	return Messege;
}

FString URemoteML_Client::SendToServer(FString Info)
{
	//Send text
	char buf[4096];
	FString Response = TEXT("");
	string userInput = string(TCHAR_TO_UTF8(*Info));
	int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
	ensure(sendResult != SOCKET_ERROR);
	//Wait for a response
	ZeroMemory(buf, 4096);//garbage collecting
	int bytesReceived = recv(sock, buf, 4096, 0);
	if (bytesReceived > 0)
	{
		//Echo response to console
		Response = string(buf, 0, bytesReceived).c_str();
		UE_LOG(LogTemp, Warning, TEXT("SERVER> %s"), *Response);
	}
	return Response;
	//tells you function TEXT(__FUNCTION__)
	//tells you line in code __LINE__int32;
}
