// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/OWGA_Active_GunFire.h"
#include "AbilitySystem/Tasks/OWGT_PlayMontageAndWaitForEvent.h"
#include "GameFramework/Character.h"
#include "OWGameplayTags.h"
#include "AbilitySystemComponent.h"
#include "Weapon/OWWeaponComponent.h"

UOWGA_Active_GunFire::UOWGA_Active_GunFire()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	FGameplayTag Ability1Tag = FGameplayTag::RequestGameplayTag(FName("Input.Action.MainFire"));
	AbilityTags.AddTag(Ability1Tag);
	ActivationOwnedTags.AddTag(Ability1Tag);

	// ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Event.Montage.SpawnProjectile")));
}


void UOWGA_Active_GunFire::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UOWWeaponComponent* WeaponComp =
		ActorInfo->AvatarActor->FindComponentByClass<UOWWeaponComponent>();

	if (!WeaponComp) { EndAbility(CurrentSpecHandle, ActorInfo, ActivationInfo, true, true); return; }
	WeaponComp->StartFire();

	// ③ Ability 자체는 더 할 일 없으면 바로 종료해도 무방
	EndAbility(CurrentSpecHandle, ActorInfo, ActivationInfo, false, false);
}

