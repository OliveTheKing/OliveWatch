// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "OWGT_Move.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoveDelegate);

/**
 * 속도, 거리가 주어졌을 때 캐릭터가 바라보고 있는 방향으로 이동
 * @todo 이동 방향을 Default 캐릭터 Forward Vector, 이외 매개변수로 전달받을 수 있도록...
 */
UCLASS()
class OLIVEWATCH_API UOWGT_Move : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility"))
	static UOWGT_Move* MoveForward(UGameplayAbility* OwningAbility, FName TaskInstanceName, float Speed, float TargetDistance);

	UPROPERTY(BlueprintAssignable)
	FMoveDelegate OnCompleted;

protected:

	float Speed;
	float TargetDistance;
	float CurrentDistance;
	TObjectPtr<class AOWCharacter> Character;

	UOWGT_Move();

	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
};
