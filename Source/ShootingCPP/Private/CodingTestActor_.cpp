// Fill out your copyright notice in the Description page of Project Settings.


#include "CodingTestActor_.h"

// Sets default values
ACodingTestActor_::ACodingTestActor_()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACodingTestActor_::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Test Actor BeginPlay"));
	
	UE_LOG(LogTemp, Warning, TEXT("%d"),num1);
	UE_LOG(LogTemp, Warning, TEXT("%.2f"),num2);
	UE_LOG(LogTemp, Warning, TEXT("%s"),*name);
	UE_LOG(LogTemp, Warning, TEXT("%d"),isReady);
	UE_LOG(LogTemp, Warning, TEXT("%d"),AddCustom(num3,num4));
}

// Called every frame
void ACodingTestActor_::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 ACodingTestActor_::AddCustom(int32 a, int32 b)
{
	return a + b;
}