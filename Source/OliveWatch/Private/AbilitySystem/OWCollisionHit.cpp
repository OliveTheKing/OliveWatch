// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/OWCollisionHit.h"
#include "AbilitySystem/OWHitHandlerComponent.h"
#include "Components/SphereComponent.h"
#include <Character/OWCharacter.h>

// Sets default values
AOWCollisionHit::AOWCollisionHit()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	CollisionComp->InitSphereRadius(100.0f);

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AOWCollisionHit::OnOverlapBegin);

	HitHandler = CreateDefaultSubobject<UOWHitHandlerComponent>(TEXT("HitHandler"));
}

// Called when the game starts or when spawned
void AOWCollisionHit::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOWCollisionHit::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	RootComponent = CollisionComp;

	HitHandler->Initialize(Cast<AOWCharacter>(GetInstigator()), EffectSpec);
}

void AOWCollisionHit::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;
	HitHandler->HitTarget(OtherActor, OtherComp);
}
