// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class SHOOTINGCPP_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;
	
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;
	
	UPROPERTY(EditAnywhere)
	float moveSpeed = 800.f;
	
	//충돌 이벤트 함수 OnCompoenentBeginOverlap 델리게이트에 등록할 함수
	UFUNCTION()
	void OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	//구버전 kismet
	//UPROPERTY(EditAnywhere)
	//class UParticleSystem* explosionFX;
	
	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* explosionFX;
};
