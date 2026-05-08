// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"

#include "EngineUtils.h"
#include "PlayerPawn.h"
#include "ShootingGameModeBase.h"
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
	
	//에디터에서 생성할 프리셋 이름을 컴포넌트에 세팅
	boxComp->SetCollisionProfileName(TEXT("Enemy"));
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
	int32 drawResult = FMath::RandRange(1,100);
	if (drawResult < traceRate)
	{	//추적을 위한 액터 탐색 반복 TActorIterater 활용
		//for(TActorIterater<찾으려는 클래스> 위치포인터변수,변수이름,++변수증감식)
		for (TActorIterator<APlayerPawn> player(GetWorld()); player; ++player)
		{
			if (player->GetName().Contains("BP_PlayerPawn"))
			{
				//찾은 플레이어 위치 - 자신 위치 = 플레어를 향한 방향
				dir = player->GetActorLocation() - GetActorLocation();
				dir.Normalize();
			}
		}
	}else//직진
	{
		dir = GetActorForwardVector();
	}
	
	//overlap 발생시 등록한 함수를 호출하라고 엔진에 사전 등록
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnEnemyOverlap);
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector newLocation = GetActorLocation() + dir * moveSpeed * DeltaTime;
	SetActorLocation(newLocation);
}

void AEnemyActor::OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//충돌한 상대 액터를 Enemy로 형변환하여 소멸 진행
	APlayerPawn* player = Cast<APlayerPawn>(OtherActor);
	if (player != nullptr)
	{
		OtherActor->Destroy();
		
		//게임 오버 메뉴 showmenu() 호출
		AShootingGameModeBase* currentGameModeBase = Cast<AShootingGameModeBase>(GetWorld()->GetAuthGameMode());
		if (currentGameModeBase != nullptr)
		{
			currentGameModeBase->ShowMenu();
		}
	}
	//자신도 소멸
	this->Destroy();
}

