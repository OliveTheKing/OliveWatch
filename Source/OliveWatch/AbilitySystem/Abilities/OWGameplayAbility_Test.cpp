// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/OWGameplayAbility_Test.h"

#include "OliveWatchCharacter.h"
#include "OWLogChannels.h"


//UOWGameplayAbility_Test::UOWGameplayAbility_Test(const FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//{
//}

bool UOWGameplayAbility_Test::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		return false;
	}

	return true;
}

void UOWGameplayAbility_Test::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("Attack!"));
	AOliveWatchCharacter* Player = Cast<AOliveWatchCharacter>(ActorInfo->AvatarActor);
	Player->Jump();

}

void UOWGameplayAbility_Test::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("Ability End"));
}
