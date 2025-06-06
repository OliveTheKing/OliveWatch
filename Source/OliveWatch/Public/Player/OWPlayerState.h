// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "OWPlayerState.generated.h"

class UOWAbilitySystemComponent;
class UOWAbilitySet;

/**
 * 
 */
UCLASS()
class OLIVEWATCH_API AOWPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AOWPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UOWAbilitySystemComponent* GetOWAbilitySystemComponent();
	UOWAbilitySet* GetOWAbilitySet();

	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UOWAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AbilitySet")
	TObjectPtr<UOWAbilitySet> AbilitySet;

};
