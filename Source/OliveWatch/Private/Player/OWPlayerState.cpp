// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/OWPlayerState.h"
#include "AbilitySystem/OWAbilitySystemComponent.h"
#include "OWGameplayTags.h"
#include "OWLogChannels.h"


AOWPlayerState::AOWPlayerState(const FObjectInitializer& ObjectInitializer)
	:	Super(ObjectInitializer)
{
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UOWAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	//AbilitySet = ObjectInitializer.CreateDefaultSubobject<UOWAbilitySet>(this, TEXT("AbilitySet"));
	//AbilitySet->GiveToAbilitySystem(AbilitySystemComponent);
}

UAbilitySystemComponent* AOWPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UOWAbilitySystemComponent* AOWPlayerState::GetOWAbilitySystemComponent()
{
	return AbilitySystemComponent;
}

void AOWPlayerState::BeginPlay()
{
	//for (const FGameplayAbilitySpec& AbilitySpec : AbilitySystemComponent->GetActivatableAbilities())
	//{
	//	AbilitySystemComponent->ActivateAbility(OWGameplayTags::Input_Action_MainFire);
	//}
}
