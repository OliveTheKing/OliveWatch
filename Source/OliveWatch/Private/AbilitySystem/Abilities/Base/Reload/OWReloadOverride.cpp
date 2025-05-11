// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Base/Reload/OWReloadOverride.h"

#include "AbilitySystem/Attributes/OWAttributeSet.h"

UOWReloadOverride::UOWReloadOverride()
{
    MaxBulletsDef = FGameplayEffectAttributeCaptureDefinition(
        UOWAttributeSet::GetMaxBulletsAttribute(),
        EGameplayEffectAttributeCaptureSource::Target,
        true);

    RelevantAttributesToCapture.Add(MaxBulletsDef);
}

float UOWReloadOverride::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    // AttributeSet에서 MaxBullets 값 가져와서 반환하기
    FAggregatorEvaluateParameters Params;
    Params.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    Params.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    float MaxBullets = 0.f;
    GetCapturedAttributeMagnitude(MaxBulletsDef, Spec, Params, MaxBullets);

    return MaxBullets;
}
