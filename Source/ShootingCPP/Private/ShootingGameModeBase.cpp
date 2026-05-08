// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameModeBase.h"

#include "MainWidget.h"
#include "Components/TextBlock.h"

void AShootingGameModeBase::AddScore(int32 point)
{
	currentScore += point;
	PrintScore();
}

void AShootingGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	//mainWidget BP파일을 메모리에 로드
	mainUI = CreateWidget<UMainWidget>(GetWorld(),mainWidget);
	//위젯이 메모리에 로드되면 뷰포트에 출력
	if (mainUI != nullptr)
	{
		mainUI->AddToViewport();
	}
}

void AShootingGameModeBase::PrintScore()
{
	if (mainUI != nullptr)
	{
		mainUI->scoreData->SetText(FText::AsNumber(currentScore));
	}
}
