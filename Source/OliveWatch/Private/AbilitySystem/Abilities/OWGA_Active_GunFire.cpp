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

/// <summary>
/// 해당 함수는 더이상 사용되지 않습니다.
/// </summary>
void UOWGA_Active_GunFire::SpawnProjectile()
{
	ACharacter* Character = Cast<ACharacter>(CurrentActorInfo->AvatarActor.Get());
	if (!Character)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}

	//// 카메라 위치와 방향 가져오기
	//FVector MuzzleLocation;
	//FRotator MuzzleRotation;
	//Character->GetActorEyesViewPoint(MuzzleLocation, MuzzleRotation);

	//FGameplayEffectSpecHandle DamageEffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageGameplayEffect, GetAbilityLevel());

	//// Pass the damage to the Damage Execution Calculation through a SetByCaller value on the GameplayEffectSpec
	//DamageEffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), Damage);

	//AOWProjectile* Projectile = GetWorld()->SpawnActorDeferred<AOWProjectile>(
	//	ProjectileClass,
	//	FTransform(MuzzleRotation, MuzzleLocation),
	//	GetOwningActorFromActorInfo(),
	//	Character,
	//	ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	//);

	//Projectile->DamageSpecHandle = DamageEffectSpecHandle;
	//// Projectile->Range = Range;

	//Projectile->FinishSpawning(FTransform(MuzzleRotation, MuzzleLocation));
}
