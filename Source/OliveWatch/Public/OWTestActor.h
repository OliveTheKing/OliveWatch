#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "GameplayEffect.h"
#include "OWTestActor.generated.h"

class USphereComponent;
class UAbilitySystemComponent;

UCLASS()
class OLIVEWATCH_API AOWTestActor : public AActor
{
	GENERATED_BODY()

public:
	AOWTestActor();

protected:
	virtual void BeginPlay() override;

	// 콜리전
	UPROPERTY(VisibleDefaultsOnly, Category = "Test")
	USphereComponent* CollisionComp;

	// 부여할 GE 클래스
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Test")
	TSubclassOf<UGameplayEffect> DamageGameplayEffect;

	// 충돌 처리
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

};
