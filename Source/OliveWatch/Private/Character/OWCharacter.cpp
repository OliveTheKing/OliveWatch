// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/OWCharacter.h"
#include "Player/OWPlayerState.h"
#include "AbilitySystem/OWAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "OWGameplayTags.h"

UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
TObjectPtr<USpringArmComponent> CameraBoom;

UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
TObjectPtr<UCameraComponent> FollowCamera;

// Sets default values
AOWCharacter::AOWCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// SpringArm
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = true;

	// FollowCamera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

// Called when the game starts or when spawned
void AOWCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOWCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AOWPlayerState* State = GetPlayerState<AOWPlayerState>()) {
		AbilitySystemComponent = Cast<UOWAbilitySystemComponent>(State->GetOWAbilitySystemComponent());
		AbilitySystemComponent->InitAbilityActorInfo(State, this);
	}
}

void AOWCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (AOWPlayerState* State = GetPlayerState<AOWPlayerState>())
	{
		AbilitySystemComponent = Cast<UOWAbilitySystemComponent>(State->GetAbilitySystemComponent());
		AbilitySystemComponent->InitAbilityActorInfo(State, this);
	}
}

void AOWCharacter::Move(const FVector& direction, const float& speed)
{
	if (!CanMoveOrJump()) {
		return;
	}
	const FRotator YawRot(0, GetControlRotation().Yaw, 0);

	const FVector ForwardDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	const FVector RightDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

	const FVector MoveDir = ForwardDir * direction.Y + RightDir * direction.X;

	AddMovementInput(MoveDir, speed);
}

void AOWCharacter::Look(const FVector& direction)
{
	AddControllerYawInput(direction.X);
	AddControllerPitchInput(direction.Y);
}

void AOWCharacter::ActivateAbility(FGameplayTag AbilityTag)
{
	AbilitySystemComponent->ActivateAbility(AbilityTag);
}

UOWAbilitySystemComponent* AOWCharacter::GetOWAbilitySystemComponent()
{
	return AbilitySystemComponent;
}
void AOWCharacter::Jump()
{
	if (!CanMoveOrJump()) {
		return;
	}
	Super::Jump();
}


bool AOWCharacter::CanMoveOrJump()
{
	const FGameplayAbilityActorInfo* ActorInfo = nullptr;
	if (AbilitySystemComponent) {
		ActorInfo = AbilitySystemComponent->AbilityActorInfo.Get();
	}
	if (ActorInfo && ActorInfo->AbilitySystemComponent->HasMatchingGameplayTag(OWGameplayTags::Status_MovementBlocked))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("Status: Movement Blocked"));
		return false;
	}
	return true;
}

