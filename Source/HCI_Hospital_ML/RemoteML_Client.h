// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <WS2tcpip.h>
#include "RemoteML_Client.generated.h"
#pragma comment(lib, "ws2_32.lib")

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HCI_HOSPITAL_ML_API URemoteML_Client : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URemoteML_Client();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FString ipAddress = "127.0.0.1";
	int port = 54000;
	SOCKET sock; 
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	
	
	SOCKET MakeSocket(); 
	void CloseSocket(SOCKET sock);
	sockaddr_in SetUpAddress(FString IpAddress, int Port); //Configures connecting socket address
	bool ConnectToServer(SOCKET sock, sockaddr_in addr);
	FString SendToServer(FString Info);

		
};
