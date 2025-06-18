#include "Weapon/OWWeaponComponent.h"
#include "Weapon/OWFireDataAsset.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "Player/OWPlayerState.h"
#include "OWGameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"
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
    CachedOwningASC = GetOwnerASC();
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

// WeaponComponent 같은 캐릭터 종속 클래스 안에서
UAbilitySystemComponent* UOWWeaponComponent::GetOwnerASC() const
{
    if (const ACharacter* Char = Cast<ACharacter>(GetOwner()))
    {
        if (AOWPlayerState* PS = Char->GetPlayerState<AOWPlayerState>())
        {
            return PS->GetAbilitySystemComponent();
        }
    }
    return nullptr;
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

    if (FireData->FirePattern.IsRayCast) {
        ShootRay();
    }
    else {
        SpawnProjectile();
    }
}

void UOWWeaponComponent::ShootRay()
{
    if (!CachedOwningCharacter || !FireData) { return; }

    FVector Start;
    FRotator ViewRot;
    CachedOwningCharacter->GetActorEyesViewPoint(Start, ViewRot);

    FVector AdjustRotation =
        (ViewRot.Vector() * Direction.X) +  // 전방
        (FRotationMatrix(ViewRot).GetUnitAxis(EAxis::Y) * Direction.Y) +  // 오른쪽
        (FRotationMatrix(ViewRot).GetUnitAxis(EAxis::Z) * Direction.Z);
    AdjustRotation = AdjustRotation.GetSafeNormal();

    const float RayLen = FireData->FirePattern.RayLength;
    const FVector End = Start + AdjustRotation * RayLen;

    FHitResult Hit;
    FCollisionQueryParams Params(SCENE_QUERY_STAT(ShootRay), /*bTraceComplex*/false, CachedOwningCharacter);
    Params.bReturnPhysicalMaterial = false;

    const bool bHit = GetWorld()->LineTraceSingleByChannel(
        Hit, Start, End, ECC_Visibility, Params);


#if WITH_EDITOR
    DrawDebugLine(GetWorld(), Start, End, bHit ? FColor::Red : FColor::Green, false, 2.f, 0, 1.f);
#endif

    AActor* Victim = Hit.GetActor();
    if (!Victim) { return; }

    if (UAbilitySystemComponent* VictimASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Victim))
    {
        if (FireData->FirePattern.DamageGameplayEffect)
        {
            FGameplayEffectContextHandle Ctx = VictimASC->MakeEffectContext();
            Ctx.AddSourceObject(this);

            FGameplayEffectSpecHandle Spec =
                VictimASC->MakeOutgoingSpec(FireData->FirePattern.DamageGameplayEffect,
                    /*Level*/1.f, Ctx);

            if (Spec.IsValid())
            {
                const float Damage = FireData->FirePattern.Damage;
                Spec.Data->SetSetByCallerMagnitude(
                    OWGameplayTags::Data_Damage, Damage);

                VictimASC->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
            }
        }
    }
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


