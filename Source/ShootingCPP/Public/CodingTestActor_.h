// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodingTestActor_.generated.h"

UCLASS()
class SHOOTINGCPP_API ACodingTestActor_ : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACodingTestActor_();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//기본 자료형 변수
	int32 num1 = 32;
	float num2 = 3.14f;
	FString name = TEXT("FString");
	bool isReady = false;

};
