// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Effects/OWGameplayEffect.h"
#include "AbilitySystem/Attributes/OWAttributeSet.h"
#include "OWGE_Cost.generated.h"

/**
 * 현재는 궁극기 스킬의 코스트를 0으로 바꾸는 역할을 수행합니다.
 * @todo 궁극기 스킬의 코스트를 0으로 바꾸는 것이 아니라, 코스트를 소모하는 스킬에 적용 가능하도록 확장
 * @todo 궁극기 스킬의 코스트를 0, 15(영웅 변경), 풀차징(의도적 궁극기 충전 - Ex. 훈련장) 등 다양한 값으로 설정할 수 있도록 확장
 * @todo 해당 C++ 파일을 확장성 있게 만들고 BP로 수정하게 하는 방향이 좋아보임.
 */
UCLASS()
class OLIVEWATCH_API UOWGE_Cost : public UOWGameplayEffect
{
	GENERATED_BODY()

public:

	UOWGE_Cost() {
		DurationPolicy = EGameplayEffectDurationType::Instant;
	}
};
