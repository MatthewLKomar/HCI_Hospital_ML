// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "DataSetStruct.generated.h"

USTRUCT(BlueprintType)
struct FDataSet
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Sex = false; //'SEXO'
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Age = 0; //EDAD
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Hospitalized = false; //TIPO_PACIENTE
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Intubed = false; //INTUBADO
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Pneuomonia = false; //NEUMONIA
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Pregnant = false; //'EMBARAZO',
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Diabetes = false; //DIABETES
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Asthma = false;; //ASMA
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Cardiovascular = false;; //CARDIOVASCULAR
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Obese = false;; //OBESIDAD
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IntensiveCareUnit = false;; //UCI
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Epoc = false;; //EPOC
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Immunosuppression = false;; //IMMUNOSUPR
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Hypertension = false;; //HiperTension
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ChronicRenal = false;; // 'RENAL_CRONICA'
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Smokes = false;; //TABAQUISMO
};


UCLASS()
class HCI_HOSPITAL_ML_API UDataSetStruct : public UUserDefinedStruct
{
	GENERATED_BODY()
	
};
