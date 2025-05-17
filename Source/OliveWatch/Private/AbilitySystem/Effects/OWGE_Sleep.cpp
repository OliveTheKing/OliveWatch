// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effects/OWGE_Sleep.h"
#include "OWGameplayTags.h"

UOWGE_Sleep::UOWGE_Sleep(const FObjectInitializer& ObjectInitializer) 
	:Super(ObjectInitializer)
{
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FScalableFloat(1.f);	// MakeOutGoingSpec�� �ι�° ���� level�� scale ������ ����

	// �±� �߰� �� ȸ��(GE�� life cycle�� ���� ��)
	InheritableOwnedTagsContainer.AddTag(OWGameplayTags::Status_SkillBlocked);
	InheritableOwnedTagsContainer.AddTag(OWGameplayTags::Status_MovementBlocked);
}

void UOWGE_Sleep::AddGrantedTag(FGameplayTag NewTag)
{
	InheritableOwnedTagsContainer.AddTag(NewTag);
}
