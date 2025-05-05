// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/OWGameplayAbility.h"
#include "GameplayEffect.h"
#include "AbilitySystem//Effects/OWCooldownGameplayEffect.h"
#include "AbilitySystemComponent.h"



UOWGameplayAbility::UOWGameplayAbility()
{
	CooldownGameplayEffectClass = UOWCooldownGameplayEffect::StaticClass();
}

void UOWGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	/*Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ApplyCooldown(Handle, ActorInfo, ActivationInfo);*/
}

void UOWGameplayAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	//Super::ApplyCooldown(Handle, ActorInfo, ActivationInfo);

	//if (UGameplayEffect* Effect = GetCooldownGameplayEffect()) {

	//	FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(Effect->GetClass(), GetAbilityLevel());

	//	if (SpecHandle.IsValid())
	//	{
	//		SpecHandle.Data->DynamicGrantedTags.AppendTags(CooldownTags);
	//		SpecHandle.Data->SetDuration(CooldownDuration.GetValueAtLevel(GetAbilityLevel()), true);
	//		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, FString::Printf(TEXT("Cooldown Duration: %f"), SpecHandle.Data->GetDuration()));
	//		ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
	//	}
	//}
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
