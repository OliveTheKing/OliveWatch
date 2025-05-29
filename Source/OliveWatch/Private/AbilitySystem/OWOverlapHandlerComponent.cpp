// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/OWOverlapHandlerComponent.h"
#include "AbilitySystemComponent.h"
#include "Character/OWCharacter.h"

// Sets default values for this component's properties
UOWOverlapHandlerComponent::UOWOverlapHandlerComponent()
{
}

void UOWOverlapHandlerComponent::Initialize(AOWCharacter* InInstigator, const TArray<FGameplayEffectSpecHandle>& InEffectSpecs)
{
	Instigator = InInstigator;
	EffectSpecs = InEffectSpecs;
}

void UOWOverlapHandlerComponent::OverlapTarget(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AOWCharacter>(OtherActor) == Instigator) return;
	UAbilitySystemComponent* ASC = OtherActor->FindComponentByClass<UAbilitySystemComponent>();
	if (!ASC) return;

	for (FGameplayEffectSpecHandle Effect : EffectSpecs) {
		if (Effect.IsValid())
		{
			ASC->ApplyGameplayEffectSpecToSelf(*Effect.Data.Get());
			GEngine->AddOnScreenDebugMessage(12345, 3.0f, FColor::Red, TEXT("Overlap Applied!!!"));
		}
	}
}

// Called when the game starts
void UOWOverlapHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}