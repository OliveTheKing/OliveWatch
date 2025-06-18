#include "Weapon/OWWeaponComponent.h"
#include "Weapon/OWFireDataAsset.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UOWWeaponComponent::UOWWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    BurstShotsRemaining = 0;
}

void UOWWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
    CachedOwningCharacter = Cast<ACharacter>(GetOwner());

    UOWFireDataAsset* CurrentFireData = GetFireData();
    if (CurrentFireData)
    {
        BurstShotsRemaining = CurrentFireData->FirePattern.FullBullet;
    }
    else
    {
        BurstShotsRemaining = 10;
        UE_LOG(LogTemp, Warning, TEXT("Using default BurstShotsRemaining value"));
    }
}

UOWFireDataAsset* UOWWeaponComponent::GetFireData()
{
    if (!FireData)
    {
        FString DefaultFireDataPath = TEXT("/Game/OliveWatch/Weapons/FireData.FireData");
        UE_LOG(LogTemp, Warning, TEXT("Attempting to load FireData from: %s"), *DefaultFireDataPath);

        FireData = Cast<UOWFireDataAsset>(StaticLoadObject(UOWFireDataAsset::StaticClass(), nullptr, *DefaultFireDataPath));
    }
    return FireData;
}

void UOWWeaponComponent::StartFire(const FVector Dir, const FGameplayEffectSpecHandle& InSpec)
{
    CurrentDamageSpec = InSpec;
    Direction = Dir;
    HandleFireTick();
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

void UOWWeaponComponent::SpawnProjectile()
{
    FVector MuzzleLocation;
    FRotator MuzzleRotation;
    CachedOwningCharacter->GetActorEyesViewPoint(MuzzleLocation, MuzzleRotation);

    FVector AdjustRotation =
        (MuzzleRotation.Vector() * Direction.X) +  // 전방
        (FRotationMatrix(MuzzleRotation).GetUnitAxis(EAxis::Y) * Direction.Y) +  // 오른쪽
        (FRotationMatrix(MuzzleRotation).GetUnitAxis(EAxis::Z) * Direction.Z);
    MuzzleRotation = AdjustRotation.Rotation();

    AOWProjectile* Projectile = GetWorld()->SpawnActorDeferred<AOWProjectile>(
        FireData->FirePattern.ProjectileClass,
        FTransform(MuzzleRotation, MuzzleLocation),
        CachedOwningCharacter,
        CachedOwningCharacter,
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn
    );

    if (Projectile)
    {
        //Projectile->DamageSpecHandle = CurrentDamageSpec;
        Projectile->OverlapEffectSpec.Add(CurrentDamageSpec);

        Projectile->FinishSpawning(FTransform::Identity);  // 임시 트랜스폼으로 완료

        Projectile->SetActorLocation(MuzzleLocation);
        Projectile->SetActorRotation(MuzzleRotation);

        FVector ProjectileDirection = MuzzleRotation.Vector();
        Projectile->SetProjectileVelocity(ProjectileDirection);
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


