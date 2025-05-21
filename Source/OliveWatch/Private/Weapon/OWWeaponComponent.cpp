// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/OWWeaponComponent.h"
#include "Weapon/OWFireDataAsset.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UOWWeaponComponent::UOWWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	FireData = nullptr;
	/*ProjectileFactory = nullptr;*/
	BurstShotsRemaining = 0;
}

void UOWWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
    BurstShotsRemaining = FireData->FirePattern.FullBullet;
    if (ACharacter* Ch = Cast<ACharacter>(GetOwner()))
    {
        Ch->GetActorEyesViewPoint(MuzzleLocation, MuzzleRotation);
    }
}

UOWFireDataAsset* UOWWeaponComponent::GetFireData()
{
    return FireData;
}

void UOWWeaponComponent::StartFire(const FGameplayEffectSpecHandle& InSpec)
{
    CurrentDamageSpec = InSpec;
    // 즉시 1발
    HandleFireTick();
    // 이후 Interval마다 발사
    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle_Fire,
        this, &UOWWeaponComponent::HandleFireTick,
        FireData->FirePattern.Interval,
        true);
}

void UOWWeaponComponent::StopFire()
{
    GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Fire);
}

void UOWWeaponComponent::HandleFireTick()
{
    if (BurstShotsRemaining-- <= 0)
    {
        StartReload();
        return;
    }

    SpawnProjectile();
}

void UOWWeaponComponent::SpawnProjectile()
{
    AOWProjectile* Projectile = GetWorld()->SpawnActorDeferred<AOWProjectile>(
        FireData->FirePattern.ProjectileClass,
        FTransform(MuzzleRotation, MuzzleLocation),
        Cast<ACharacter>(GetOwner()),
        nullptr,
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn
    );
    if (Projectile) {
        Projectile->DamageSpecHandle = CurrentDamageSpec;
        Projectile->FinishSpawning(FTransform(MuzzleRotation, MuzzleLocation));
    }
}

void UOWWeaponComponent::StartReload()
{
    StopFire();

    const float ReloadTime = FireData ? FireData->FirePattern.Interval : 1.5f;
    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle_Fire,
        this, &UOWWeaponComponent::FinishReload,
        ReloadTime,
        false);
}

void UOWWeaponComponent::FinishReload()
{
    BurstShotsRemaining = FireData->FirePattern.FullBullet;
}