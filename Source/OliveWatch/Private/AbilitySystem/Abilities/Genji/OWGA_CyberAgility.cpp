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
	
	// 일단 벽이 있는지 확인
	if (IsNextToWall(Character))
	{
		// 벽타기 시작
		StartWallClimb(Character);
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	// 공중에 있는지 확인 (벽 없음)
	if (!Character->GetCharacterMovement()->IsFalling())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	// 더블점프 
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

	bool bHitWall = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

	// 디버그용 라인
	DrawDebugLine(GetWorld(), Start, End, bHitWall ? FColor::Green : FColor::Red, false, 1.0f, 0, 2.0f);

	return bHitWall;
}

void UOWGA_CyberAgility::StartWallClimb(ACharacter* Character)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("~~~~~~~~~~~~~~~~~~~~~~~START WALL CLIMB~~~~~~~~~~~~~~~~~~~~~~~~~~~~"));

	bWallClimbActive = true;
	WallClimbTimeElapsed = 0.f;

	Character->GetCharacterMovement()->GravityScale = 0.0f;
	Character->GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, WallClimbSpeed); 

	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("StopWallClimb"));

	AActor* OwnerActor = GetAvatarActorFromActorInfo();
	OwnerActor->GetWorldTimerManager().SetTimer(
		WallClimbTimerHandle,
		TimerDel,
		MaxWallClimbDuration,
		false
	);

	if (GetWorld()->GetTimerManager().IsTimerActive(WallClimbTimerHandle))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("WallClimb timer successfully set."));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Timer failed to set!"));
	}

}

void UOWGA_CyberAgility::StopWallClimb()
{
	bWallClimbActive = false;

	ACharacter* Character = Cast<ACharacter>(CurrentActorInfo->AvatarActor.Get());

	Character->GetCharacterMovement()->GravityScale = 1.0f;
	Character->GetCharacterMovement()->Velocity = FVector::ZeroVector;

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT(">>> STOP WALL CLIMB <<<"));
}
