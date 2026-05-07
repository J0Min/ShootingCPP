// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "Components/BoxComponent.h"


// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//콜리전 생성후 루트 컴포넌트 설정
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Collider"));
	SetRootComponent(boxComp);
	//박스 콜라이더 크기 조절
	FVector boxSize = FVector(50.f,50.f,50.f);
	boxComp->SetBoxExtent(boxSize);
	//scale 조절 - 박스 크기를 총알 형태에 가깝게 조절
	boxComp->SetWorldScale3D(FVector(0.75f,0.25f,1.f));
	
	//외형 메쉬컴포넌트 생성후 박스 컴포넌트에 상속
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My StaticMesh Component"));
	meshComp->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

