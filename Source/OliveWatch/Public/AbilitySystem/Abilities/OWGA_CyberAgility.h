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

	/** �� Ÿ�� ���¸� ���� Ÿ�̸� �ڵ� */
	FTimerHandle WallClimbTimerHandle;

	/** Ability ���� ���� ������ */
	bool bWallClimbUsed;
	bool bDoubleJumpUsed;

	/** ���� ������ �Ķ���� */
	UPROPERTY(EditDefaultsOnly, Category = "CyberAgility")
	float WallClimbDuration;

	UPROPERTY(EditDefaultsOnly, Category = "CyberAgility")
	float WallClimbSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "CyberAgility")
	float MaxClimbHeight;

	/** �÷��̾ ���� ���� �ִ��� Ȯ���ϴ� ���� �Լ� */
	bool IsFacingClimbableWall(const ACharacter* Character, FVector& OutWallNormal) const;
};
