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

DECLARE_DELEGATE_OneParam(OWDelegate, FGameplayTag);

/**
 * 
 */

UCLASS()
class OLIVEWATCH_API UOWAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UOWAttributeSet();

public:
	ATTRIBUTE_ACCESSORS(ThisClass, MaxHP);
	ATTRIBUTE_ACCESSORS(ThisClass, HP);
	ATTRIBUTE_ACCESSORS(ThisClass, MaxBullets);
	ATTRIBUTE_ACCESSORS(ThisClass, Bullets);
	ATTRIBUTE_ACCESSORS(ThisClass, Speed);

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_HP(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_Bullets(const FGameplayAttributeData& OldValue);

	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxHP;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), ReplicatedUsing = OnRep_HP)
	FGameplayAttributeData HP;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxBullets;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), ReplicatedUsing = OnRep_Bullets)
	FGameplayAttributeData Bullets;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Speed;

public:
	mutable OWDelegate ExecuteUpdateData;

};
