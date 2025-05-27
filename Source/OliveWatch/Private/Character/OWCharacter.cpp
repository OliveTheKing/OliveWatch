// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/OWCharacter.h"
#include "Player/OWPlayerState.h"
#include "AbilitySystem/OWAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	if (WeaponComponentClass)
	{
		WeaponComponent = NewObject<UOWWeaponComponent>(this, WeaponComponentClass);
		WeaponComponent->RegisterComponent();  // World에 등록
	}
}

void AOWCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AOWPlayerState* State = GetPlayerState<AOWPlayerState>()) {
		AbilitySystemComponent = Cast<UOWAbilitySystemComponent>(State->GetOWAbilitySystemComponent());
		AbilitySystemComponent->InitAbilityActorInfo(State, this);
	}
}

void AOWCharacter::Move(const FVector& direction, const float& speed)
{
	//언리얼 좌표 기준으로 변경(Y, X, Z)
	AddMovementInput(FVector(direction.Y, direction.X, 0.f).GetSafeNormal(), speed);
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

