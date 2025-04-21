// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "OWAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)			\
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName)	\
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)				\
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)				\
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */

UCLASS()
class OLIVEWATCH_API UOWAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	ATTRIBUTE_ACCESSORS(ThisClass, MaxHP);
	ATTRIBUTE_ACCESSORS(ThisClass, HP);
	ATTRIBUTE_ACCESSORS(ThisClass, MaxBullets);
	ATTRIBUTE_ACCESSORS(ThisClass, Bullets);
	ATTRIBUTE_ACCESSORS(ThisClass, Speed);


private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxHP;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData HP;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxBullets;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Bullets;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Speed;
};
