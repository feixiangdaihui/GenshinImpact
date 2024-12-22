// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallProjectile.generated.h"
class USphereComponent;
class UProjectileMovementComponent;
UCLASS()
class GENSHINIMPACT_API ABallProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABallProjectile();
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> CollisionComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	float MaxDistance;

	float Damage;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector InitialLocation;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	float GetDamage();
	void SetDamage(float damage);

};
