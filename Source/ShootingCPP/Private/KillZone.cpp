// Fill out your copyright notice in the Description page of Project Settings.


#include "KillZone.h"
#include "Components/BoxComponent.h"


// Sets default values
AKillZone::AKillZone()
{
	//Tick이 필요없는 액터는 항상 false로 설정
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	//박스 콜리전 컴포넌트 생성 및 최상단 컴포넌트로 설정
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	SetRootComponent(boxComp);
	//콜리전 박스 크기 조절
	FVector boxsize = FVector(50.f, 2000.f, 50.f);
	boxComp->SetBoxExtent(boxsize);
	//박스 모빌리티 고정
	boxComp->SetMobility(EComponentMobility::Static);
	
	boxComp->SetCollisionProfileName(TEXT("KillZone"));

}

// Called when the game starts or when spawned
void AKillZone::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AKillZone::OnKillZoneOverlap);
}

void AKillZone::OnKillZoneOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 충돌 오버랩 발생한 액터 제거
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}

