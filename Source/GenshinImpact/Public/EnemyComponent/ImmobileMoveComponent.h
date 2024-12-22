// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/MoveInterface.h"
#include "ImmobileMoveComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GENSHINIMPACT_API UImmobileMoveComponent : public UActorComponent, public IMoveInterface
{
	GENERATED_BODY()

public:
	UImmobileMoveComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void MoveTo(const FVector& Location, float AcceptRadius) override { return; };
	virtual void MoveTo(const FVector& Location, float AcceptRadius, float Speed) { return; };
	virtual void Patrol() override { return; };
	virtual void ChasePlayer() override;
	virtual void TurnTo(const FVector& TargetLocation, float deltaTime) override;
	virtual void Stop() override { return; };
	virtual bool GetIsMoving() const override { return false; }
	virtual bool GetIsChasing() const override { return false; }
	virtual bool GetIsResting() const override { return bIsResting; }
	virtual bool GetIsIdling() const override { return bIsIdling; }
	virtual FVector GetSpawnLocation() const { return SpawnLocation; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void RenewState();

	// 出生点位置
	FVector SpawnLocation;

	// 当前速度
	float CurrentSpeed;

	// 休息时间
	UPROPERTY(EditAnywhere, Category = "Move Settings")
	float RestTime;

	// 转身速度
	UPROPERTY(EditAnywhere, Category = "Move Settings")
	float TurnRate;

	// 是否正在休息
	bool bIsResting;

	// 是否待机
	bool bIsIdling;

	// 用于休息时间的计时器
	FTimerHandle RestTimerHandle;
};
