// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/OWDamageCollisionCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Physics/OWCollision.h"

void AOWDamageCollisionCharacter::AttackHitCheck()
{
	FHitResult OutHitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	const float AttackRange = 40.0f;
	const float AttackRadius = 50.0f;
	const float AttackDamage = 30.0f;
	const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + GetActorForwardVector() * AttackRange;

	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, CCHANNEL_OWACTION, FCollisionShape::MakeSphere(AttackRadius), Params);
	GEngine->AddOnScreenDebugMessage(
		-1,                     // Key: -1은 항상 새로운 메시지 출력
		2.0f,                   // Duration: 2초 동안 표시
		FColor::Red,           // 텍스트 색상
		TEXT("Hit NotDetected!")  // 출력할 메시지
	);
	if (HitDetected)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,                     // Key: -1은 항상 새로운 메시지 출력
			2.0f,                   // Duration: 2초 동안 표시
			FColor::Red,           // 텍스트 색상
			TEXT("Hit Detected!")  // 출력할 메시지
		);
	}
#if ENABLE_DRAW_DEBUG

	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
	float CapsuleHalfHeight = AttackRange * 0.5f;
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);
#endif
}
