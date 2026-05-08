// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameModeBase.h"
#include "MenuWidget.h"
#include "MainWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

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

//게임 오버 메뉴 위젯 출력 함수
// void AShootingGameModeBase::ShowMenu()
// {
// 	if (menuWidget != nullptr)
// 	{
// 		menuUI = CreateWidget<UMenuWidget>(GetWorld(),menuWidget);
// 		if (menuUI != nullptr)
// 		{
// 			menuUI->AddToViewport();
// 			//메뉴 등장시 게임 일시 정지
// 			UGameplayStatics::SetGamePaused(GetWorld(),true);
// 			GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
// 		}
// 	}
// }

void AShootingGameModeBase::ShowMenu()
{
	if (menuWidget != nullptr)
	{
		// 메뉴 위젯 생성
		menuUI = CreateWidget<UMenuWidget>(GetWorld(), menuWidget);
		
		if (menuUI != nullptr)
		{
			menuUI->AddToViewport();
			// 메뉴 등장 시, 게임 일시 정지
			UGameplayStatics::SetGamePaused(GetWorld(), true);
			// 컨트롤러에서 마우스 커서 보이게 하기
			GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
		}
	}
}