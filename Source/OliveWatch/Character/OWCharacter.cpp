// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/OWCharacter.h"

// Sets default values
AOWCharacter::AOWCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOWCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOWCharacter::Move(const FVector2D& direction, const float& speed)
{
	//언리얼식 좌표(Y, X, Z)
	AddMovementInput(FVector(direction.Y, direction.X, 0.f).GetSafeNormal(), speed);
}

