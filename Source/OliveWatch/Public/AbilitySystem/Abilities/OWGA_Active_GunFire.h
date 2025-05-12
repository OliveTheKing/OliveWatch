// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Base/OWGA_Active.h"
// #include "AbilitySystem/OWTmpProjectile.h"
#include "OWProjectile.h"
#include "OWGA_Active_GunFire.generated.h"

/**
 * 
 */
UCLASS()
class OLIVEWATCH_API UOWGA_Active_GunFire : public UOWGA_Active
{
	GENERATED_BODY()

public:
	UOWGA_Active_GunFire();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UAnimMontage* FireProjectilepMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UGameplayEffect> DamageGameplayEffect;

	// Projectile을 쓸 경우 사용할 Projectile 클래스
	UPROPERTY(EditDefaultsOnly, Category = "GunFire")
	TSubclassOf<AOWProjectile> ProjectileClass;
	// TSubclassOf<AOWTmpProjectile> ProjectileClass;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

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

	UFUNCTION()
	void SpawnProjectile();
};
