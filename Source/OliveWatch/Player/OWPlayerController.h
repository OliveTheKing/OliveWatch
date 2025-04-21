// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OWPlayerController.generated.h"

class UOWInputData;
class AOWCharacter;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class OLIVEWATCH_API AOWPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	virtual void SetupInputComponent() override;
	virtual void Input_Move(const FInputActionValue& InputValue);
	virtual void Input_Jump(const FInputActionValue& InputValue);

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UOWInputData> InputData;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AOWCharacter> OWPlayer;
};
