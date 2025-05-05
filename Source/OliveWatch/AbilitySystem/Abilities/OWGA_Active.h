// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/OWGameplayAbility.h"
#include "OWGA_Active.generated.h"

/**
 * 쿨타임이 존재하는 능력입니다.
 */
UCLASS()
class OLIVEWATCH_API UOWGA_Active : public UOWGameplayAbility
{
	GENERATED_BODY()

public:
	UOWGA_Active();

	/**
	* 쿨타임에 필요한 데이터를 설정합니다.
	* @param Duration 쿨타임 시간
	* @param Tags 쿨타임 전 재사용을 제약할 태그(InputTags 사용 중)
	*/
	UFUNCTION(BlueprintCallable, Category = "Cooldowns")
	void SetCooldownData(const FScalableFloat& Duration, const FGameplayTagContainer& Tags);

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cooldowns")
	FScalableFloat CooldownDuration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cooldowns")
	FGameplayTagContainer CooldownTags;
};
