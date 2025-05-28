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

	/** Ability Activate Entry Point */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	/** Ability Logic **/
	void StartWallClimb();
	void EndWallClimb();
	void ResetJumpState();

	/** 벽 타기 상태를 위한 타이머 핸들 */
	FTimerHandle WallClimbTimerHandle;

	/** Ability 내부 상태 변수들 */
	bool bWallClimbUsed;
	bool bDoubleJumpUsed;

	/** 설정 가능한 파라미터 */
	UPROPERTY(EditDefaultsOnly, Category = "CyberAgility")
	float WallClimbDuration;

	UPROPERTY(EditDefaultsOnly, Category = "CyberAgility")
	float WallClimbSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "CyberAgility")
	float MaxClimbHeight;

	/** 플레이어가 벽을 향해 있는지 확인하는 헬퍼 함수 */
	bool IsFacingClimbableWall(const ACharacter* Character, FVector& OutWallNormal) const;
};
