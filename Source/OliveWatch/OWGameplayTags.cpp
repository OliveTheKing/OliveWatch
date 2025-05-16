// Fill out your copyright notice in the Description page of Project Settings.


#include "OWGameplayTags.h"

namespace OWGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Move, "Input.Action.Move");

	//공통 액션
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Jump, "Input.Action.Jump");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Curl, "Input.Action.Curl");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_MeleeAttack, "Input.Action.MeleeAttack");

	//스킬
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_MainFire, "Input.Action.MainFire");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_SubFire, "Input.Action.SubFire");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Skill1, "Input.Action.Skill1");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Skill2, "Input.Action.Skill2");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Skill3, "Input.Action.Skill3");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Reload, "Input.Action.Reload");

	//몽타주 알람
	UE_DEFINE_GAMEPLAY_TAG(Event_Montage_EndAbility, "Event.Montage.EndAbility");
	UE_DEFINE_GAMEPLAY_TAG(Event_Montage_SpawnProjectile, "Event.Montage.SpawnProjectile");

	// 데이터
	UE_DEFINE_GAMEPLAY_TAG(Data_Damage, "Data.Damage");
	
}