// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Base/OWGA_Ultimate.h"
#include "AbilitySystem/Effects/OWGE_Cost.h"
#include "AbilitySystem/Effects/OWGE_InitUltimateGauge.h"
#include "AbilitySystem/Attributes/OWAttributeSet.h"

UOWGA_Ultimate::UOWGA_Ultimate()
{
	GaugeInitEffect = UOWGE_InitUltimateGauge::StaticClass();
	CostGameplayEffectClass = UOWGE_Cost::StaticClass();
	ActivationRequiredTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("State.UltimateReady")));
}

void UOWGA_Ultimate::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(GaugeInitEffect);
	if (SpecHandle.IsValid())
	{
		GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}
