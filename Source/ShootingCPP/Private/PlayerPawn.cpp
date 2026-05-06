// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/BoxComponent.h"


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
	}
}

