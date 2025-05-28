// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OWCollisionHit.generated.h"

class UOWHitHandlerComponent;
struct FGameplayEffectSpecHandle;
class USphereComponent;

//충돌 처리 담당 클래스(타격체에 붙는 클래스)
UCLASS()
class OLIVEWATCH_API AOWCollisionHit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOWCollisionHit();

	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	TArray<FGameplayEffectSpecHandle> EffectSpec;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	//충돌을 감지하는 함수
	UFUNCTION()
	virtual void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	//충돌을 감지하기 위한 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	USphereComponent* CollisionComp;

	UPROPERTY(EditAnywhere, Category = Collision)
	UOWHitHandlerComponent* HitHandler;
};
