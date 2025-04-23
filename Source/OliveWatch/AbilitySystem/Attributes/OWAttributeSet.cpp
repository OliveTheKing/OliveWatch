// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/OWAttributeSet.h"

#include "Net/UnrealNetwork.h"


void UOWAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	FString Msg = FString::Printf(TEXT("%f %f"), OldValue, NewValue);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, Msg);
}

void UOWAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UOWAttributeSet, HP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOWAttributeSet, Bullets, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOWAttributeSet, Speed, COND_None, REPNOTIFY_Always);

}

void UOWAttributeSet::OnRep_HP(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOWAttributeSet, HP, OldValue);
}

void UOWAttributeSet::OnRep_Bullets(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOWAttributeSet, Bullets, OldValue);
}


