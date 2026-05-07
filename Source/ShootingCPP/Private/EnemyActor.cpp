// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"

#include "Components/BoxComponent.h"


// Sets default values
AEnemyActor::AEnemyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//박스 콜리전 컴포넌트 생성 및 최상단 컴포넌트로 설정
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	SetRootComponent(boxComp);
	
	//스태틱 매쉬 컴포넌트 생성 및 박스 콜리전 자식으로 설정
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh Component"));
	meshComp->SetupAttachment(boxComp);
	
	//콜리전 박스 크기 조절
	FVector boxsize = FVector(50.f, 50.f, 50.f);
	boxComp->SetBoxExtent(boxsize);
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

