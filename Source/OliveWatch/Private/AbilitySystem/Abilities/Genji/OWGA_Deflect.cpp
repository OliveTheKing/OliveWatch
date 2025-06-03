// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Genji/OWGA_Deflect.h"

#include "AbilitySystem/OWAbilitySystemComponent.h"
#include "OWGameplayTags.h"

bool UOWGA_Deflect::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	return true;
}

void UOWGA_Deflect::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	AActor* Owner = ActorInfo->AvatarActor.Get();

	// Player에 Deflecting 태그 부여
	ActorInfo->AbilitySystemComponent->AddLooseGameplayTag(OWGameplayTags::State_Deflecting);

	// 일정 시간 이후 종료
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("튕겨내기 시작"));
	Owner->GetWorldTimerManager().SetTimer(DeflectTimerHandle, this, &UOWGA_Deflect::OnDeflectEnd, DeflectDuration, false);
}

void UOWGA_Deflect::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	AActor* Owner = ActorInfo->AvatarActor.Get();

	// Deflecting 태그, 타이머 제거
	ActorInfo->AbilitySystemComponent->RemoveLooseGameplayTag(OWGameplayTags::State_Deflecting);
	Owner->GetWorldTimerManager().ClearTimer(DeflectTimerHandle);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("튕겨내기 끝"));

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UOWGA_Deflect::OnDeflectEnd()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
