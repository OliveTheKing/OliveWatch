// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Effects/OWGameplayEffect.h"
#include "OWGE_Sleep.generated.h"

/**
 * 
 */
UCLASS()
class OLIVEWATCH_API UOWGE_Sleep : public UOWGameplayEffect
{
	GENERATED_BODY()
	
public:
	UOWGE_Sleep(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void InitSleepEffect(float SleepDuration);
};
