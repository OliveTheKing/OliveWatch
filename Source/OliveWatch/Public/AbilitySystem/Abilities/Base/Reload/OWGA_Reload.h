// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Base/OWGA_Passive.h"
#include "OWGA_Reload.generated.h"

/**
 * 
 */
UCLASS()
class OLIVEWATCH_API UOWGA_Reload : public UOWGA_Passive
{
	GENERATED_BODY()
	
public:
	virtual void SetCurrentMontage(class UAnimMontage* InCurrentMontage) override;

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

public:
	/**
	* @brief 탄창 재장전 함수 -> animation event에서 실행
	*/
	void Reload();

private:
	UPROPERTY(EditAnywhere, Category = "GAS")
	TSubclassOf<class UOWGameplayEffect> ReloadEffect;

};
