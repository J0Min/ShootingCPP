// Fill out your copyright notice in the Description page of Project Settings.


#include "AccessTestActor.h"

#include "CodingTestActor_.h"

// Sets default values
AAccessTestActor::AAccessTestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAccessTestActor::BeginPlay()
{
	Super::BeginPlay();
	
	ACodingTestActor_* testActor = NewObject<ACodingTestActor_>();
	testActor->num1 = 100;
	UE_LOG(LogTemp, Warning, TEXT("num1: %i"), testActor->num1);
}

// Called every frame
void AAccessTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

