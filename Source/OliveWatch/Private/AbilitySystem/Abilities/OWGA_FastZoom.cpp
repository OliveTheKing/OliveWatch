#include "AbilitySystem/Abilities/OWGA_FastZoom.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/PlayerController.h"

void UOWGA_FastZoom::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    APlayerController* PC = Cast<APlayerController>(ActorInfo->PlayerController);
    if (PC && PC->PlayerCameraManager)
    {
        OriginalFOV = PC->PlayerCameraManager->GetFOVAngle();
        PC->PlayerCameraManager->SetFOV(ZoomFOV);
    }
}

void UOWGA_FastZoom::EndAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    bool bReplicateEndAbility, bool bWasCancelled)
{
    APlayerController* PC = Cast<APlayerController>(ActorInfo->PlayerController);
    if (PC && PC->PlayerCameraManager)
    {
        PC->PlayerCameraManager->SetFOV(OriginalFOV);
    }

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
