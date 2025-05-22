// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Base/OWGameplayAbility.h"
#include "OWGA_Ultimate.generated.h"

/**
 * 궁극기 스킬입니다.
 */
UCLASS()
class OLIVEWATCH_API UOWGA_Ultimate : public UOWGameplayAbility
{
	GENERATED_BODY()

public:
	UOWGA_Ultimate();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "GameplayEffect")
	TSubclassOf<UGameplayEffect> GaugeInitEffect;
};
