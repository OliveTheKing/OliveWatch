// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/OWGA_Active_GunFire.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "OWGA_ShurikenMain.generated.h"

/**
 *
 */
UCLASS()
class OLIVEWATCH_API UOWGA_ShurikenMain : public UOWGA_Active_GunFire
{
	GENERATED_BODY()

public:
	UOWGA_ShurikenMain();

public:
	virtual void SetCurrentMontage(class UAnimMontage* InCurrentMontage) override;

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

public:
	/**
	* @brief 겐지 수리검(좌클릭) 공격 함수 -> animation event에서 실행
	*/
	UFUNCTION()
	void ShurikenMain();

	UFUNCTION()
	void ThrowFirstShuriken();

	UFUNCTION()
	void ThrowSecondShuriken();

	UFUNCTION()
	void ThrowThirdShuriken();

private:
	UPROPERTY(EditAnywhere, Category = "GAS")
	TSubclassOf<class UOWGameplayEffect> UseBullet;

	UPROPERTY()
	UAbilityTask_WaitDelay* DelayTask;
};
