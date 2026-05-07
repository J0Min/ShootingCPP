// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class SHOOTINGCPP_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;
	
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;
	
	//IMC 파일의 포인터 함수
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* imcPlayerInput;
	
	UPROPERTY(EditAnywhere)
	class UInputAction* iaHorizontal;
	UPROPERTY(EditAnywhere)
	class UInputAction* iaVertical;
	UPROPERTY(EditAnywhere)
	class UInputAction* iaFire;
	
	UPROPERTY(EditAnywhere)
	float movespeed = 500.f;
	
	//총구(총알 발사 위치)
	UPROPERTY(EditAnywhere)
	class UArrowComponent* firePosition;
	//생성할 총알 BP
	//원본 파일을 변수에 할당을 위한 TSubclassOf 타입 사용
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet> bulletFactory;
	UPROPERTY(EditAnywhere)
	class USoundBase* fireSound;
private:
	float h, v;
	
	void OnInputHorizontal(const struct FInputActionValue& value);
	void OnInputVertical(const struct FInputActionValue& value);
	void Fire();
};
