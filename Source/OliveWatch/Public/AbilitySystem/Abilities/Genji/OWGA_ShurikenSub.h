// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/OWGA_Active_GunFire.h"
#include "OWGA_ShurikenSub.generated.h"

/**
 * 
 */
UCLASS()
class OLIVEWATCH_API UOWGA_ShurikenSub : public UOWGA_Active_GunFire
{
	GENERATED_BODY()
	
public:
	virtual void SetCurrentMontage(class UAnimMontage* InCurrentMontage) override;

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

public:
	/**
	* @brief 겐지 수리검(우클릭) 공격 함수 -> animation event에서 실행
	*/
	UFUNCTION()
	void ShurikenSub();

	/**
	* @brief 발사체 생성 함수 SpawnProjectile() 오버로딩
	* @param Direction: 발사체 날아가는 방향 설정
	*/
	void SpawnProjectile(FVector Direction);

private:
	UPROPERTY(EditAnywhere, Category = "GAS")
	TSubclassOf<class UOWGameplayEffect> UseBullet;
};
