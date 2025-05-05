// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/OWCharacter.h"
#include "Player/OWPlayerState.h"
#include "AbilitySystem/OWAbilitySystemComponent.h"

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

void AOWCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AOWPlayerState* State = GetPlayerState<AOWPlayerState>()) {
		AbilitySystemComponent = Cast<UOWAbilitySystemComponent>(State->GetOWAbilitySystemComponent());
		AbilitySystemComponent->InitAbilityActorInfo(State, this);
	}
}

void AOWCharacter::Move(const FVector2D& direction, const float& speed)
{
	//언리얼 좌표 기준으로 변경(Y, X, Z)
	AddMovementInput(FVector(direction.Y, direction.X, 0.f).GetSafeNormal(), speed);
}

void AOWCharacter::ActivateAbility(FGameplayTag AbilityTag)
{
	AbilitySystemComponent->ActivateAbility(AbilityTag);
}

