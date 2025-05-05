// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/OWProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AOWProjectile::AOWProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	// �浹 ������Ʈ ���� �� ����
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AOWProjectile::OnHit);

	// ��Ʈ ������Ʈ�� ����
	RootComponent = CollisionComp;

	// �޽� ������Ʈ ���� �� ����
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f)); // ũ�� ����
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // �޽ô� �浹 ����

	// ������Ÿ�� �����Ʈ ������Ʈ ���� �� ����
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 1.0f; // �߷� ����(���� �̵�)

	// ���� ���� (3�� �� �ڵ� �ı�)
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AOWProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOWProjectile::FireInDirection(const FVector& Direction)
{
	if (ProjectileMovement)
	{
		// �߻� �������� �ӵ� ����
		ProjectileMovement->Velocity = Direction * ProjectileMovement->InitialSpeed;
	}
}

// �浹 ó�� �Լ�
void AOWProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// �ڽ��� �߻��� ���Ϳ��� �浹�� ����
	if (OtherActor && OtherActor != this && OtherActor != GetOwner())
	{
		// AbilitySystem�� ����ϴ� ��� - GAS�� ������ ó��
		//UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
		//if (TargetASC)
		//{
		//	// GAS�� ���� ������ ó�� ������ ���⿡ ����
		//	// ���� ������ ������ GAS ������ ���� �޶���
		//}
		//else
		//{
		//	// TODO : �Ϲ����� ������ ���� ���
		//}

		// ȿ�� ���� (���û���)
		// UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());

		// ������Ÿ�� ����
		Destroy();
	}
}

// Called every frame
void AOWProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}