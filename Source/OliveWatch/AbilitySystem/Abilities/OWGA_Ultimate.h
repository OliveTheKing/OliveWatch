// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/OWGameplayAbility.h"
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

	virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	/**
	* 궁극기 사용에 필요한 코스트
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Costs")
	FScalableFloat UltCost;
};
