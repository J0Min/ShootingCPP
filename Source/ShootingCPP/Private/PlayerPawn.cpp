// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "Bullet.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
	
	//총구 컴포넌트 생성 및 계층 구조 정리
	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Fire Component"));
	firePosition->SetupAttachment(boxComp);
	
	/*
	//충돌 채널으 cpp에서 직접 설정
	//코드 가독성 감소
	//충돌 설정은 채널/응답 조합이 복잡해질 가능성이 높아, 언리얼 에디터 프리셋을 통환 관리가 유리
	boxComp->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);//player
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	boxComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	boxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);//Enemy
	*/
	
	//에디터에서 생성할 프리셋 이름을 컴포넌트에 세팅
	boxComp->SetCollisionProfileName(TEXT("Player"));
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	//컨트롤러
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if (pc != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* subsys = 
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if (subsys != nullptr){}
		subsys->AddMappingContext(imcPlayerInput, 0);
	}
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector dir = FVector(0,h,v);
	dir.Normalize();//정규화
	FVector newLocation = GetActorLocation() + dir * movespeed * DeltaTime;
	SetActorLocation(newLocation);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* eic = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (eic != nullptr)
	{
		eic->BindAction(iaHorizontal, ETriggerEvent::Triggered, this, &APlayerPawn::OnInputHorizontal);
		eic->BindAction(iaHorizontal, ETriggerEvent::Completed, this, &APlayerPawn::OnInputHorizontal);
		eic->BindAction(iaVertical, ETriggerEvent::Triggered, this, &APlayerPawn::OnInputVertical);
		eic->BindAction(iaVertical, ETriggerEvent::Completed, this, &APlayerPawn::OnInputVertical);
		
		eic->BindAction(iaFire, ETriggerEvent::Started, this, &APlayerPawn::Fire);
	}
}

//사용자가 키를 누르면 홏풀되어, 변수를 재할당 하는 함수
void APlayerPawn::OnInputHorizontal(const struct FInputActionValue& value)
{
	h = value.Get<float>();
}

void APlayerPawn::OnInputVertical(const struct FInputActionValue& value)
{
	v = value.Get<float>();
}

void APlayerPawn::Fire()
{
	ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory,
		firePosition->GetComponentLocation(), firePosition->GetComponentRotation());
	
	UGameplayStatics::PlaySound2D(GetWorld(),fireSound);
}
