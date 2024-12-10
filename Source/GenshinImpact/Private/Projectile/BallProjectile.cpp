// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/BallProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PlayerController/SumPlayerController.h"
#include "Enemy/EnemyCharacter.h"
#include "Character\PlayCharacter.h"
// Sets default values
ABallProjectile::ABallProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	SetRootComponent(CollisionComponent);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &ABallProjectile::OnHit);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	MaxDistance = 10000.0f;
	InitialLocation = GetActorLocation();
}

void ABallProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		ASumPlayerController* PlayerController = Cast<ASumPlayerController>(GetWorld()->GetFirstPlayerController());
		if (!PlayerController)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to get PlayerController"));
			return;
		}
		APlayCharacter* Player = Cast<APlayCharacter>(PlayerController->GetPawn());
		//判断OtherActor是否是敌人
		AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor);
		if (Enemy)
		{

			GElement EnemyElementType = Enemy->GetElementType();
			GElement CharacterElementType = Player->GetElementType();
			int EnemyLevel = Enemy->GetLevel();
			int CharacterLevel = Player->GetLevel();
			float ActualDamage = UGlobalTypes::ModifyDamage(Damage, EnemyLevel, CharacterLevel, EnemyElementType, CharacterElementType);
			UE_LOG(LogTemp, Warning, TEXT("Damage: %f"), ActualDamage);
			Enemy->TakeDamageByValue(ActualDamage);
		}
		Destroy();
	}
	Destroy();
}

// Called when the game starts or when spawned
void ABallProjectile::BeginPlay()
{
	Super::BeginPlay();


	
}

// Called every frame
void ABallProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (FVector::Dist(InitialLocation, GetActorLocation()) > MaxDistance)
	{
		Destroy();
	}

}
float ABallProjectile::GetDamage()
{
	return Damage;
}

void ABallProjectile::SetDamage(float damage)
{
	Damage = damage;
}


