// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/OWAttributeSet.h"


void UOWAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	FString Msg = FString::Printf(TEXT("%f %f"), OldValue, NewValue);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, Msg);
}
