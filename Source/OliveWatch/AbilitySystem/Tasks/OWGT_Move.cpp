// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Tasks/OWGT_Move.h"
#include "Character/OWCharacter.h"
#include "Abilities/Tasks/AbilityTask.h"

UOWGT_Move* UOWGT_Move::MoveForward(UGameplayAbility* OwningAbility, FName TaskInstanceName, float Speed, float TargetDistance)
{
	UOWGT_Move* Task = NewAbilityTask<UOWGT_Move>(OwningAbility, TaskInstanceName);
	Task->Speed = Speed;
	Task->TargetDistance = TargetDistance;
	Task->ReadyForActivation();

	return Task;
}

UOWGT_Move::UOWGT_Move()
	: TargetDistance(0.f)
	, Speed(0.f)
	, CurrentDistance(0.f)
{
	bTickingTask = true;
}

void UOWGT_Move::Activate()
{
	Super::Activate();
	if (AOWCharacter* OwningCharacter = Cast<AOWCharacter>(GetAvatarActor()))
	{
		Character = OwningCharacter;
	}
	else
	{
		EndTask();
		return;
	}
}

void UOWGT_Move::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (Character)
	{
		CurrentDistance += Speed * DeltaTime;
		if (CurrentDistance >= TargetDistance)
		{
			EndTask();
		}
		else
		{
			FVector Direction = Character->GetActorForwardVector();
			Character->Move(Direction, Speed * DeltaTime);
		}
	}
	else
	{
		EndTask();
	}
}

void UOWGT_Move::OnDestroy(bool bInOwnerFinished)
{
	OnCompleted.Broadcast();
}
