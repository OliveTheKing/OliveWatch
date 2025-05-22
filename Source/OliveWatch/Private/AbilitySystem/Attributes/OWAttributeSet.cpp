// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/OWAttributeSet.h"

#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "OWGameplayTags.h"

UOWAttributeSet::UOWAttributeSet()
{

}

void UOWAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UOWAttributeSet, HP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOWAttributeSet, Bullets, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOWAttributeSet, Speed, COND_None, REPNOTIFY_Always);

}

void UOWAttributeSet::OnRep_HP(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOWAttributeSet, HP, OldValue);
}

void UOWAttributeSet::OnRep_Bullets(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOWAttributeSet, Bullets, OldValue);
}

// Instant GE로 BaseValue 변경 직전 실행
bool UOWAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	Super::PreGameplayEffectExecute(Data);

	return true;
}

void UOWAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)  
{  
   Super::PostGameplayEffectExecute(Data);  

   //HP 0 이하 시 사망처리
   if (Data.EvaluatedData.Attribute == GetHPAttribute())  
   {  
       if (GetHP() <= 0.f)
       {  
           UAbilitySystemComponent* ASC = &Data.Target;
           if (ASC && !ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(TEXT("State.Dead"))))  
           {  
               static const FGameplayTag DeadTag = FGameplayTag::RequestGameplayTag(TEXT("State.Dead"));  
               ASC->AddLooseGameplayTag(DeadTag);
			   GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("DEAD"));
           }  
       }  
   }  
}

// BaseValue 변경 직전 실행
void UOWAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

// CurrentValue 변경 직전 실행
void UOWAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

// CurrentValue 변경 직후 실행
void UOWAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	// 테스트용
	FString Msg = FString::Printf(TEXT("before: %f\nafter: %f"), OldValue, NewValue);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, Msg);
}

void UOWAttributeSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	// 범위 벗어나지 않게 조정
	if (Attribute == GetHPAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHP());
	}
	else if (Attribute == GetBulletsAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxBullets());
	}
}


