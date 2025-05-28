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
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
