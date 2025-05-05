// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/OWGA_Ultimate.h"
#include "AbilitySystem/Effects/OWGE_Cost.h"
#include "AbilitySystem/Attributes/OWAttributeSet.h"

UOWGA_Ultimate::UOWGA_Ultimate()
{
	CostGameplayEffectClass = UOWGE_Cost::StaticClass();
}

bool UOWGA_Ultimate::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	bool bFound = false;
	float CurrentUltCost = ActorInfo->AbilitySystemComponent->GetGameplayAttributeValue(UOWAttributeSet::GetUltimateCostAttribute(), bFound);
	if (!bFound) {
		return false;
	}
	else if (CurrentUltCost > UltCost.GetValue()) {
		return true;
	}
	return false;
}

// @todo 매번 GetClass 대신 캐싱을 하는 것도...
void UOWGA_Ultimate::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
	if (UGameplayEffect* Effect = GetCostGameplayEffect()) {
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(Effect->GetClass(), GetAbilityLevel());
		if (SpecHandle.IsValid())
		{
			ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
		}
	}
}

void UOWGA_Ultimate::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
}
