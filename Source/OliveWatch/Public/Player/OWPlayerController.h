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

private:
    void Input_Move(const FInputActionValue& InputValue);
    void Input_Jump(const FInputActionValue& InputValue);
    void Input_Curl(const FInputActionValue& InputValue);
    void Input_MeleeAttack(const FInputActionValue& InputValue);
    void Input_MainFire(const FInputActionValue& InputValue);
    void Input_SubFire(const FInputActionValue& InputValue);
    void Input_Skill1(const FInputActionValue& InputValue);
    void Input_Skill2(const FInputActionValue& InputValue);
    void Input_Skill3(const FInputActionValue& InputValue);
    void Input_Reload(const FInputActionValue& InputValue);
    void Input_Look(const FInputActionValue& InputValue);

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UOWInputData> InputData;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AOWCharacter> OWPlayer;
};
