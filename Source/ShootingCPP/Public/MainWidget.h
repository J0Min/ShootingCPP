// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//점수 텍스트 컴포넌트 . 언리얼에디터 위젯에서 BP에서 같은 이름으로 바인딩
	UPROPERTY(EditAnywhere, meta = (BindWidget))//meta 파라미터 - 정보데이터 
	//(변수노출시킬떄, 코드와 이름을 다르게 하거나, 입력값을 특정 범위로 제한하는 등의 사용)
	class UTextBlock* scoreText;
	
	//점수 UI 갱신 변수
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* scoreData;
};
