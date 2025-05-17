// Fill out your copyright notice in the Description page of Project Settings.


#include "OWGameplayTags.h"

namespace OWGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Move, "Input.Action.Move");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Look, "Input.Action.Look");

	//���� �׼�
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Jump, "Input.Action.Jump");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Curl, "Input.Action.Curl");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_MeleeAttack, "Input.Action.MeleeAttack");

	//��ų
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_MainFire, "Input.Action.MainFire");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_SubFire, "Input.Action.SubFire");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Skill1, "Input.Action.Skill1");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Skill2, "Input.Action.Skill2");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Skill3, "Input.Action.Skill3");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Reload, "Input.Action.Reload");

	//override
	UE_DEFINE_GAMEPLAY_TAG(Input_Override_MainFire, "Input.Override.MainFire");
	UE_DEFINE_GAMEPLAY_TAG(Input_Override_SubFire, "Input.Override.SubFire");
	UE_DEFINE_GAMEPLAY_TAG(Input_Override_Skill1, "Input.Override.Skill1");
	UE_DEFINE_GAMEPLAY_TAG(Input_Override_Skill2, "Input.Override.Skill2");
	UE_DEFINE_GAMEPLAY_TAG(Input_Override_Skill3, "Input.Override.Skill3");
	UE_DEFINE_GAMEPLAY_TAG(Input_Override_Reload, "Input.Override.Reload");

	//��Ÿ�� �˶�
	UE_DEFINE_GAMEPLAY_TAG(Event_Montage_EndAbility, "Event.Montage.EndAbility");
	UE_DEFINE_GAMEPLAY_TAG(Event_Montage_SpawnProjectile, "Event.Montage.SpawnProjectile");

	// ������
	UE_DEFINE_GAMEPLAY_TAG(Data_Damage, "Data.Damage");
	

	//Player State
	UE_DEFINE_GAMEPLAY_TAG(State_Dead, "State.Dead");
	UE_DEFINE_GAMEPLAY_TAG(State_UltimateReady, "State.UltimateReady");
	UE_DEFINE_GAMEPLAY_TAG(State_Deflecting, "State.Deflecting");

	//Ability
	UE_DEFINE_GAMEPLAY_TAG(Ability_GunFire, "Ability.GunFire");

	// ĳ���� �����̻�
	UE_DEFINE_GAMEPLAY_TAG(Status_SkillBlocked, "Status.SkillBlocked");
	UE_DEFINE_GAMEPLAY_TAG(Status_MovementBlocked, "Status.MovementBlocked");
}