// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Base/OWGA_Ultimate.h"
#include "AbilitySystem/Effects/OWGE_Cost.h"
#include "AbilitySystem/Attributes/OWAttributeSet.h"

UOWGA_Ultimate::UOWGA_Ultimate()
{
	CostGameplayEffectClass = UOWGE_Cost::StaticClass();
	ActivationRequiredTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("State.UltimateReady")));
}
