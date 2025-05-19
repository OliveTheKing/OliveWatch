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
	Super::SpawnProjectile();

	FVector left(1.0f, -0.3f, 0.0f);
	FVector right(1.0f, 0.3f, 0.0f);
	SpawnProjectile(left);
	SpawnProjectile(right);

	// 이펙트 실행
	FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(UseBullet, 1.0f);
	ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, SpecHandle);
	ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, SpecHandle);
	ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, SpecHandle);

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UOWGA_ShurikenSub::SpawnProjectile(FVector Direction)
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
		FTransform(MuzzleRotation, MuzzleLocation + Direction),
		GetOwningActorFromActorInfo(),
		Character,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	Projectile->SetProjectileVelocity(Direction);
	Projectile->DamageSpecHandle = DamageEffectSpecHandle;
	// Projectile->Range = Range;

	Projectile->FinishSpawning(FTransform(MuzzleRotation, MuzzleLocation));
}
