#include "AbilitySystem/Abilities/OWGA_CyberAgility.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

UOWGA_CyberAgility::UOWGA_CyberAgility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	WallClimbDuration = 1.2f;
	WallClimbSpeed = 300.0f;
	MaxClimbHeight = 970.0f; // 단위: cm → 9.7m

	bWallClimbUsed = false;
	bDoubleJumpUsed = false;
}

void UOWGA_CyberAgility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	if (!Character || bWallClimbUsed)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	FVector WallNormal;
	if (IsFacingClimbableWall(Character, WallNormal))
	{
		StartWallClimb();
	}
	else
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}
}

void UOWGA_CyberAgility::StartWallClimb()
{
	bWallClimbUsed = true;

	ACharacter* Character = Cast<ACharacter>(CurrentActorInfo->AvatarActor.Get());
	if (!Character) return;

	// 중력 제거 및 수직 이동
	UCharacterMovementComponent* MoveComp = Character->GetCharacterMovement();
	if (MoveComp)
	{
		MoveComp->GravityScale = 0.0f;
		MoveComp->Velocity = FVector(0.0f, 0.0f, WallClimbSpeed);
	}

	// 일정 시간 후 벽타기 종료
	GetWorld()->GetTimerManager().SetTimer(WallClimbTimerHandle, this, &UOWGA_CyberAgility::EndWallClimb, WallClimbDuration, false);
}

void UOWGA_CyberAgility::EndWallClimb()
{
	ACharacter* Character = Cast<ACharacter>(CurrentActorInfo->AvatarActor.Get());
	if (!Character) return;

	UCharacterMovementComponent* MoveComp = Character->GetCharacterMovement();
	if (MoveComp)
	{
		MoveComp->GravityScale = 1.0f;
	}

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UOWGA_CyberAgility::ResetJumpState()
{
	bWallClimbUsed = false;
	bDoubleJumpUsed = false;
}

bool UOWGA_CyberAgility::IsFacingClimbableWall(const ACharacter* Character, FVector& OutWallNormal) const
{
	FVector Start = Character->GetActorLocation();
	FVector Forward = Character->GetActorForwardVector();
	FVector End = Start + Forward * 100.0f;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Character);

	bool bHit = Character->GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);
	if (bHit && Hit.Normal.Z < 0.5f) // 거의 수직면만 벽으로 간주
	{
		OutWallNormal = Hit.Normal;
		return true;
	}

	return false;
}
