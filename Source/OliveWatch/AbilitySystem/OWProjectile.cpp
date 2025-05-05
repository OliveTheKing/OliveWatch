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

	// 충돌 컴포넌트 생성 및 설정
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AOWProjectile::OnHit);

	// 루트 컴포넌트로 설정
	RootComponent = CollisionComp;

	// 메시 컴포넌트 생성 및 설정
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f)); // 크기 조정
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 메시는 충돌 없음

	// 프로젝타일 무브먼트 컴포넌트 생성 및 설정
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 1.0f; // 중력 있음(직선 이동)

	// 수명 설정 (3초 후 자동 파괴)
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
		// 발사 방향으로 속도 설정
		ProjectileMovement->Velocity = Direction * ProjectileMovement->InitialSpeed;
	}
}

// 충돌 처리 함수
void AOWProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 자신을 발사한 액터와의 충돌은 무시
	if (OtherActor && OtherActor != this && OtherActor != GetOwner())
	{
		// AbilitySystem을 사용하는 경우 - GAS로 데미지 처리
		//UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
		//if (TargetASC)
		//{
		//	// GAS를 통한 데미지 처리 로직을 여기에 구현
		//	// 실제 구현은 게임의 GAS 설정에 따라 달라짐
		//}
		//else
		//{
		//	// TODO : 일반적인 데미지 적용 방법
		//}

		// 효과 생성 (선택사항)
		// UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());

		// 프로젝타일 제거
		Destroy();
	}
}

// Called every frame
void AOWProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}