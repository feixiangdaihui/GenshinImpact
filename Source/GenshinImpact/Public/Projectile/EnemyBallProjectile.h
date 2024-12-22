// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/BallProjectile.h"
#include "EnemyBallProjectile.generated.h"

/**
 * 
 */
UCLASS()
class GENSHINIMPACT_API AEnemyBallProjectile : public ABallProjectile
{
	GENERATED_BODY()
public:
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
