// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/OWGameplayAbility.h"
#include "OliveWatchProjectile.h"
//#include "AbilitySystem/OWProjectile.h"
#include "OWGameplayAbility_GunFire.generated.h"

/**
 * 
 */
UCLASS()
class OLIVEWATCH_API UOWGameplayAbility_GunFire : public UOWGameplayAbility
{
	GENERATED_BODY()

public:
	UOWGameplayAbility_GunFire();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UAnimMontage* FireProjectilepMontage;

	// Projectile을 쓸 경우 사용할 Projectile 클래스
	UPROPERTY(EditDefaultsOnly, Category = "GunFire")
	TSubclassOf<AOliveWatchProjectile> ProjectileClass;

	// Raytrace를 쓸 경우 최대 사거리
	UPROPERTY(EditDefaultsOnly, Category = "GunFire")
	float MaxTraceDistance = 10000.0f;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void FireProjectile();

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Range;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Damage;

	UFUNCTION()
	void OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION()
	void OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION()
	void EventReceived(FGameplayTag EventTag, FGameplayEventData EventData);
	void OnFireNotify(const FGameplayEventData* Data);
};
