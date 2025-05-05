// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "OWAbilitySystemComponent.generated.h"

class UOWAttributeSet;

/**
 * 
 */
UCLASS()
class OLIVEWATCH_API UOWAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UOWAbilitySystemComponent();
	
public:
	UFUNCTION()
	void UpdatePlayerState(FGameplayTag StateTag);

	void ActivateAbility(FGameplayTag AbilityTag);

	
protected:
	UPROPERTY()
	TObjectPtr<const UOWAttributeSet> AttributeSet;

};
