// Copyright Epic Games, Inc. All Rights Reserved.

#include "OWProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemComponent.h"
#include "OWGameplayTags.h"
#include "Character/OWCharacter.h"


AOWProjectile::AOWProjectile()
{
    //// Use a sphere as a simple collision representation
    //CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    //CollisionComp->InitSphereRadius(5.0f);
    //CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
    //CollisionComp->OnComponentHit.AddDynamic(this, &AOWProjectile::OnHit);      // set up a notification for when this component hits something blocking

    //// Players can't walk on it
    //CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
    //CollisionComp->CanCharacterStepUpOn = ECB_No;

    // Set as root component
    //RootComponent = CollisionComp;

    // Use a ProjectileMovementComponent to govern this projectile's movement
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
    ProjectileMovement->UpdatedComponent = CollisionComp;
    ProjectileMovement->InitialSpeed = 3000.f;
    ProjectileMovement->MaxSpeed = 3000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = true;

    // Die after 3 seconds by default
    InitialLifeSpan = 3.0f;
    PrimaryActorTick.bCanEverTick = false;
}

// 게임 시작 또는 스폰 시 호출
void AOWProjectile::BeginPlay()
{
    Super::BeginPlay();
    if (ProjectileMovement->Velocity == FVector::ZeroVector) {
        ProjectileMovement->Velocity = GetActorForwardVector() * ProjectileMovement->InitialSpeed;
    }

    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("Projectile Spawned"));
}

void AOWProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    //UAbilitySystemComponent* ASC = OtherActor->FindComponentByClass<UAbilitySystemComponent>();
    UAbilitySystemComponent* ASC = Cast<AOWCharacter>(OtherActor)->GetOWAbilitySystemComponent();

    if (ASC && ASC->HasMatchingGameplayTag(OWGameplayTags::State_Deflecting))
    {
        // 튕겨내기 로직
        FVector DeflectDir = OtherActor->GetActorForwardVector();
        SetActorRotation(DeflectDir.Rotation());
        SetProjectileVelocity(DeflectDir);

        // 주인 변경(겐지로)
        SetOwner(OtherActor);

        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("반사"));
        return;
    }
    else
    {
        Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
    }
}

//void AOWProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
//{
//    //if (!OtherActor || OtherActor == this) return;
//
//    //UAbilitySystemComponent* ASC = OtherActor->FindComponentByClass<UAbilitySystemComponent>();
//    //if (ASC && DamageSpecHandle.IsValid())
//    //{
//    //    ASC->ApplyGameplayEffectSpecToSelf(*DamageSpecHandle.Data.Get());
//    //    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Damage Applied"));
//    //}
//
//    //if (OtherComp && OtherComp->IsSimulatingPhysics())
//    //{
//    //    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("Speeding~"));
//    //    OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
//    //}
//
//    // Destroy();
//}

void AOWProjectile::SetProjectileVelocity(FVector Rotation)
{
    ProjectileMovement->Velocity = Rotation * ProjectileMovement->InitialSpeed;
}
