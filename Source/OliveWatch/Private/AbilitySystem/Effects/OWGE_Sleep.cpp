// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effects/OWGE_Sleep.h"
#include "OWGameplayTags.h"

UOWGE_Sleep::UOWGE_Sleep(const FObjectInitializer& ObjectInitializer) 
	:Super(ObjectInitializer)
{
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FScalableFloat(1.f);	// MakeOutGoingSpec의 두번째 인자 level로 scale 곱연산 가능

	// 태그 추가 및 회수(GE의 life cycle과 같이 감)
	InheritableOwnedTagsContainer.AddTag(OWGameplayTags::Status_SkillBlocked);
	InheritableOwnedTagsContainer.AddTag(OWGameplayTags::Status_MovementBlocked);
}