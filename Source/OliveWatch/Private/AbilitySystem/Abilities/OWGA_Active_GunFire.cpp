// Fill out your copyright notice in the Description page of Project Settings.
#include "AbilitySystem/Abilities/OWGA_Active_GunFire.h"
#include "AbilitySystem/Tasks/OWGT_PlayMontageAndWaitForEvent.h"
#include "GameFramework/Character.h"
#include "Weapon/OWFireDataAsset.h"
#include "OWGameplayTags.h"
#include "AbilitySystemComponent.h"
#include "Weapon/OWWeaponComponent.h"

UOWGA_Active_GunFire::UOWGA_Active_GunFire()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	SetAssetTags(FGameplayTagContainer(FGameplayTag::RequestGameplayTag("Input.Action.MainFire")));
}


void UOWGA_Active_GunFire::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UOWWeaponComponent* WeaponComp =
		ActorInfo->AvatarActor->FindComponentByClass<UOWWeaponComponent>();

	if (!WeaponComp) 
	{ 
		EndAbility(CurrentSpecHandle, ActorInfo, ActivationInfo, true, true); 
		return; 
	}
	
	UOWFireDataAsset* FD = WeaponComp->GetFireData();
	if (FD) 
	{
		FGameplayEffectSpecHandle DamageEffectSpecHandle = MakeOutgoingGameplayEffectSpec(FD->FirePattern.DamageGameplayEffect, GetAbilityLevel());
		DamageEffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("Input.Action.MainFire"), FD->FirePattern.Damage);
		WeaponComp->StartFire(DamageEffectSpecHandle);
	}

	EndAbility(CurrentSpecHandle, ActorInfo, ActivationInfo, false, false);
}

