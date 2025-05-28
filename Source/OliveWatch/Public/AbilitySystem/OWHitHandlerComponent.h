// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayEffectTypes.h"
#include "OWHitHandlerComponent.generated.h"

class AOWCharacter;

//타격 담당 컴포넌트
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OLIVEWATCH_API UOWHitHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOWHitHandlerComponent();

	virtual void Initialize(AOWCharacter* InInstigator, const TArray<FGameplayEffectSpecHandle>& InEffectSpecs);
	virtual void HitTarget(AActor* TargetActor, UPrimitiveComponent* OtherComp);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<class AOWCharacter> Instigator;

	UPROPERTY()
	TArray<FGameplayEffectSpecHandle> EffectSpecs;
};
