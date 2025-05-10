// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "OWReloadOverride.generated.h"

/**
 * 
 */
UCLASS()
class OLIVEWATCH_API UOWReloadOverride : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UOWReloadOverride();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	UPROPERTY()
	FGameplayEffectAttributeCaptureDefinition MaxBulletsDef;
};
