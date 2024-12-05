#include "Enemycomponent/MoveComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"

UMoveComponent::UMoveComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    // 初始化默认值
    PatrolRange = 500.0f;
    WalkSpeed = 100.0f;
    RunSpeed = 200.0f;
    TurnRate = 5.0f; // 默认转身速度
	CurrentSpeed = WalkSpeed;
	bIsMoving = false;
	bIsChasing = false;
	bIsResting = false;
}

void UMoveComponent::BeginPlay()
{
    UActorComponent::BeginPlay();

    // 获取敌人的出生点
    if (AActor* Owner = GetOwner())
    {
        SpawnLocation = Owner->GetActorLocation();
        UE_LOG(LogTemp, Warning, TEXT("Spawn location initialized: %s"), *SpawnLocation.ToString());
    }
}

void UMoveComponent::MoveTo(const FVector& Location)
{
    if (AActor* Owner = GetOwner())
    {
        FVector CurrentLocation = Owner->GetActorLocation();
        FVector Direction = (Location - CurrentLocation).GetSafeNormal();

        // 调用平滑转向，使用默认转身速度
        TurnTo(Direction, GetWorld()->GetDeltaSeconds(), TurnRate);

        // 移动到目标位置
        bIsChasing = false;
        bIsMoving = true;
        bIsResting = false;
        CurrentSpeed = WalkSpeed;
        FVector NewLocation = CurrentLocation + Direction * WalkSpeed * GetWorld()->GetDeltaSeconds();
        Owner->SetActorLocation(NewLocation);

        UE_LOG(LogTemp, Warning, TEXT("Moving to location: %s"), *Location.ToString());
    }
}

void UMoveComponent::Patrol()
{
    if (AActor* Owner = GetOwner())
    {
        UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
        if (NavSys)
        {
            FNavLocation PatrolTarget;
            if (NavSys->GetRandomPointInNavigableRadius(SpawnLocation, PatrolRange, PatrolTarget))
            {
                FVector TargetLocation = PatrolTarget.Location;

                FVector CurrentLocation = Owner->GetActorLocation();
                FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();

                // 调用平滑转向，使用默认转身速度
                TurnTo(Direction, GetWorld()->GetDeltaSeconds(), TurnRate);

                // 移动到目标位置
                bIsChasing = false;
                bIsMoving = true;
                bIsResting = false;
				CurrentSpeed = WalkSpeed;
                FVector NewLocation = CurrentLocation + Direction * WalkSpeed * GetWorld()->GetDeltaSeconds();
                Owner->SetActorLocation(NewLocation);

                UE_LOG(LogTemp, Warning, TEXT("Patrolling to location: %s"), *TargetLocation.ToString());
            }
        }
    }
}

void UMoveComponent::ChasePlayer()
{
    if (AActor* Owner = GetOwner())
    {
        AActor* Player = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
        if (Player)
        {
            FVector PlayerLocation = Player->GetActorLocation();
            FVector CurrentLocation = Owner->GetActorLocation();
            FVector Direction = (PlayerLocation - CurrentLocation).GetSafeNormal();

            // 调用平滑转向，使用自定义的更快转身速度
            TurnTo(Direction, GetWorld()->GetDeltaSeconds(), TurnRate * 1.5f);

            // 移动到目标位置
			bIsChasing = true;
            bIsMoving = false;
			bIsResting = false;
			CurrentSpeed = RunSpeed;
            FVector NewLocation = CurrentLocation + Direction * RunSpeed * GetWorld()->GetDeltaSeconds();
            Owner->SetActorLocation(NewLocation);

            UE_LOG(LogTemp, Warning, TEXT("Chasing player at location: %s"), *PlayerLocation.ToString());
        }
    }
}

void UMoveComponent::TurnTo(const FVector& Direction, float DeltaTime, float CustomTurnRate)
{
    if (AActor* Owner = GetOwner())
    {
        FRotator CurrentRotation = Owner->GetActorRotation();
        FRotator TargetRotation = Direction.Rotation();

        // 使用 RInterpTo 实现平滑转向
        FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, CustomTurnRate);
        Owner->SetActorRotation(NewRotation);

        UE_LOG(LogTemp, Warning, TEXT("Turning to direction: %s with TurnRate: %f"), *Direction.ToString(), CustomTurnRate);
    }
}
