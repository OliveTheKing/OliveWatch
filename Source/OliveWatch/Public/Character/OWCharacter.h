// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapon/OWWeaponComponent.h"
#include "GameplayTagContainer.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystem/OWAbilitySystemComponent.h"
#include "OWCharacter.generated.h"

UCLASS()
class OLIVEWATCH_API AOWCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOWCharacter();

	UPROPERTY()
	UOWWeaponComponent* WeaponComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//봇을 구현할 시 OWPlayer 와 같은 자식 클래스로 이동할 것
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

public:
	void Move(const FVector& direction, const float& speed = 1.f);
	/**
	 * 캐릭터의 카메라를 마우스 인풋에 따라 회전시킵니다.
	 * @param direction 회전 방향
	 */
	void Look(const FVector& direction);
	void ActivateAbility(FGameplayTag AbilityTag);
	UOWAbilitySystemComponent* GetOWAbilitySystemComponent();
	void Jump() override;

private:
	bool CanMoveOrJump();

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<UOWWeaponComponent> WeaponComponentClass;

protected:
	UPROPERTY()
	TObjectPtr<class UOWAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* FirstPersonCamera;
};