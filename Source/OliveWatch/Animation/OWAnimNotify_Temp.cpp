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

    // �� �±׿� ���̷ε� �غ�
    FGameplayEventData Payload;
    Payload.EventTag = OWGameplayTags::Notify_Fire;   // ex) GameplayEvent.Notify.Fire
    Payload.Instigator = Owner;
    // �ʿ��ϸ� Payload.TargetData = ��

    // �� �� �ٷ� ASC���� �̺�Ʈ ����
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner, Payload.EventTag, Payload);
}
