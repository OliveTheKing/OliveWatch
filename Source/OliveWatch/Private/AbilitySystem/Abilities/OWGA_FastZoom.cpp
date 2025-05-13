#include "AbilitySystem/Abilities/OWGA_FastZoom.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "GameplayAbilitySpec.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"

void UOWGA_FastZoom::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    if (AActor* Avatar = this->GetAvatarActorFromActorInfo())
    {
        if (UCameraComponent* Camera = Avatar->FindComponentByClass<UCameraComponent>())
        {
            OriginalFOV = Camera->FieldOfView;
            Camera->SetFieldOfView(ZoomFOV);

            UE_LOG(LogTemp, Warning, TEXT(">> FastZoom Activated: Set Camera FOV to %.1f"), ZoomFOV);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT(">> FastZoom Failed: CameraComponent not found"));
        }
    }

    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("Ana's Fast Zoom Activated"));

}

void UOWGA_FastZoom::EndAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    bool bReplicateEndAbility, bool bWasCancelled)
{
    if (AActor* Avatar = this->GetAvatarActorFromActorInfo())
    {
        if (UCameraComponent* Camera = Avatar->FindComponentByClass<UCameraComponent>())
        {
            Camera->SetFieldOfView(OriginalFOV);
            UE_LOG(LogTemp, Warning, TEXT(">> FastZoom Ended: Restored FOV to %.1f"), OriginalFOV);
        }
    }

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
