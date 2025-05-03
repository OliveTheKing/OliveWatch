// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/OWPlayerState.h"
#include "AbilitySystem/OWAbilitySystemComponent.h"
#include "AbilitySystem/OWAbilitySet.h"
#include "OWPlayerState.h"
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
	AbilitySet->GiveToAbilitySystem(AbilitySystemComponent);
	//for (const FGameplayAbilitySpec& AbilitySpec : AbilitySystemComponent->GetActivatableAbilities())
	//{
	//	AbilitySystemComponent->ActivateAbility(OWGameplayTags::Input_Action_MainFire);
	//}
}

TArray<FGameplayTag> AOWPlayerState::GetCurrentStateTag()
{
	return States;
}

void AOWPlayerState::AddStateTag(FGameplayTag Tag)
{
	if (!Tag.IsValid())
	{
		return;
	}

	// States 안에 이미 Tag가 존재하는지 확인
	for (FGameplayTag& T : States)
	{
		if (T == Tag)
		{
			return;
		}
	}

	States.Add(Tag);
}

void AOWPlayerState::RemoveStateTag(FGameplayTag Tag)
{
	if (!Tag.IsValid())
	{
		return;
	}

	States.Remove(Tag);
}
