// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilitySystemComponent.h"
#include "OWWeaponComponent.generated.h"


class UOWFireDataAsset;
class UOWProjectileFactory;

UCLASS(ClassGroup = (Custom), BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class OLIVEWATCH_API UOWWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UOWWeaponComponent();

    /** 시작: BurstCount만큼 Timer로 자동 발사 */
    UFUNCTION(BlueprintCallable, Category = "Weapon") void StartFire(const FGameplayEffectSpecHandle& InSpec);
    /** 중단: 자동 사격 타이머 클리어 */
    UFUNCTION(BlueprintCallable, Category = "Weapon") void StopFire();

    /** 탄창 재장전*/
    void StartReload();      // GA_Reload가 호출
    void FinishReload();     // Timer 콜백

    UOWFireDataAsset* GetFireData();

protected:
    virtual void BeginPlay() override;

private:	
    /** 발사 설정 데이터 */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    UOWFireDataAsset* FireData;

    /** TimerHandle for auto‐fire */
    FTimerHandle TimerHandle_Fire;
    FGameplayEffectSpecHandle CurrentDamageSpec;

    /** 남은 발사 횟수 */
    int32 BurstShotsRemaining;
    FVector MuzzleLocation;
    FRotator MuzzleRotation;

    /** Timer 콜백: 한 발씩 발사 */
    void HandleFireTick();	
    void SpawnProjectile();
};
