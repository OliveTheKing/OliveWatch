// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/OWTmpProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AOWTmpProjectile::AOWTmpProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
}

// Called when the game starts or when spawned
void AOWTmpProjectile::BeginPlay()
{
	Super::BeginPlay();
}

