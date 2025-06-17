#include "AbilitySystem/Abilities/Genji/OWGA_CyberAgility.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UOWGA_CyberAgility::UOWGA_CyberAgility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UOWGA_CyberAgility::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());

	if (!Character->GetCharacterMovement()->IsFalling())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	if (bDoubleJumpUsed)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("CyberAgility: activate double jump!"));

	Character->LaunchCharacter(FVector(0.f, 0.f, DoubleJumpStrength), false, true);
	bDoubleJumpUsed = true;
	Character->LandedDelegate.AddDynamic(this, &UOWGA_CyberAgility::OnLanded);

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}


void UOWGA_CyberAgility::OnLanded(const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("Landed!!!!!!!!"));

	ACharacter* Character = Cast<ACharacter>(CurrentActorInfo->AvatarActor.Get());
	if (Character)
	{
		bDoubleJumpUsed = false;
		Character->LandedDelegate.RemoveDynamic(this, &UOWGA_CyberAgility::OnLanded);
	}
}
