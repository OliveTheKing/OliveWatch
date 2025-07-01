// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/OWCharacter.h"
#include "OWMonster.generated.h"

/**
 * 
 */
UCLASS()
class OLIVEWATCH_API AOWMonster : public AOWCharacter
{
	GENERATED_BODY()

public:
	AOWMonster();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AbilitySet")
	TObjectPtr<class UOWAbilitySet> AbilitySet;

private:
	float TimeDuration;
	float ElapsedTime;
	bool bMoveRight;
};
