// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/OWPlayerController.h"
#include "OWGameplayTags.h"
#include "Data/OWInputData.h"
#include "Character/OWCharacter.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/OWPlayerState.h"


void AOWPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (InputData)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputData->InputMappingContext, 0);
		}

	}

	OWPlayer = Cast<AOWCharacter>(GetCharacter());
}

void AOWPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputData) {

        EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

		if (EnhancedInputComponent) {

            // BindAction 호출
            // 모든 영웅 동일 기본 Action
            BindNativeAction(OWGameplayTags::Input_Action_Move, this, &ThisClass::Input_Move);
            BindNativeAction(OWGameplayTags::Input_Action_Curl, this, &ThisClass::Input_Curl);
            BindNativeAction(OWGameplayTags::Input_Action_MeleeAttack, this, &ThisClass::Input_MeleeAttack);
            BindNativeAction(OWGameplayTags::Input_Action_Look, this, &ThisClass::Input_Look);
        }
	}
}

void AOWPlayerController::BindAbilitiesFromPawn(APawn* InPawn)
{
	UnbindPreviousInputs();            // (옵션) 옛 Pawn 바인딩 해제

	if (AOWCharacter* Ch = Cast<AOWCharacter>(InPawn))
	{
		if (UOWAbilitySet* OWAS = Ch->GetOWAbilitySet())
		{
			BindSkillAction(OWAS, OWGameplayTags::Input_Action_Jump, this, &ThisClass::Input_Jump);
			BindSkillAction(OWAS, OWGameplayTags::Input_Action_MainFire, this, &ThisClass::Input_MainFire);
			BindSkillAction(OWAS, OWGameplayTags::Input_Action_MainFireMainTain, this, &ThisClass::Input_MainFireMainTain);
			BindSkillAction(OWAS, OWGameplayTags::Input_Action_SubFire, this, &ThisClass::Input_SubFire);
			BindSkillAction(OWAS, OWGameplayTags::Input_Action_Skill1, this, &ThisClass::Input_Skill1);
			BindSkillAction(OWAS, OWGameplayTags::Input_Action_Skill2, this, &ThisClass::Input_Skill2);
			BindSkillAction(OWAS, OWGameplayTags::Input_Action_Skill3, this, &ThisClass::Input_Skill3);
			BindSkillAction(OWAS, OWGameplayTags::Input_Action_Reload, this, &ThisClass::Input_Reload);
		}
	}
}

void AOWPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	BindAbilitiesFromPawn(InPawn);                 // 서버
}

void AOWPlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();
	BindAbilitiesFromPawn(GetPawn());              // 클라이언트
}

void AOWPlayerController::UnbindPreviousInputs()
{

}



void AOWPlayerController::Input_Move(const FInputActionValue& InputValue)
{
	FVector2D Direction = InputValue.Get<FVector2D>();

	OWPlayer->Move(FVector(Direction.X, Direction.Y, 0.f));
}

void AOWPlayerController::Input_Jump(const FInputActionValue& Value)
{
	OWPlayer->ActivateAbility(OWGameplayTags::Input_Action_Jump);
}

void AOWPlayerController::Input_Curl(const FInputActionValue& Value)
{
	OWPlayer->ActivateAbility(OWGameplayTags::Input_Action_Curl);
}

void AOWPlayerController::Input_MeleeAttack(const FInputActionValue& Value)
{
	OWPlayer->ActivateAbility(OWGameplayTags::Input_Action_MeleeAttack);
}

void AOWPlayerController::Input_MainFire(const FInputActionValue& Value)
{
	OWPlayer->ActivateAbility(OWGameplayTags::Input_Action_MainFire);
}

void AOWPlayerController::Input_MainFireMainTain(const FInputActionValue& InputValue)
{
	OWPlayer->ActivateAbility(OWGameplayTags::Input_Action_MainFireMainTain);
}

void AOWPlayerController::Input_SubFire(const FInputActionValue& Value)
{
	OWPlayer->ActivateAbility(OWGameplayTags::Input_Action_SubFire);
}

void AOWPlayerController::Input_Skill1(const FInputActionValue& Value)
{
	OWPlayer->ActivateAbility(OWGameplayTags::Input_Action_Skill1);
}

void AOWPlayerController::Input_Skill2(const FInputActionValue& Value)
{
	OWPlayer->ActivateAbility(OWGameplayTags::Input_Action_Skill2);
}

void AOWPlayerController::Input_Skill3(const FInputActionValue& Value)
{
	OWPlayer->ActivateAbility(OWGameplayTags::Input_Action_Skill3);
}

void AOWPlayerController::Input_Reload(const FInputActionValue& Value)
{
	OWPlayer->ActivateAbility(OWGameplayTags::Input_Action_Reload);
}

void AOWPlayerController::Input_Look(const FInputActionValue& InputValue)
{
    FVector2D Direction = InputValue.Get<FVector2D>();

    OWPlayer->Look(FVector(Direction.X, Direction.Y, 0.f));
}
