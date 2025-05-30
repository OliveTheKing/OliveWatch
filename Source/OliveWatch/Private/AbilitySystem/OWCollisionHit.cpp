// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/OWCollisionHit.h"
#include "AbilitySystem/OWHitHandlerComponent.h"
#include "AbilitySystem/OWOverlapHandlerComponent.h"
#include "Components/SphereComponent.h"
#include <Character/OWCharacter.h>

// Sets default values
AOWCollisionHit::AOWCollisionHit()
{
}

// Called when the game starts or when spawned
void AOWCollisionHit::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOWCollisionHit::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (!HitHandler)
	{
		HitHandler = FindComponentByClass<UOWHitHandlerComponent>();
	}

	if (!OverlapHandler)
	{
		OverlapHandler = FindComponentByClass<UOWOverlapHandlerComponent>();
	}

	if (!CollisionComp) {
		CollisionComp = FindComponentByClass<UPrimitiveComponent>();
	}

	if (IsValid(CollisionComp)) {
		CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AOWCollisionHit::OnOverlapBegin);
		RootComponent = CollisionComp;
	}

	if (HitHandler) {
		HitHandler->Initialize(Cast<AOWCharacter>(GetInstigator()), HitEffectSpec);
		CollisionComp->SetNotifyRigidBodyCollision(true);
	}
	if (OverlapHandler) {
		OverlapHandler->Initialize(Cast<AOWCharacter>(GetInstigator()), OverlapEffectSpec);
		CollisionComp->SetGenerateOverlapEvents(true);
	}
}

void AOWCollisionHit::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || !OverlapHandler) return;
	OverlapHandler->OverlapTarget(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AOWCollisionHit::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor || HitHandler) return;
	HitHandler->HitTarget(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
}
