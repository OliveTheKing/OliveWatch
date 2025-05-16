// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace OWGameplayTags
{
	//기본 이동
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Move);
	
	//공통 액션
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Jump);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Curl);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_MeleeAttack);

	//스킬
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_MainFire);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_SubFire);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Skill1);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Skill2);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Skill3);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Reload);

	//Anim notify
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Montage_SpawnProjectile);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Montage_EndAbility);

	//데이터
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Data_Damage);
}