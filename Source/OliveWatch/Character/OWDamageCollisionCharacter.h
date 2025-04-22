// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OliveWatchCharacter.h"
#include "Interface/OWAnimationAttacksInterface.h"
#include "OWDamageCollisionCharacter.generated.h"

/**
 * 
 */
UCLASS()
class OLIVEWATCH_API AOWDamageCollisionCharacter : public AOliveWatchCharacter, public IOWAnimationAttacksInterface
{
	GENERATED_BODY()

protected:
	virtual void AttackHitCheck() override;
};
