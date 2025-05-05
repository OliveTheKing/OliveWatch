// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/OWGameplayAbility_GunFire.h"
//#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Animation/AnimMontage.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "OWGameplayTags.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"

UOWGameplayAbility_GunFire::UOWGameplayAbility_GunFire()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	FGameplayTag Ability1Tag = FGameplayTag::RequestGameplayTag(FName("Input.Action.MainFire"));
	AbilityTags.AddTag(Ability1Tag);
	ActivationOwnedTags.AddTag(Ability1Tag);

	//ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Skill")));
	
	Range = 1000.0f;
	Damage = 12.0f;
}

void UOWGameplayAbility_GunFire::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
	
	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	if (Character)
	{
		UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
		if (AnimInstance && FireProjectilepMontage)
		{
			AnimInstance->Montage_Play(FireProjectilepMontage);
		}
	}
	//// 2) 몽타주 + 이벤트 대기 Task
	//auto* Task = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
	//	this, NAME_None, FireProjectilepMontage);

	//	//UAbilityTask_PlayMontageAndWait* Task =
	//	//UAbilityTask_PlayMontageAndWaitForEvent::PlayMontageAndWaitForEvent(
	//	//	this, NAME_None, FireProjectilepMontage,
	//	//	/*OnlyTriggerTags=*/FGameplayTagContainer(OWGameplayTags::Notify_Fire));

	//Task->ReadyForActivation();

	//// 2) GameplayEvent 델리게이트 따로 바인딩
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	ASC->GenericGameplayEventCallbacks.FindOrAdd(OWGameplayTags::Notify_Fire)
		.AddUObject(this, &ThisClass::OnFireNotify);
}

void UOWGameplayAbility_GunFire::OnFireNotify(const FGameplayEventData* Data) 
{
	{
		FString DebugText = FString::Printf(TEXT("실행됨 발사! activate"));
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, DebugText);
	}
	FireProjectile();
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UOWGameplayAbility_GunFire::FireProjectile()
{
	if (!ProjectileClass|| !CurrentActorInfo)
	{
		return;
	}

	// 캐릭터 가져오기
	ACharacter* Character = Cast<ACharacter>(CurrentActorInfo->AvatarActor.Get());
	if (!Character)
	{
		return;
	}

	// 카메라 위치와 방향 가져오기
	FVector MuzzleLocation;
	FRotator MuzzleRotation;
	Character->GetActorEyesViewPoint(MuzzleLocation, MuzzleRotation);

	// 프로젝타일 스폰
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Character;
	SpawnParams.Instigator = Character;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AOWProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AOWProjectile>(
		ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

	if (SpawnedProjectile)
	{
		UE_LOG(LogTemp, Warning, TEXT("GunFire 실행됨"));

		// 프로젝타일에 데미지 효과 정보 전달
		// SpawnedProjectile->SetDamageEffectClass(DamageEffectClass);
		//SpawnedProjectile->FireInDirection(MuzzleRotation.Vector());
	}
}

void UOWGameplayAbility_GunFire::OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData)
{
	/*FString DebugText = FString::Printf(TEXT("취소취소됨"));
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, DebugText);*/
}

void UOWGameplayAbility_GunFire::OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData)
{
	FString DebugText = FString::Printf(TEXT("끝남"));
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, DebugText);

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}

void UOWGameplayAbility_GunFire::EventReceived(FGameplayTag EventTag, FGameplayEventData EventData)
{
	FString DebugText = FString::Printf(TEXT("이벤트 received"));
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, DebugText);
}

