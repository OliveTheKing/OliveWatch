// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/OWMonster.h"

#include "AbilitySystem/OWAbilitySet.h"
#include "AbilitySystem/OWAbilitySystemComponent.h"

AOWMonster::AOWMonster()
{
	AbilitySystemComponent = CreateDefaultSubobject<UOWAbilitySystemComponent>("AbilitySystemComponent");
}

void AOWMonster::BeginPlay()
{
	Super::BeginPlay();

	AbilitySet->GiveToAbilitySystem(AbilitySystemComponent);

}