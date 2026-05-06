// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodingTestActor_.generated.h"

UCLASS()
class SHOOTINGCPP_API ACodingTestActor_ : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACodingTestActor_();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//기본 자료형 변수
	UPROPERTY(EditAnywhere)//블프 설정창에서 변경 가능, 레벨에 배치된 액터(인스턴스) 가능
	int32 num1 = 32;
	UPROPERTY(VisibleAnywhere)//값은 보지만 수정불가 코드에서만 수정 가능
	float num2 = 3.14f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)//블프이벤트 그래프에서 읽기쓰기 가능
	int32 num3 = 40;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)//블프 이벤트에서 읽기만 가능
	int32 num4 = 50;
	UPROPERTY(EditInstanceOnly) //레벨에 배치된 객체에서 변경
	FString name = TEXT("FString");
	//인스턴스와 디폴트는 상반
	UPROPERTY(EditDefaultsOnly)//블프 설정에서만 수정가능
	bool isReady = false;

	UFUNCTION(BlueprintCallable)//블프에서 함수 호출가능
	int32 AddCustom(int32 a, int32 b);
};