// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/OWHitHandlerComponent.h"
#include "AbilitySystemComponent.h"
#include "Character/OWCharacter.h"

// Sets default values for this component's properties
UOWHitHandlerComponent::UOWHitHandlerComponent()
{
	
}

void UOWHitHandlerComponent::Initialize(AOWCharacter* InInstigator, const TArray<FGameplayEffectSpecHandle>& InEffectSpecs)
{
	Instigator = InInstigator;
	EffectSpecs = InEffectSpecs;
}

void UOWHitHandlerComponent::HitTarget(AActor* TargetActor, UPrimitiveComponent* OtherComp)
{
	if (Cast<AOWCharacter>(TargetActor) == Instigator) return;
	UAbilitySystemComponent* ASC = TargetActor->FindComponentByClass<UAbilitySystemComponent>();
	if (!ASC) return;

	for (FGameplayEffectSpecHandle Effect : EffectSpecs) {
		if (Effect.IsValid())
		{
			ASC->ApplyGameplayEffectSpecToSelf(*Effect.Data.Get());
			GEngine->AddOnScreenDebugMessage(12345, 3.0f, FColor::Red, TEXT("Applied!!!"));
		}
	}
}


// Called when the game starts
void UOWHitHandlerComponent::BeginPlay()
{
	Super::BeginPlay();
}
