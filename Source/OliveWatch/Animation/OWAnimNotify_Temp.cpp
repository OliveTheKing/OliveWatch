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

    // ① AnimInstance가 붙은 Pawn → PlayerState 얻기
    ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
    if (!Character) return;

    AOWPlayerState* PS = Character->GetPlayerState<AOWPlayerState>();
    if (!PS)     return;

    // ② 페이로드 구성
    FGameplayEventData Payload;
    Payload.EventTag = OWGameplayTags::Notify_Fire;
    Payload.Instigator = Character;

    // ③ PlayerState에 이벤트 전송
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(PS, Payload.EventTag, Payload);
    // (디버그)
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Notify 실행됨"));
}
