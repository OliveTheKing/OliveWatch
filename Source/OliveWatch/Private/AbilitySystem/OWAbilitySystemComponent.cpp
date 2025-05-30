// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/OWAbilitySystemComponent.h"

#include "AbilitySystem/Abilities/Base/OWGameplayAbility.h"
#include "AbilitySystem/OWAbilitySet.h"

//void UOWAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<class UGameplayAbility>>& StartupAbilities)
//{
//	for (auto& AbilityClass : StartupAbilities)
//	{
//		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
//		FGameplayAbilitySpecHandle SpecHandle = GiveAbility(AbilitySpec);
//
//		auto& a = ActivatableAbilities;
//
//		SpecHandles.Add(SpecHandle);
//	}
//}

void UOWAbilitySystemComponent::ActivateAbility(FGameplayTag InputTag)
{
	for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
	{
		if (AbilitySpec.Ability && AbilitySpec.GetDynamicSpecSourceTags().HasTag(InputTag))
		{
			TryActivateAbility(AbilitySpec.Handle);	
		}
		
	}
}
