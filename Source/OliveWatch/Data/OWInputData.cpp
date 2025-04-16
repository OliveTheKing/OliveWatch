// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/OWInputData.h"
#include "InputAction.h"

const UInputAction* UOWInputData::FindInputActionByTag(const FGameplayTag& InputTag) const
{
	for (const FOWInputAction& Action : InputActions) {
		if (Action.InputAction && Action.InputTag == InputTag) {
			return Action.InputAction;
		}
	}
	return nullptr;
}
