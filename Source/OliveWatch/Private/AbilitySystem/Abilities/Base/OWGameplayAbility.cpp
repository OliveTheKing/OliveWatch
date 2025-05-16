// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Base/OWGameplayAbility.h"
#include "AbilitySystem/Effects/OWGE_Cost.h"
#include "AbilitySystem/Attributes/OWAttributeSet.h"
#include "GameplayEffect.h"
#include "AbilitySystem//Effects/OWCooldownGameplayEffect.h"
#include "AbilitySystemComponent.h"


UOWGameplayAbility::UOWGameplayAbility()
{
	CostGameplayEffectClass = UOWGE_Cost::StaticClass();
	CooldownGameplayEffectClass = UOWCooldownGameplayEffect::StaticClass();
}

void UOWGameplayAbility::SetCostEffect(const UOWGE_Cost* CostEffect)
{
	CostGameplayEffectClass = CostEffect->GetClass();
}

void UOWGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
}

void UOWGameplayAbility::SetCooldownData(const FScalableFloat& Duration, const FGameplayTagContainer& Tags) {
	CooldownDuration = Duration;
	CooldownTags = Tags;
}

void UOWGameplayAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCooldown(Handle, ActorInfo, ActivationInfo);

	if (UGameplayEffect* Effect = GetCooldownGameplayEffect()) {

		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(Effect->GetClass(), GetAbilityLevel());

		if (SpecHandle.IsValid())
		{
			SpecHandle.Data->DynamicGrantedTags.AppendTags(CooldownTags);
			SpecHandle.Data->SetDuration(CooldownDuration.GetValueAtLevel(GetAbilityLevel()), true);
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, FString::Printf(TEXT("Cooldown Duration: %f"), SpecHandle.Data->GetDuration()));
			ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
		}
	}
}

bool UOWGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (ActorInfo->AbilitySystemComponent->HasAnyMatchingGameplayTags(CooldownTags))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("Blocked"));
		return false;
	}

	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}
