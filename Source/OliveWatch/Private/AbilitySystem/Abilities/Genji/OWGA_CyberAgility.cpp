﻿#include "AbilitySystem/Abilities/Genji/OWGA_CyberAgility.h"
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
	
	// 일단 벽이 있는지 확인
	if (IsNextToWall(Character))
	{
		// 벽타기 시작
		StartWallClimb(Character);
		//EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	// 공중에 있는지 확인 (벽 없음)
	else if (Character->GetCharacterMovement()->IsFalling())
	{
		// 더블점프 
		if (!bDoubleJumpUsed)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("CyberAgility: activate double jump!"));

			Character->LaunchCharacter(FVector(0.f, 0.f, DoubleJumpStrength), false, true);
			bDoubleJumpUsed = true;
			//bCanWallClimb = false;
			Character->LandedDelegate.AddDynamic(this, &UOWGA_CyberAgility::OnLanded);
		}
	}

	else Character->Jump();

	// 점프 전 혹은 점프 못하는 상황
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
	// 벽에 얼마나 가까이 가야하는가?
	FVector End = Start + Forward * 300.f;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Character);

	bool bHitWall = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

	// 디버그용 라인
	//DrawDebugLine(GetWorld(), Start, End, bHitWall ? FColor::Green : FColor::Red, false, 1.0f, 0, 2.0f);

	return bHitWall;
}

void UOWGA_CyberAgility::StartWallClimb(ACharacter* Character)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("~~~~~~~~~~~~~~~~~~~~~~~START WALL CLIMB~~~~~~~~~~~~~~~~~~~~~~~~~~~~"));

	bWallClimbActive = true;
	WallClimbTimeElapsed = 0.f;

	Character->GetCharacterMovement()->GravityScale = 0.0f;
	Character->GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, WallClimbSpeed); 
	Character->GetCharacterMovement()->SetMovementMode(MOVE_Flying);


	FTimerDelegate TimerDel;
	TimerDel.BindUObject(this, &UOWGA_CyberAgility::StopWallClimb);

	Character->GetWorldTimerManager().SetTimer(
		WallClimbTimerHandle,
		TimerDel,
		MaxWallClimbDuration,
		false
	);
}

void UOWGA_CyberAgility::StopWallClimb()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("~~~~~~~~~~~~~~~~~~~~~~~STOP WALL CLIMB~~~~~~~~~~~~~~~~~~~~~~~~~~~~"));

	bWallClimbActive = false;
	bDoubleJumpUsed = false;

	ACharacter* Character = Cast<ACharacter>(CurrentActorInfo->AvatarActor.Get());

	Character->GetCharacterMovement()->GravityScale = 1.0f;
	Character->GetCharacterMovement()->Velocity = FVector::ZeroVector;
	Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);


	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);

}
