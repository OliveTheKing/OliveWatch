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
	UPROPERTY(EditDefaultsOnly, Category = "CyberAgility")
	float DoubleJumpStrength = 600.f;

	UPROPERTY(BlueprintReadOnly)
	bool bDoubleJumpUsed = false;

	UFUNCTION()
	void OnLanded(const FHitResult& Hit);
};
