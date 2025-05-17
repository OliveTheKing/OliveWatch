// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effects/OWGE_Sleep.h"
#include "OWGameplayTags.h"

UOWGE_Sleep::UOWGE_Sleep(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) 
	:Super(ObjectInitializer)
{
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
}

void UOWGE_Sleep::InitSleepEffect(float SleepDuration)
{
	DurationMagnitude = FScalableFloat(SleepDuration);

	// 태그 추가 및 회수(GE의 life cycle과 같이 감)
	InheritableOwnedTagsContainer.AddTag(OWGameplayTags::Status_SkillBlocked);
	InheritableOwnedTagsContainer.AddTag(OWGameplayTags::Status_MovementBlocked);
}
