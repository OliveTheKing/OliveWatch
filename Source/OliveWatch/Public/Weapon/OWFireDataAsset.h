// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "OWProjectile.h"
#include "GameplayEffect.h"
#include "OWFireDataAsset.generated.h"

/**
 * 
 */
USTRUCT()
struct FOWFirePattern
{
    GENERATED_BODY()

public: 

    UPROPERTY(EditDefaultsOnly) int32 BurstCount = 1;   // 1 = 단발, 3 = 표창 3연사
    UPROPERTY(EditDefaultsOnly) float Interval = 0.12f; // 발사 간격
    UPROPERTY(EditDefaultsOnly) uint8 bFixed : 1; // 일정한 간격 ~ 산탄
    UPROPERTY(EditDefaultsOnly) float Spread = 0.f;     // 도트 총이면 0, 산탄 정도
    UPROPERTY(EditDefaultsOnly) float MuzzleDelay = 0.03f; // 애니 지연 보정
    UPROPERTY(EditDefaultsOnly) TSubclassOf<AOWProjectile> ProjectileClass;
    UPROPERTY(EditDefaultsOnly) TSubclassOf<UGameplayEffect> DamageGameplayEffect;
    UPROPERTY(EditDefaultsOnly) float Damage = 12.0f; // 임시 데미지.ge에 들어가야함.
};

USTRUCT()
struct FOWFireMontage
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly) UAnimMontage* ShooteMontage;
    UPROPERTY(EditDefaultsOnly) UAnimMontage* ReloadMontage;
};

UCLASS(BlueprintType)
class OLIVEWATCH_API UOWFireDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()
	
public:
    UOWFireDataAsset(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    UPROPERTY(EditDefaultsOnly) FOWFirePattern FirePattern;
    UPROPERTY(EditDefaultsOnly) FOWFireMontage FireMontage;  
};
