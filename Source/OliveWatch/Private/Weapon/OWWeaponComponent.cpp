// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/OWWeaponComponent.h"
#include "Weapon/OWFireDataAsset.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UOWWeaponComponent::UOWWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	/*ProjectileFactory = nullptr;*/
	BurstShotsRemaining = 0;
}

void UOWWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
    BurstShotsRemaining = FireData->FirePattern.FullBullet;
}

UOWFireDataAsset* UOWWeaponComponent::GetFireData()
{
    if(!FireData)    
    {
        FString DefaultFireDataPath = TEXT("/Game/OliveWatch/Weapons/FireData.FireData");
        FireData = Cast<UOWFireDataAsset>(StaticLoadObject(UOWFireDataAsset::StaticClass(), nullptr, *DefaultFireDataPath));
    }
    return FireData;
}

void UOWWeaponComponent::StartFire(const FVector Dir, const FGameplayEffectSpecHandle& InSpec)
{
    CurrentDamageSpec = InSpec;
    Direction = Dir;
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
    if (BurstShotsRemaining-- < FireData->FirePattern.BurstCount)
    {
        StartReload();
        return;
    }

    SpawnProjectile();
}

void UOWWeaponComponent::ShootRoutine()
{
}

void UOWWeaponComponent::SpawnProjectile()
{
    FTransform MuzzleWorldTransform = GetComponentTransform();
    MuzzleLocation = MuzzleWorldTransform.GetLocation();
    ACharacter* OwningCharacter = Cast<ACharacter>(GetOwner());
    MuzzleRotation = OwningCharacter ? OwningCharacter->GetControlRotation() : GetComponentRotation();

    AOWProjectile* Projectile = GetWorld()->SpawnActorDeferred<AOWProjectile>(
        FireData->FirePattern.ProjectileClass,
        FTransform(MuzzleRotation, MuzzleLocation),
        Cast<ACharacter>(GetOwner()),
        nullptr,
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn
    );
    if (Projectile) {
        Projectile->SetProjectileVelocity(Direction);
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