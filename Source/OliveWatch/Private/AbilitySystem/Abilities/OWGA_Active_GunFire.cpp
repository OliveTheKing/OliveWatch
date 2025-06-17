// Fill out your copyright notice in the Description page of Project Settings.
#include "AbilitySystem/Abilities/OWGA_Active_GunFire.h"
#include "AbilitySystem/Tasks/OWGT_PlayMontageAndWaitForEvent.h"
#include "GameFramework/Character.h"
#include "OWGameplayTags.h"
#include "AbilitySystemComponent.h"


UOWGA_Active_GunFire::UOWGA_Active_GunFire()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	SetAssetTags(FGameplayTagContainer(FGameplayTag::RequestGameplayTag("Input.Action.MainFire")));
	CooldownTags.AddTag(OWGameplayTags::Ability_GunFire);
	ActivationBlockedTags.AddTag(OWGameplayTags::Ability_GunFire);
}


void UOWGA_Active_GunFire::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

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
	
	Shoot();

	EndAbility(CurrentSpecHandle, ActorInfo, ActivationInfo, false, false);
}

void UOWGA_Active_GunFire::Shoot(FVector Direction)
{
	if (!WeaponComp)
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponComponent is nullptr!"));
		return;
	}

	UOWFireDataAsset* FD = WeaponComp->GetFireData();
	if (FD)
	{
		UAnimMontage* FireMontage = FD->FireMontage.ShooteMontage;
		// TASK ³Ö±â

		FGameplayEffectSpecHandle DamageEffectSpecHandle = MakeOutgoingGameplayEffectSpec(FD->FirePattern.DamageGameplayEffect, GetAbilityLevel());
		DamageEffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("Input.Action.MainFire"), FD->FirePattern.Damage);
		WeaponComp->StartFire(Direction, DamageEffectSpecHandle);
	}
}