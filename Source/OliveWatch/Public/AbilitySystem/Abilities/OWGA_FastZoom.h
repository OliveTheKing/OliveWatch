#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Base/OWGA_Active.h"
#include "GameplayAbilitySpec.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "OWGA_FastZoom.generated.h"

UCLASS()
class OLIVEWATCH_API UOWGA_FastZoom : public UOWGA_Active
{
    GENERATED_BODY()

public:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData) override;

    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
    // 줌 시 사용할 FOV 값
    UPROPERTY(EditDefaultsOnly, Category = "FastZoom")
    float ZoomFOV = 40.f;

private:
    float OriginalFOV = 90.f;
};
