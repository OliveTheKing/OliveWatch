// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayEffectTypes.h"
#include "OWOverlapHandlerComponent.generated.h"

class AOWCharacter;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OLIVEWATCH_API UOWOverlapHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UOWOverlapHandlerComponent();

	virtual void Initialize(AOWCharacter* InInstigator, const TArray<FGameplayEffectSpecHandle>& InEffectSpecs);
	virtual void OverlapTarget(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<class AOWCharacter> Instigator;

	UPROPERTY()
	TArray<FGameplayEffectSpecHandle> EffectSpecs;
};
