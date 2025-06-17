// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Genji/OWGA_ShurikenSub.h"

#include "AbilitySystem/Effects/OWGameplayEffect.h"
#include "GameFramework/Character.h"

void UOWGA_ShurikenSub::SetCurrentMontage(UAnimMontage* InCurrentMontage)
{
}

bool UOWGA_ShurikenSub::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	return true;
}

void UOWGA_ShurikenSub::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor);
	if (!Character)
	{
		EndAbility(CurrentSpecHandle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	WeaponComp = ActorInfo->AvatarActor->FindComponentByClass<UOWWeaponComponent>();
	if (!WeaponComp)
	{
		EndAbility(CurrentSpecHandle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	// Animation 실행

	// Animation event에서 실행
	// 지금은 test용으로 여기서 실행
	ShurikenSub();
}

void UOWGA_ShurikenSub::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UOWGA_ShurikenSub::ShurikenSub()
{
	Super::Shoot();

	FVector left(1.0f, -0.3f, 0.0f);
	FVector right(1.0f, 0.3f, 0.0f);
	Super::Shoot(left);
	Super::Shoot(right);

	// 이펙트 실행
	FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(UseBullet, 1.0f);
	ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, SpecHandle);
	ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, SpecHandle);
	ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, SpecHandle);

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
