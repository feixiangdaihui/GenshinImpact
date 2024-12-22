// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/EnemyBallProjectile.h"
#include "PlayerController/SumPlayerController.h"
#include "Enemy/EnemyCharacter.h"
#include "Character\PlayCharacter.h"
#include "PlayerComponent/HealthComponent.h"

void AEnemyBallProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		ASumPlayerController* PlayerController = Cast<ASumPlayerController>(GetWorld()->GetFirstPlayerController());
		if (!PlayerController)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to get PlayerController"));
			return;
		}
		APlayCharacter* Player = Cast<APlayCharacter>(OtherActor);
		if (Player)
		{
			Player->HealthComponent->DamageHealthByValue(Damage);
		}
	}
	Destroy();
}
