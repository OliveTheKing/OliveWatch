// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Effects/OWGameplayEffect.h"
#include "OWCooldownGameplayEffect.generated.h"

/**
 * 
 */
UCLASS()
class OLIVEWATCH_API UOWCooldownGameplayEffect : public UOWGameplayEffect
{
	GENERATED_BODY()

public:

	UOWCooldownGameplayEffect() {
		DurationPolicy = EGameplayEffectDurationType::HasDuration;
	}
	
};
