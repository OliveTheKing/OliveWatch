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
	// Actor에 붙어 있는 Factory 컴포넌트 참조
	/*ProjectileFactory = GetOwner()->FindComponentByClass<UOWProjectileFactory>();*/
}

void UOWWeaponComponent::SetFireData(UOWFireDataAsset* NewData)
{
	FireData = NewData;
}

void UOWWeaponComponent::StartFire()
{
    /*if (!FireData || !ProjectileFactory)
        return;*/

    // BurstCount만큼 발사 준비
    BurstShotsRemaining = FireData->FirePattern.BurstCount;
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
    if (BurstShotsRemaining <= 0)
    {
        StopFire();
        return;
    }
    --BurstShotsRemaining;
    
    /* ? 프로젝트일 / 레이캐스트 스폰 ? */
    // 예: SpawnProjectile(FireData->FirePattern, …);
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
}