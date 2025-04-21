// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/OWAbilitySystemComponent.h"

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

void UOWAbilitySystemComponent::ActivateAbility(FGameplayTag AbilityTag)
{
	for (FGameplayAbilitySpecHandle& SpecHandle : SpecHandles)
	{
		TryActivateAbility(SpecHandle);
	}
}
