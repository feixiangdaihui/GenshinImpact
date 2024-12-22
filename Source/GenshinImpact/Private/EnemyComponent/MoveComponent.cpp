#include "Enemycomponent/MoveComponent.h"
#include "Enemy/EnemyAIController.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"

UMoveComponent::UMoveComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    // 初始化默认值
    PatrolRange = 1000.0f;
    WalkSpeed = 100.0f;
    RunSpeed = 200.0f;
    TurnRate = 5.0f; // 默认转身速度
	CurrentSpeed = WalkSpeed;
	SpawnLocation = FVector::ZeroVector;
    PatrolTarget = FVector::ZeroVector;
	bIsMoving = true;
	bIsChasing = false;
	bIsResting = false;
	bIsIdling = false;
	PatrolTime = 20.0f;
	RestTime = 5.0f;
	EnemyMovement = nullptr;
}

void UMoveComponent::BeginPlay()
{
    UActorComponent::BeginPlay();

    // 获取敌人的出生点
    if (AActor* Owner = GetOwner())
    {
        SpawnLocation = Owner->GetActorLocation();
		EnemyMovement = Cast<ACharacter>(GetOwner())->GetCharacterMovement();
    }
	UE_LOG(LogTemp, Warning, TEXT("run speed:%f"), RunSpeed);
}

void UMoveComponent::MoveTo(const FVector& Location, float AcceptRadius)
{
    if (AActor* Owner = GetOwner())
    {
        AAIController* AIController = Cast<AAIController>(Owner->GetInstigatorController());
        if (!AIController)
        {
            UE_LOG(LogTemp, Error, TEXT("Owner does not have a valid AIController!"));
            return;
        }

        // 使用 AIController 的 MoveToLocation 内置函数
        AIController->MoveToLocation(Location, AcceptRadius);

        if (CurrentSpeed == WalkSpeed)
        {
			bIsMoving = true;
			bIsChasing = false;
        }
        else if (CurrentSpeed == RunSpeed)
        {
            bIsChasing = true;
            bIsMoving = false;
        }
        bIsIdling = false;
        bIsResting = false;

        //UE_LOG(LogTemp, Warning, TEXT("MoveToLocation called: %s"), *Location.ToString());
    }
}

void UMoveComponent::MoveTo(const FVector& Location, float AcceptRadius, float Speed)
{
    if (AActor* Owner = GetOwner())
    {
        AAIController* AIController = Cast<AAIController>(Owner->GetInstigatorController());
        if (!AIController)
        {
            UE_LOG(LogTemp, Error, TEXT("Owner does not have a valid AIController!"));
            return;
        }

        // 使用 AIController 的 MoveToLocation 内置函数
        if (EnemyMovement)
        {
            EnemyMovement->MaxWalkSpeed = Speed;
        }
        else
			UE_LOG(LogTemp, Error, TEXT("EnemyMovement not found in MoveComponent!"));
        AIController->MoveToLocation(Location, AcceptRadius);

        if (!bIsChasing)
            bIsMoving = true;
        else
            bIsMoving = false;
        bIsIdling = false;
        bIsResting = false;

        //UE_LOG(LogTemp, Warning, TEXT("MoveToLocation called: %s"), *Location.ToString());
    }
}

void UMoveComponent::Patrol()
{
    if (AActor* Owner = GetOwner())
    {
        // 如果正在休息，不进行巡逻逻辑
        if (bIsResting)
        {
            bIsChasing = false;
            bIsMoving = false;
            bIsResting = true;
            bIsIdling = false;
            CurrentSpeed = 0.0f;
            EnemyMovement->MaxWalkSpeed = CurrentSpeed;

            UE_LOG(LogTemp, Warning, TEXT("Resting..."));

            // 设置休息定时器，5秒后退出休息状态
            GetWorld()->GetTimerManager().SetTimer(
                RestTimerHandle,
                this,
                &UMoveComponent::StopResting,
                RestTime,
                false
            );
            return;
        }

        // 设置巡逻定时器，巡逻一段时间后进入休息
        GetWorld()->GetTimerManager().SetTimer(
            PatrolTimerHandle,
            this,
            &UMoveComponent::StartResting,
            PatrolTime,
            false
        );

        // 如果没有巡逻目标，或者接近当前目标，生成一个新的巡逻点
        if (PatrolTarget.IsZero() || FVector::Dist(Owner->GetActorLocation(), PatrolTarget) <= 200)
        {
            UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
            if (NavSys)
            {
                FNavLocation NewLocation;
                if (NavSys->GetRandomPointInNavigableRadius(SpawnLocation, PatrolRange, NewLocation))
                {
                    PatrolTarget = NewLocation.Location;

                    // 在调试中显示巡逻点
                    if (GEngine)
                    {
                        // 在游戏世界中绘制巡逻点位置
                        UWorld* World = GetWorld();
                        if (World)
                        {
                            // 绘制一个调试球体来表示巡逻点
                            // 参数分别是：位置，半径，颜色，持续时间
                            DrawDebugSphere(World, PatrolTarget, 20.0f, 12, FColor::Green, false, 2.0f);
                        }
                    }

                    UE_LOG(LogTemp, Warning, TEXT("Generated new patrol target: %s"), *PatrolTarget.ToString());
                }
            }
        }

        // 调用 MoveTo 函数移动到目标点
        bIsMoving = true;
        bIsChasing = false;
        bIsIdling = false;
        bIsResting = false;
        CurrentSpeed = WalkSpeed;
        UE_LOG(LogTemp, Warning, TEXT("Patrolling to location: %s"), *PatrolTarget.ToString());
        MoveTo(PatrolTarget, 100, CurrentSpeed); // 使用 MoveTo 移动到新目标点
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
            //TurnTo(Direction, GetWorld()->GetDeltaSeconds());

            // 移动到目标位置
			bIsChasing = true;
            bIsMoving = false;
			bIsResting = false;
			bIsIdling = false;
			CurrentSpeed = RunSpeed;
            UE_LOG(LogTemp, Warning, TEXT("Chasing player at: %f"), CurrentSpeed);
			MoveTo(PlayerLocation, 100, CurrentSpeed);

            //UE_LOG(LogTemp, Warning, TEXT("Chasing player at location: %s"), *PlayerLocation.ToString());
        }
    }
}

void UMoveComponent::TurnTo(const FVector& Direction, float DeltaTime)
{
    if (AActor* Owner = GetOwner())
    {
        FRotator CurrentRotation = Owner->GetActorRotation();
        FRotator TargetRotation = Direction.Rotation();
        FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, TurnRate);
        Owner->SetActorRotation(NewRotation);
    }
}


void UMoveComponent::Stop()
{
	bIsMoving = false;
	bIsChasing = false;
	bIsResting = false;
	bIsIdling = true;
	CurrentSpeed = 0.0f;
	AActor* Owner = GetOwner();
	if (Owner)
		Owner->SetActorLocation(Owner->GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("Stopping movement"));
}