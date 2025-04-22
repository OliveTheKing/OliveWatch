// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/OWAbilitySet.h"

#include "AbilitySystem/OWAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/OWGameplayAbility.h"
#include "OWLogChannels.h"

UOWAbilitySet::UOWAbilitySet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// ASC에 ability, effect, attribute 연결하고 활성화
void UOWAbilitySet::GiveToAbilitySystem(UOWAbilitySystemComponent* OWASC) const
{
	check(OWASC);

	// Attribute
	for (int32 i = 0; i < GrantedAttributes.Num(); i++)
	{
		const FOWAbilitySet_AttributeSet& SetToGrant = GrantedAttributes[i];

		if (!IsValid(SetToGrant.AttributeSet))
		{
			UE_LOG(LogOW, Log, TEXT("GrantedAttributes[%d] on ability set [%s] is not valid"), i, *GetNameSafe(this));
			continue;
		}

		UAttributeSet* NewSet = NewObject<UAttributeSet>(OWASC->GetOwner(), SetToGrant.AttributeSet);
		OWASC->AddAttributeSetSubobject(NewSet);
	}

	// Ability
	for (int32 i = 0; i < GrantedGameplayAbilities.Num(); i++)
	{
		FOWAbilitySet_GameplayAbility AbilityToGrant = GrantedGameplayAbilities[i];

		if (!IsValid(AbilityToGrant.Ability))
		{
			UE_LOG(LogOW, Log, TEXT("GrantedGameplayAbilities[%d] on ability set [%s] is not valid."), i, *GetNameSafe(this));
			continue;
		}

		UOWGameplayAbility* AbilityCDO = AbilityToGrant.Ability->GetDefaultObject<UOWGameplayAbility>();

		FGameplayAbilitySpec AbilitySpec(AbilityCDO, AbilityToGrant.AbilityLevel);
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilityToGrant.InputTag);

		const FGameplayAbilitySpecHandle AbilitySpecHandle = OWASC->GiveAbility(AbilitySpec);
	}

	// Effect
	for (int32 i = 0; i < GrantedGameplayEffects.Num(); i++)
	{
		const FOWAbilitySet_GameplayEffect& EffectToGrant = GrantedGameplayEffects[i];

		if (!IsValid(EffectToGrant.GameplayEffect))
		{
			UE_LOG(LogOW, Log, TEXT("GrantedGameplayEffects[%d] on ability set [%s] is not valid"), i, *GetNameSafe(this));
			continue;
		}

		const UGameplayEffect* GameplayEffect = EffectToGrant.GameplayEffect->GetDefaultObject<UGameplayEffect>();
		const FActiveGameplayEffectHandle GameplayEffectHandle = OWASC->ApplyGameplayEffectToSelf(GameplayEffect, EffectToGrant.EffectLevel, OWASC->MakeEffectContext());
	}
}
