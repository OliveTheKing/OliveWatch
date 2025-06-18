// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"         
#include "AbilitySystem/OWAbilitySet.h"   
#include "Data/OWInputData.h"             
#include "EnhancedInputComponent.h"       
#include "AbilitySystem/Abilities/Base/OWGameplayAbility.h"
#include "OWPlayerController.generated.h"

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

    template<class UserClass, typename FuncType>
    void BindNativeAction(const FGameplayTag& InputTag, UserClass* Object, FuncType Func);

    template<class UserClass, typename FuncType>
    void BindSkillAction(UOWAbilitySet* OWAS, const FGameplayTag& InputTag, UserClass* Object, FuncType Func);
    void UnbindPreviousInputs();

protected:
	virtual void SetupInputComponent() override;

private:
    void Input_Move(const FInputActionValue& InputValue);
    void Input_Jump(const FInputActionValue& InputValue);
    void Input_Curl(const FInputActionValue& InputValue);
    void Input_MeleeAttack(const FInputActionValue& InputValue);
    void Input_MainFire(const FInputActionValue& InputValue);
    void Input_MainFireMainTain(const FInputActionValue& InputValue);
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

    UPROPERTY()
    UEnhancedInputComponent* EnhancedInputComponent;

private:
    void BindAbilitiesFromPawn(APawn* InPawn);
    void OnPossess(APawn* InPawn);
    void OnRep_Pawn();
};

template<class UserClass, typename FuncType>
inline void AOWPlayerController::BindNativeAction(const FGameplayTag& InputTag, UserClass* Object, FuncType Func)
{
    if (const UInputAction* IA = InputData->FindInputActionByTag(InputTag))
    {
        EnhancedInputComponent->BindAction(IA, ETriggerEvent::Triggered, Object, Func);
    }
}

template<class UserClass, typename FuncType>
inline void AOWPlayerController::BindSkillAction(UOWAbilitySet* OWAS, const FGameplayTag& InputTag, UserClass* Object, FuncType Func)
{
    if (const UInputAction* IA = InputData->FindInputActionByTag(InputTag))
    {
        auto GA = OWAS->FindAbilityByTag(InputTag);

        if (GA.Ability) {
            EnhancedInputComponent->BindAction(IA, GA.TriggerType, Object, Func);
        }
        else {
            EnhancedInputComponent->BindAction(IA, ETriggerEvent::Triggered, Object, Func);
        }
    }
}
