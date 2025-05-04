// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "OWAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class OLIVEWATCH_API UOWAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	//// 틱마다 애니메이션 업데이트
	//virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	//// 초기화
	//virtual void NativeInitializeAnimation() override;
};
