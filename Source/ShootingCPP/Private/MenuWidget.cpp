// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	//각 버튼 클릭 이벤트에 대응 함수 연결
	buttonRestart->OnClicked.AddDynamic( this, &UMenuWidget::Restart);
	buttonQuit->OnClicked.AddDynamic( this, &UMenuWidget::Quit);
}

void UMenuWidget::Restart()
{
	UGameplayStatics::OpenLevel(GetWorld(),TEXT("ShootingMap"));
}

void UMenuWidget::Quit()
{
	UWorld* currentWorld = GetWorld();
	UKismetSystemLibrary::QuitGame(currentWorld, currentWorld->GetFirstPlayerController(), EQuitPreference::Quit,false);
}
