// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Genji/OWGA_ShurikenMain.h"

#include "AbilitySystem/Effects/OWGameplayEffect.h"

UOWGA_ShurikenMain::UOWGA_ShurikenMain()
{
}

void UOWGA_ShurikenMain::SetCurrentMontage(UAnimMontage* InCurrentMontage)
{
}

bool UOWGA_ShurikenMain::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	return true;
}

void UOWGA_ShurikenMain::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	// Animation 실행

	// Animation event에서 실행
	// 지금은 test용으로 여기서 실행
	ShurikenMain();

}

void UOWGA_ShurikenMain::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UOWGA_ShurikenMain::ShurikenMain()
{
	ThrowFirstShuriken();
}

void UOWGA_ShurikenMain::ThrowFirstShuriken()
{
	Shoot();

	// 이펙트 실행
	FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(UseBullet, 1.0f);
	ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, SpecHandle);

	// 다음 표창까지 딜레이
	DelayTask = UAbilityTask_WaitDelay::WaitDelay(this, 0.1f);
	DelayTask->OnFinish.AddDynamic(this, &UOWGA_ShurikenMain::ThrowSecondShuriken);
	DelayTask->ReadyForActivation();

}

void UOWGA_ShurikenMain::ThrowSecondShuriken()
{
	Shoot();

	// 이펙트 실행
	FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(UseBullet, 1.0f);
	ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, SpecHandle);

	// 다음 표창까지 딜레이
	DelayTask = UAbilityTask_WaitDelay::WaitDelay(this, 0.1f);
	DelayTask->OnFinish.AddDynamic(this, &UOWGA_ShurikenMain::ThrowThirdShuriken);
	DelayTask->ReadyForActivation();
}

void UOWGA_ShurikenMain::ThrowThirdShuriken()
{
	Shoot();

	// 이펙트 실행
	FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(UseBullet, 1.0f);
	ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, SpecHandle);

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
