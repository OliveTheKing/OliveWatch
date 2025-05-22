// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Effects/OWGameplayEffect.h"
#include "AbilitySystem/Attributes/OWAttributeSet.h"
#include "OWGE_InitUltimateGauge.generated.h"

/**
 * 
 */
UCLASS()
class OLIVEWATCH_API UOWGE_InitUltimateGauge : public UOWGameplayEffect
{
	GENERATED_BODY()
	
public:
	UOWGE_InitUltimateGauge() {
		DurationPolicy = EGameplayEffectDurationType::Instant;

		FGameplayModifierInfo ModInfo;
		ModInfo.Attribute = UOWAttributeSet::GetUltimateGaugeAttribute();
		ModInfo.ModifierOp = EGameplayModOp::Override;
		ModInfo.ModifierMagnitude = FScalableFloat(0.0f);

		Modifiers.Add(ModInfo);
	}
};
