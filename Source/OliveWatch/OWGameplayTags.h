// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace OWGameplayTags
{
	//�⺻ �̵�
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Move);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Look);
	
	//���� �׼�
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Jump);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Curl);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_MeleeAttack);

	//��ų
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_MainFire);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_SubFire);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Skill1);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Skill2);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Skill3);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Reload);

	//Override
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Override_MainFire);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Override_SubFire);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Override_Skill1);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Override_Skill2);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Override_Skill3);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Override_Reload);

	//Anim notify
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Montage_SpawnProjectile);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Montage_EndAbility);

	//������
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Data_Damage);

	//Player State
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Dead);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_UltimateReady);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Deflecting);

	//Ability
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_GunFire);

	// ĳ���� �����̻�
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_SkillBlocked);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_MovementBlocked);
}