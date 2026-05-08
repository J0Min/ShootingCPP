// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* buttonRestart;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* buttonQuit;
protected:
	//위젯 초기화 함수
	virtual void NativeConstruct() override;
private:
	UFUNCTION()
	void Restart();
	UFUNCTION()
	void Quit();
};
