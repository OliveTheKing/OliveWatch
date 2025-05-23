// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "OWProjectile.h"
#include "OWFireDataAsset.generated.h"

/**
 * 
 */
USTRUCT()
struct FOWFirePattern
{
    GENERATED_BODY()

public: 

    UPROPERTY(EditDefaultsOnly) int32 BurstCount = 1;   // 1 = �ܹ�, 3 = ǥâ 3����
    UPROPERTY(EditDefaultsOnly) float Interval = 0.12f; // �߻� ����
    UPROPERTY(EditDefaultsOnly) uint8 bFixed : 1; // ������ ���� ~ ��ź
    UPROPERTY(EditDefaultsOnly) float Spread = 0.f;     // ��Ʈ ���̸� 0, ��ź ����
    UPROPERTY(EditDefaultsOnly) TSubclassOf<AOWProjectile> ProjectileClass;
    UPROPERTY(EditDefaultsOnly) float MuzzleDelay = 0.03f; // �ִ� ���� ����
    UPROPERTY(EditDefaultsOnly) float Damage = 12.f;
};

USTRUCT()
struct FOWFireMontage
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly) UAnimMontage* ShooteMontage;
    UPROPERTY(EditDefaultsOnly) UAnimMontage* ReloadMontage;
};

UCLASS()
class OLIVEWATCH_API UOWFireDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()
	
public:
    UOWFireDataAsset(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    UPROPERTY(EditDefaultsOnly) FOWFirePattern FirePattern;
    UPROPERTY(EditDefaultsOnly) FOWFireMontage FireMontage;  
};
