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

	//상태
	UE_DEFINE_GAMEPLAY_TAG(State_Death, "State.Death");
	UE_DEFINE_GAMEPLAY_TAG(State_Healing, "State.Healing");
	UE_DEFINE_GAMEPLAY_TAG(State_HealBan, "State.HealBan");
}