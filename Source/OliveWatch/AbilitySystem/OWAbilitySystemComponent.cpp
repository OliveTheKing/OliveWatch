// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/OWAbilitySystemComponent.h"

#include "AbilitySystem/Abilities/OWGameplayAbility.h"
#include "AbilitySystem/OWAbilitySet.h"
#include "AbilitySystem/Attributes/OWAttributeSet.h"
#include "Player/OWPlayerState.h"


UOWAbilitySystemComponent::UOWAbilitySystemComponent()
{
	AttributeSet = GetSet<UOWAttributeSet>();
	AttributeSet->ExecuteUpdateData.BindUObject(this, &ThisClass::UpdatePlayerState);
}

void UOWAbilitySystemComponent::UpdatePlayerState(FGameplayTag StateTag)
{
	AOWPlayerState* PS = Cast<AOWPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);
	PS->AddStateTag(StateTag);

}

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
