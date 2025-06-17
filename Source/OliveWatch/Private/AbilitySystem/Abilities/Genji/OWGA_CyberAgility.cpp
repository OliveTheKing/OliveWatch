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

	// 떨어지는 경우
	if (!Character->GetCharacterMovement()->IsFalling())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	// 
	if (!bWallClimbActive && IsNextToWall(Character))
	{
		StartWallClimb(Character);
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
	//bCanWallClimb = false;
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
		bWallClimbActive = false;
		WallClimbTimeElapsed = 0.f;

		GetWorld()->GetTimerManager().ClearTimer(WallClimbTimerHandle);
		Character->LandedDelegate.RemoveDynamic(this, &UOWGA_CyberAgility::OnLanded);
	}
}

bool UOWGA_CyberAgility::IsNextToWall(ACharacter* Character)
{
	FVector Start = Character->GetActorLocation();
	FVector Forward = Character->GetActorForwardVector();
	FVector End = Start + Forward * 50.f;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Character);

	return GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);
}

void UOWGA_CyberAgility::StartWallClimb(ACharacter* Character)
{
	bWallClimbActive = true;
	WallClimbTimeElapsed = 0.f;

	GetWorld()->GetTimerManager().SetTimer(WallClimbTimerHandle, this, &UOWGA_CyberAgility::WallClimbTickWrapper, 0.01f, true);
	Character->LandedDelegate.AddDynamic(this, &UOWGA_CyberAgility::OnLanded);
}

void UOWGA_CyberAgility::WallClimbTickWrapper()
{
	WallClimbTick(0.01f); // deltaTime 고정값
}

void UOWGA_CyberAgility::WallClimbTick(float DeltaTime)
{
	ACharacter* Character = Cast<ACharacter>(CurrentActorInfo->AvatarActor.Get());
	if (!Character) return;

	WallClimbTimeElapsed += DeltaTime;
	if (WallClimbTimeElapsed >= MaxWallClimbDuration)
	{
		bWallClimbActive = false;
		GetWorld()->GetTimerManager().ClearTimer(WallClimbTimerHandle);
		return;
	}

	FVector ClimbVelocity = FVector(0.0f, 0.0f, WallClimbSpeed * DeltaTime);
	Character->AddActorWorldOffset(ClimbVelocity, true);
}