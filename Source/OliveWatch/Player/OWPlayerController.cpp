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
			auto Action1 = InputData->FindInputActionByTag(OWGameplayTags::Input_Action_Move);

			EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
			EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Started, this, &ThisClass::Input_Jump);
			EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Completed, this, &ThisClass::Input_Jump);
		}
	}
}

void AOWPlayerController::Input_Move(const FInputActionValue& InputValue)
{
	FVector2D Direction = InputValue.Get<FVector2D>();

	OWPlayer->Move(Direction);
}

void AOWPlayerController::Input_Jump(const FInputActionValue& InputValue)
{
	GEngine->AddOnScreenDebugMessage(
		-1,                   // Key (-1이면 새 메시지)
		5.0f,                 // 지속 시간 (초)
		FColor::Green,        // 색상
		TEXT("Hello, World!") // 출력 문자열
	);
}

