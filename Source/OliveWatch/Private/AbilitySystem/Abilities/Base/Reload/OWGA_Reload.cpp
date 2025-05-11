// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Base/Reload/OWGA_Reload.h"

#include "AbilitySystem/Effects/OWGameplayEffect.h"
#include "AbilitySystem/OWAbilitySystemComponent.h"
#include "Player/OWPlayerState.h"
#include "AbilitySystem/Attributes/OWAttributeSet.h"

void UOWGA_Reload::SetCurrentMontage(UAnimMontage* InCurrentMontage)
{
	Super::SetCurrentMontage(InCurrentMontage);

}

bool UOWGA_Reload::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	return true;
}

void UOWGA_Reload::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	// Animation 실행

	// Animation event에서 실행
	// 지금은 test용으로 여기서 실행
	Reload();
}

void UOWGA_Reload::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UOWGA_Reload::Reload()
{
	// GE 실행
	FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(ReloadEffect, 1.0f);
	ApplyGameplayEffectSpecToOwner(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), SpecHandle);

	// 테스트 로그 출력용
	AOWPlayerState* PlayerState = Cast<AOWPlayerState>(CurrentActorInfo->PlayerController->PlayerState);
	float CurrentBullets = Cast<UOWAttributeSet>(PlayerState->GetOWAbilitySystemComponent()->GetAttributeSet(UOWAttributeSet::StaticClass()))->GetBullets();

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, FString::Printf(TEXT("현재 총알: %f"), CurrentBullets));
}
