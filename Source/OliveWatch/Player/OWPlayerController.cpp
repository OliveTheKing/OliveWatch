// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/OWPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "OWGameplayTags.h"
#include "Data/OWInputData.h"
#include "Character/OWCharacter.h"
#include "InputActionValue.h"



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

		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {
            auto ActionMove = InputData->FindInputActionByTag(OWGameplayTags::Input_Action_Move);
            auto ActionJump = InputData->FindInputActionByTag(OWGameplayTags::Input_Action_Jump);
            auto ActionCurl = InputData->FindInputActionByTag(OWGameplayTags::Input_Action_Curl);
            auto ActionMeleeAttack = InputData->FindInputActionByTag(OWGameplayTags::Input_Action_MeleeAttack);
            auto ActionMainFire = InputData->FindInputActionByTag(OWGameplayTags::Input_Action_MainFire);
            auto ActionSubFire = InputData->FindInputActionByTag(OWGameplayTags::Input_Action_SubFire);
            auto ActionSkill1 = InputData->FindInputActionByTag(OWGameplayTags::Input_Action_Skill1);
            auto ActionSkill2 = InputData->FindInputActionByTag(OWGameplayTags::Input_Action_Skill2);
            auto ActionSkill3 = InputData->FindInputActionByTag(OWGameplayTags::Input_Action_Skill3);
            auto ActionReload = InputData->FindInputActionByTag(OWGameplayTags::Input_Action_Reload);

            // BindAction 호출
            if (ActionMove)
                EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);

            if (ActionJump)
                EnhancedInputComponent->BindAction(ActionJump, ETriggerEvent::Triggered, this, &ThisClass::Input_Jump);

            if (ActionCurl)
                EnhancedInputComponent->BindAction(ActionCurl, ETriggerEvent::Triggered, this, &ThisClass::Input_Curl);

            if (ActionMeleeAttack)
                EnhancedInputComponent->BindAction(ActionMeleeAttack, ETriggerEvent::Triggered, this, &ThisClass::Input_MeleeAttack);

            if (ActionMainFire)
                EnhancedInputComponent->BindAction(ActionMainFire, ETriggerEvent::Triggered, this, &ThisClass::Input_MainFire);

            if (ActionSubFire)
                EnhancedInputComponent->BindAction(ActionSubFire, ETriggerEvent::Triggered, this, &ThisClass::Input_SubFire);

            if (ActionSkill1)
                EnhancedInputComponent->BindAction(ActionSkill1, ETriggerEvent::Triggered, this, &ThisClass::Input_Skill1);

            if (ActionSkill2)
                EnhancedInputComponent->BindAction(ActionSkill2, ETriggerEvent::Triggered, this, &ThisClass::Input_Skill2);

            if (ActionSkill3)
                EnhancedInputComponent->BindAction(ActionSkill3, ETriggerEvent::Triggered, this, &ThisClass::Input_Skill3);

            if (ActionReload)
                EnhancedInputComponent->BindAction(ActionReload, ETriggerEvent::Triggered, this, &ThisClass::Input_Reload);
        }
	}
}

void AOWPlayerController::Input_Move(const FInputActionValue& InputValue)
{
	FVector2D Direction = InputValue.Get<FVector2D>();

	OWPlayer->Move(Direction);
}

void AOWPlayerController::Input_Jump(const FInputActionValue& Value)
{
	OWPlayer->Jump();
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