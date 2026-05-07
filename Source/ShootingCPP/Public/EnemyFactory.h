// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyFactory.generated.h"

UCLASS()
class SHOOTINGCPP_API AEnemyFactory : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyFactory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//생성할 적
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyActor> enemy;
	
	//생성 간격
	UPROPERTY(EditAnywhere)
	float delayTime = 2.f;
	
private:
	//누적 시간
	float currentTime = 0;
	
};
