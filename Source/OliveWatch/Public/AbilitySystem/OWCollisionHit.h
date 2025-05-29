// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OWCollisionHit.generated.h"

class UOWHitHandlerComponent;
class UOWOverlapHandlerComponent;
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
	TArray<FGameplayEffectSpecHandle> HitEffectSpec;
	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	TArray<FGameplayEffectSpecHandle> OverlapEffectSpec;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	//Trigger 감지 함수
	UFUNCTION()
	virtual void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	//충돌 감지 함수
	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit
	);

	//충돌/Trigger을 감지하기 위한 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	TObjectPtr<UPrimitiveComponent> CollisionComp;

	//충돌 시 발생할 일을 정의한 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	TObjectPtr<UOWHitHandlerComponent> HitHandler;

	//Trigger 시 발생할 일을 정의한 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	TObjectPtr<UOWOverlapHandlerComponent> OverlapHandler;
};
