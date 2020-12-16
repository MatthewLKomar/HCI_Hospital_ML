// Fill out your copyright notice in the Description page of Project Settings.


#include "RemoteML_Client.h"
#include <string>
#include "Engine/World.h"

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
	Messege += BtItF(dataSet.Sex) + ','; //sexo
	Messege += BtItF(dataSet.Hospitalized) + ','; //tipo_patiente
	Messege += BtItF(dataSet.Intubed) + ','; //intubado
	Messege += BtItF(dataSet.Pneuomonia) + ','; //neuomonia
	Messege += FString::FromInt(dataSet.Age) + ','; //edad
	Messege += BtItF(dataSet.Pregnant) + ','; //embarzo
	Messege += BtItF(dataSet.Diabetes) + ','; //diabetes
	Messege += BtItF(dataSet.Epoc) + ','; //epoc
	Messege += BtItF(dataSet.Asthma) + ','; //asma
	Messege += BtItF(dataSet.Immunosuppression) + ','; //immunosupression
	Messege += BtItF(dataSet.Hypertension) + ','; //hipertension
	Messege += BtItF(dataSet.Cardiovascular) + ','; //cardio vascular
	Messege += BtItF(dataSet.Obese) + ','; //obesidad
	Messege += BtItF(dataSet.ChronicRenal) + ','; //RENAL_CHRONICA
	Messege += BtItF(dataSet.Smokes) + ','; //tabaquismo
	Messege += BtItF(dataSet.IntensiveCareUnit); //UCI
	return Messege;
}

void URemoteML_Client::SendToServer(FString Info)
{
	DidServerRespondYet = false;
	string userInput = string(TCHAR_TO_UTF8(*Info));
	int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
	ensure(sendResult != SOCKET_ERROR);
	//GetWorld()->GetTimerManager().SetTimer(ServerResponseTimer, TFunction<void>() & ServerResponse, 0.0f, false);
}


void URemoteML_Client::ServerResponse()
{
	//Send text
	char buf[4096];
	ZeroMemory(buf, 4096);//garbage collecting
	//Wait for a response
	int bytesReceived = recv(sock, buf, 4096, 0);
	if (bytesReceived > 0)
	{
		//Echo response to console
		Response = string(buf, 0, bytesReceived).c_str();
		UE_LOG(LogTemp, Warning, TEXT("SERVER> %s"), *Response);
	}
	DidServerRespondYet = true;
	//InvalidateTimer();
}

void URemoteML_Client::InvalidateTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(ServerResponseTimer);
}


FString URemoteML_Client::GetServerResponse()
{
	return Response;
}




