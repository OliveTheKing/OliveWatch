// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/OWCollisionHit.h"
#include "GameplayEffectTypes.h"
#include "OWProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UAbilitySystemComponent;

UCLASS(config = Game)
class OLIVEWATCH_API AOWProjectile : public AOWCollisionHit
{
	GENERATED_BODY()

public:
	AOWProjectile();

	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageSpecHandle;

protected:
	virtual void BeginPlay() override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	/** Sphere collision component */
	//UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	//USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY()
	bool IsDeflected = false;

	/** called when projectile hits something */
	//UFUNCTION()
	//virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

public:

	/** DamageSpec */
	void SetDamageSpecHandle(FGameplayEffectSpecHandle InHandle) { DamageSpecHandle = InHandle; }


	/** Returns CollisionComp subobject **/
	//USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	UFUNCTION()
	void SetProjectileVelocity(FVector Rotation);
};
