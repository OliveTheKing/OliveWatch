// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/OWCollisionHit.h"
#include "AbilitySystem/OWHitHandlerComponent.h"
#include "AbilitySystem/OWOverlapHandlerComponent.h"
#include "Components/SphereComponent.h"
#include <Character/OWCharacter.h>

// Sets default values
AOWCollisionHit::AOWCollisionHit()
{
	HitHandler = CreateDefaultSubobject<UOWHitHandlerComponent>(TEXT("HitHandler"));
	OverlapHandler = CreateDefaultSubobject<UOWOverlapHandlerComponent>(TEXT("OverlapHandler"));
}

// Called when the game starts or when spawned
void AOWCollisionHit::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOWCollisionHit::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (!CollisionComp) {
		CollisionComp = FindComponentByClass<UPrimitiveComponent>();
	}

	if (IsValid(CollisionComp)) {
		CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AOWCollisionHit::OnOverlapBegin);
		RootComponent = CollisionComp;
	}

	if(HitHandler) HitHandler->Initialize(Cast<AOWCharacter>(GetInstigator()), HitEffectSpec);
	if(OverlapHandler) OverlapHandler->Initialize(Cast<AOWCharacter>(GetInstigator()), OverlapEffectSpec);
}

void AOWCollisionHit::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || !HitHandler) return;
	OverlapHandler->OverlapTarget(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AOWCollisionHit::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor || !OverlapHandler) return;
	HitHandler->HitTarget(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
}
