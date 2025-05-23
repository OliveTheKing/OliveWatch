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
	// Actor�� �پ� �ִ� Factory ������Ʈ ����
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

    // BurstCount��ŭ �߻� �غ�
    BurstShotsRemaining = FireData->FirePattern.BurstCount;
    // ��� 1��
    HandleFireTick();
    // ���� Interval���� �߻�
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
    
    /* ? ������Ʈ�� / ����ĳ��Ʈ ���� ? */
    // ��: SpawnProjectile(FireData->FirePattern, ��);
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