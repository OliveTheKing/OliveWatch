// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/OWGameplayAbility_GunFire.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "OWGameplayTags.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"

UOWGameplayAbility_GunFire::UOWGameplayAbility_GunFire()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	FGameplayTag Ability1Tag = FGameplayTag::RequestGameplayTag(FName("Ability.Skill.MainFire"));
	AbilityTags.AddTag(Ability1Tag);
	ActivationOwnedTags.AddTag(Ability1Tag);

	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Skill")));

	Range = 1000.0f;
	Damage = 12.0f;
}

void UOWGameplayAbility_GunFire::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (GEngine)
	{
		FString DebugText = FString::Printf(TEXT("�����"));
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, DebugText);
	}

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}

	FireProjectile();

	// 2) ��Ÿ�� + �̺�Ʈ ��� Task
	auto* Task = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this, NAME_None, FireProjectilepMontage);

		//UAbilityTask_PlayMontageAndWait* Task =
		//UAbilityTask_PlayMontageAndWaitForEvent::PlayMontageAndWaitForEvent(
		//	this, NAME_None, FireProjectilepMontage,
		//	/*OnlyTriggerTags=*/FGameplayTagContainer(OWGameplayTags::Notify_Fire));

	Task->ReadyForActivation();

	// 2) GameplayEvent ��������Ʈ ���� ���ε�
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	ASC->GenericGameplayEventCallbacks.FindOrAdd(OWGameplayTags::Notify_Fire)
		.AddUObject(this, &ThisClass::OnFireNotify);
}

void UOWGameplayAbility_GunFire::OnFireNotify(const FGameplayEventData* Data) { FireProjectile(); }

void UOWGameplayAbility_GunFire::FireProjectile()
{
	if (!ProjectileClass || !CurrentActorInfo)
	{
		return;
	}

	// ĳ���� ��������
	ACharacter* Character = Cast<ACharacter>(CurrentActorInfo->AvatarActor.Get());
	if (!Character)
	{
		return;
	}

	// ī�޶� ��ġ�� ���� ��������
	FVector MuzzleLocation;
	FRotator MuzzleRotation;
	Character->GetActorEyesViewPoint(MuzzleLocation, MuzzleRotation);

	// ������Ÿ�� ����
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Character;
	SpawnParams.Instigator = Character;

	AOWProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AOWProjectile>(
		ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

	if (SpawnedProjectile)
	{
		// ������Ÿ�Ͽ� ������ ȿ�� ���� ���� (�ʿ��� ���)
		// SpawnedProjectile->SetDamageEffectClass(DamageEffectClass);
		SpawnedProjectile->FireInDirection(MuzzleRotation.Vector());
	}
}

void UOWGameplayAbility_GunFire::OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData)
{
	/*FString DebugText = FString::Printf(TEXT("�����ҵ�"));
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, DebugText);*/
}

void UOWGameplayAbility_GunFire::OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData)
{
	FString DebugText = FString::Printf(TEXT("����"));
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, DebugText);

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}

void UOWGameplayAbility_GunFire::EventReceived(FGameplayTag EventTag, FGameplayEventData EventData)
{
	FString DebugText = FString::Printf(TEXT("�̺�Ʈ received"));
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, DebugText);
}

