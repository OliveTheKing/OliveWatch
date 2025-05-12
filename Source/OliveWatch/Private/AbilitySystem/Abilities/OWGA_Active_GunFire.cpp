// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/OWGA_Active_GunFire.h"
#include "AbilitySystem/Tasks/OWGT_PlayMontageAndWaitForEvent.h"
#include "GameFramework/Character.h"
#include "OWGameplayTags.h"
#include "AbilitySystemComponent.h"

UOWGA_Active_GunFire::UOWGA_Active_GunFire()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	FGameplayTag Ability1Tag = FGameplayTag::RequestGameplayTag(FName("Input.Action.MainFire"));
	AbilityTags.AddTag(Ability1Tag);
	ActivationOwnedTags.AddTag(Ability1Tag);

	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Event.Montage.SpawnProjectile")));

	Range = 1000.0f;
	Damage = 12.0f;
}


void UOWGA_Active_GunFire::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	SpawnProjectile();
	UAnimMontage* MontageToPlay = FireProjectilepMontage;

	UOWGT_PlayMontageAndWaitForEvent* Task = UOWGT_PlayMontageAndWaitForEvent::PlayMontageAndWaitForEvent(this, NAME_None, MontageToPlay, FGameplayTagContainer(), 1.0f, NAME_None, false, 1.0f);
	Task->OnBlendOut.AddDynamic(this, &UOWGA_Active_GunFire::OnCompleted);
	Task->OnCompleted.AddDynamic(this, &UOWGA_Active_GunFire::OnCompleted);
	Task->OnInterrupted.AddDynamic(this, &UOWGA_Active_GunFire::OnCancelled);
	Task->OnCancelled.AddDynamic(this, &UOWGA_Active_GunFire::OnCancelled);
	Task->EventReceived.AddDynamic(this, &UOWGA_Active_GunFire::EventReceived);
	// ReadyForActivation() is how you activate the AbilityTask in C++. Blueprint has magic from K2Node_LatentGameplayTaskCall that will automatically call ReadyForActivation().
	Task->ReadyForActivation();
}

void UOWGA_Active_GunFire::OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UOWGA_Active_GunFire::OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UOWGA_Active_GunFire::EventReceived(FGameplayTag EventTag, FGameplayEventData EventData)
{
	FString TagString = EventTag.ToString();
	FString Message = FString::Printf(TEXT("Received! %s"), *TagString);
	GEngine->AddOnScreenDebugMessage(
		-1,               // Key: -1이면 새 메시지
		5.0f,             // 몇 초 보여줄지
		FColor::Green,    // 색깔
		Message
	);
	// Montage told us to end the ability before the montage finished playing.
	// Montage was set to continue playing animation even after ability ends so this is okay.
	if (EventTag == FGameplayTag::RequestGameplayTag(FName("Event.Montage.EndAbility")))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
		return;
	}

	// Only spawn projectiles on the Server.
	// Predicting projectiles is an advanced topic not covered in this example.
	// if (GetOwningActorFromActorInfo()->GetLocalRole() == ROLE_Authority && EventTag == FGameplayTag::RequestGameplayTag(FName("Event.Montage.SpawnProjectile")))
	if (EventTag == FGameplayTag::RequestGameplayTag(FName("Event.Montage.SpawnProjectile")))
	{
		/*if (!ProjectileClass || !CurrentActorInfo)
		{
			return;
		}*/
		SpawnProjectile();
	}
}

void UOWGA_Active_GunFire::SpawnProjectile()
{
	//GEngine->AddOnScreenDebugMessage(
	//	-1,               // Key: -1이면 새 메시지
	//	5.0f,             // 몇 초 보여줄지
	//	FColor::Green,    // 색깔
	//	TEXT("Hello, OliveWatch!")  // 내용
	//);
	ACharacter* Character = Cast<ACharacter>(CurrentActorInfo->AvatarActor.Get());
	if (!Character)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}

	// 카메라 위치와 방향 가져오기
	FVector MuzzleLocation;
	FRotator MuzzleRotation;
	Character->GetActorEyesViewPoint(MuzzleLocation, MuzzleRotation);

	FGameplayEffectSpecHandle DamageEffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageGameplayEffect, GetAbilityLevel());

	// Pass the damage to the Damage Execution Calculation through a SetByCaller value on the GameplayEffectSpec
	DamageEffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), Damage);

	AOWProjectile* Projectile = GetWorld()->SpawnActorDeferred<AOWProjectile>(
		ProjectileClass,
		FTransform(MuzzleRotation, MuzzleLocation),
		GetOwningActorFromActorInfo(),
		Character,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	Projectile->DamageSpecHandle = DamageEffectSpecHandle;
	// Projectile->Range = Range;

	Projectile->FinishSpawning(FTransform(MuzzleRotation, MuzzleLocation));
}
