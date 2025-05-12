// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "OWGameplayAbility.generated.h"

class UOWGE_Cost;
/**
 * 
 */
UCLASS()
class OLIVEWATCH_API UOWGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UOWGameplayAbility();

	/**
	* 쿨타임에 필요한 데이터를 설정합니다.
	* @param Duration 쿨타임 시간
	* @param Tags 쿨타임 전 재사용을 제약할 태그(InputTags 사용 중)
	*/
	UFUNCTION(BlueprintCallable, Category = "Cooldowns")
	void SetCooldownData(const FScalableFloat& Duration, const FGameplayTagContainer& Tags);

	/**
	* 코스트에 필요한 데이터를 설정합니다.
	* @param SkillCost 코스트 값(양수)
	* @param Tags 쿨타임 전 재사용을 제약할 태그(InputTags 사용 중)
	*/
	UFUNCTION(BlueprintCallable, Category = "Costs")
	void SetCostEffect(const UOWGE_Cost* CostEffect);

	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	/**
	* 쿨타임 사용에 필요한 코스트
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cooldowns")
	FScalableFloat CooldownDuration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cooldowns")
	FGameplayTagContainer CooldownTags;
};
