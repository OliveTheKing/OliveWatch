// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/Character.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "OWAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class OLIVEWATCH_API UOWAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UOWAnimInstance();

protected:
	//// ƽ���� �ִϸ��̼� ������Ʈ
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	//// �ʱ�ȭ
	virtual void NativeInitializeAnimation() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class ACharacter> Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class UCharacterMovementComponent> Movement;
};
