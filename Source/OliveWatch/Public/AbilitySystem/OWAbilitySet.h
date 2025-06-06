﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "InputTriggers.h"
#include "OWAbilitySet.generated.h"

class AOWPlayerController;
class UOWAbilitySystemComponent;
class UOWGameplayAbility;
class UGameplayEffect;
class UAttributeSet;

/**
 * 
 */

// Ability 정보를 구조체로 저장
USTRUCT()
struct FOWAbilitySet_GameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UOWGameplayAbility> Ability = nullptr;

	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly)
	ETriggerEvent TriggerType;

	UPROPERTY(EditDefaultsOnly)
	TArray<FGameplayTag> EffectsTags;
};

// Effect 정보를 구조체로 저장
USTRUCT()
struct FOWAbilitySet_GameplayEffect
{
	GENERATED_BODY()

public:

	// Gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> GameplayEffect = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float EffectLevel = 1.0f;

};

// Attribute Set을 구조체로 저장
USTRUCT()
struct FOWAbilitySet_AttributeSet
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttributeSet> AttributeSet = nullptr;

};

UCLASS()
class OLIVEWATCH_API UOWAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UOWAbilitySet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION()
	const FOWAbilitySet_GameplayAbility FindAbilityByTag(const FGameplayTag& InputTag) const;

	UFUNCTION()
	void GiveToAbilitySystem(UOWAbilitySystemComponent* OWASC) const;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta = (TitleProperty = Ability))
	TArray<FOWAbilitySet_GameplayAbility> GrantedGameplayAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects", meta = (TitleProperty = Effect))
	TArray<FOWAbilitySet_GameplayEffect> GrantedGameplayEffects;

	UPROPERTY(EditDefaultsOnly, Category = "Attribute Sets", meta = (TitleProperty = AttributeSet))
	TArray<FOWAbilitySet_AttributeSet> GrantedAttributes;

};
