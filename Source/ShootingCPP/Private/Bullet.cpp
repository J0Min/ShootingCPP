// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "EnemyActor.h"
#include "NiagaraFunctionLibrary.h"
#include "ShootingGameModeBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


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
	
	//에디터에서 생성할 프리셋 이름을 컴포넌트에 세팅
	boxComp->SetCollisionProfileName(TEXT("Bullet"));
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	//onCompBeginOverlap 델리게이트에 onOverlap 함수 등록
	//overlap 발생시 등록한 함수를 호출하라고 엔진에 사전 등록
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletOverlap);
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//전방 이동을 위한 위치 계산
	//지금 위치에서 전방벡터*속도(크기)*델타타임으로 이동 위치 계산
	FVector newLocation = GetActorLocation() + GetActorForwardVector() * moveSpeed * DeltaTime;
	//액터 위치 설정
	SetActorLocation(newLocation);
}

void ABullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//충돌한 상대 액터를 Enemy로 형변환하여 소멸 진행
	AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);
	if (enemy != nullptr)
	{
		//충돌 이펙트 추가
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFX, GetActorTransform());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), explosionFX, GetActorLocation());
		OtherActor->Destroy();
		
		//현재 게임 모드 가져오기
		AGameModeBase* currentGameMode = GetWorld()->GetAuthGameMode();
		AShootingGameModeBase* currenGameModeBase = Cast<AShootingGameModeBase>(currentGameMode);
		if (currenGameModeBase != nullptr)
		{
			currenGameModeBase->AddScore(1);
		}
	}
	//자신도 소멸
	this->Destroy();
}