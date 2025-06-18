#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Base/OWGA_Active.h"
#include "OWGA_CyberAgility.generated.h"

UCLASS()
class OLIVEWATCH_API UOWGA_CyberAgility : public UOWGA_Active
{
	GENERATED_BODY()

public:
	UOWGA_CyberAgility();

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

protected:

	// 이단점프
	UPROPERTY(EditDefaultsOnly, Category = "CyberAgility")
	float DoubleJumpStrength = 600.f;

	UPROPERTY(BlueprintReadOnly)
	bool bDoubleJumpUsed = false;

	UFUNCTION()
	void OnLanded(const FHitResult& Hit);

	// 벽타기
	bool bWallClimbActive = false;
	float WallClimbTimeElapsed = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "CyberAgility")
	float MaxWallClimbDuration = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "CyberAgility")
	float WallClimbSpeed = 780.0f; // 7.8 m/s == 780 cm/s

	FTimerHandle WallClimbTimerHandle;

	UFUNCTION()
	bool IsNextToWall(ACharacter* Character);

	UFUNCTION()
	void StartWallClimb(ACharacter* Character);

	UFUNCTION()
	void StopWallClimb();
};
