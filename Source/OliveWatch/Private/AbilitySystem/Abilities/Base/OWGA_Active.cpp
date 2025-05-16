// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Base/OWGA_Active.h"
#include "GameplayEffect.h"
#include "AbilitySystem//Effects/OWCooldownGameplayEffect.h"
#include "AbilitySystemComponent.h"

UOWGA_Active::UOWGA_Active()
{
	CooldownGameplayEffectClass = UOWCooldownGameplayEffect::StaticClass();
}
