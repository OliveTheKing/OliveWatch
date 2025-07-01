// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/OWMonster.h"

#include "AbilitySystem/OWAbilitySet.h"
#include "AbilitySystem/OWAbilitySystemComponent.h"

AOWMonster::AOWMonster()
{
	AbilitySystemComponent = CreateDefaultSubobject<UOWAbilitySystemComponent>("AbilitySystemComponent");

	TimeDuration = 1.f;
	ElapsedTime = 0.f;
	bMoveRight = true;
}

void AOWMonster::BeginPlay()
{
	Super::BeginPlay();

	AbilitySet->GiveToAbilitySystem(AbilitySystemComponent);

}

void AOWMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector MoveDirection = bMoveRight ? FVector::ForwardVector : FVector::BackwardVector;
	ElapsedTime += DeltaTime;
	Move(MoveDirection,0.5f);
	if (ElapsedTime >= TimeDuration) {
		bMoveRight = !bMoveRight;
		ElapsedTime = 0.f;

	}

}
