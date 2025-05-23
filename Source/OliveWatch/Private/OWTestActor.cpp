#include "OWTestActor.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemGlobals.h"

// Sets default values
AOWTestActor::AOWTestActor()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	RootComponent = CollisionComp;

	CollisionComp->InitSphereRadius(100.f);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComp->SetCollisionObjectType(ECC_WorldStatic);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	CollisionComp->SetGenerateOverlapEvents(true);

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AOWTestActor::OnOverlap);

}

void AOWTestActor::BeginPlay()
{
	Super::BeginPlay();
}

void AOWTestActor::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("TestActor Collision"));
	if (!OtherActor || OtherActor == this || !DamageGameplayEffect)
	{
		return;
	}

	UAbilitySystemComponent* ASC = OtherActor->FindComponentByClass<UAbilitySystemComponent>();
	if (ASC)
	{
		FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
		Context.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(DamageGameplayEffect, 3.0f, Context);
		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle Handle = ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			if (Handle.WasSuccessfullyApplied()) {
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("GE applied"));
			}
		}
	}
}
