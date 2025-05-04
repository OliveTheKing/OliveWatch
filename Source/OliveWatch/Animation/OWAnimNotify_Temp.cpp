// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/OWAnimNotify_Temp.h"

#include "GameFramework/Character.h"
#include "Player/OWPlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "OWGameplayTags.h"

void UOWAnimNotify_Temp::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::Notify(MeshComp, Animation);

    if (!MeshComp) return;
    AActor* Owner = MeshComp->GetOwner();
    if (!Owner)   return;

    // ① 태그와 페이로드 준비
    FGameplayEventData Payload;
    Payload.EventTag = OWGameplayTags::Notify_Fire;   // ex) GameplayEvent.Notify.Fire
    Payload.Instigator = Owner;
    // 필요하면 Payload.TargetData = …

    // ② 한 줄로 ASC에게 이벤트 전송
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner, Payload.EventTag, Payload);
}
