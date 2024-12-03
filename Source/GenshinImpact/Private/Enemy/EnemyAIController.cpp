#include "Enemy/EnemyAIController.h"
#include "Enemy/EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"

AEnemyAIController::AEnemyAIController()
{
    // 默认检测玩家视角

    // 初始化成员变量
    ControlledEnemy = nullptr;
    TargetPlayer = nullptr;
    PatrolTarget = FVector::ZeroVector;
	LastKnownPlayerLocation = FVector::ZeroVector;

	UE_LOG(LogTemp, Warning, TEXT("Enemy AI Controller Constructed!"));
}

void AEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

    // 获取控制的敌人Pawn
    ControlledEnemy = GetPawn();
    EnemyCharacter = Cast<AEnemyCharacter>(ControlledEnemy);
	UE_LOG(LogTemp, Warning, TEXT("Enemy AI Controller Begin Play!"));
}

void AEnemyAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (ControlledEnemy == nullptr)
        return; // 确保控制器有控制的Pawn

    //UpdateStatePerTick();
    if (EnemyCharacter->IsBeingAttacked && TargetPlayer == nullptr)
    {
        // 如果敌人正在被攻击，转向攻击方向移动一段距离
        FVector AttackDirection = EnemyCharacter->GetLastDamageDirection();
        FVector NewLocation = ControlledEnemy->GetActorLocation() + AttackDirection * 5 * EnemyCharacter->AttackRange;
        MoveToLocation(NewLocation);
    }
    else if (DetectPlayer())
    {
        EnemyCharacter->IsSitting = false;
        float DistanceToPlayer = FVector::Dist(ControlledEnemy->GetActorLocation(), TargetPlayer->GetActorLocation());
        if (DistanceToPlayer <= EnemyCharacter->AttackRange)
        {
            // 如果玩家在攻击范围内，执行攻击
            AttackPlayer();
			UE_LOG(LogTemp, Warning, TEXT("Enemy is attacking!"));
        }
        else
        {
            // 如果玩家在追击范围内，执行追击
            ChasePlayer();
			UE_LOG(LogTemp, Warning, TEXT("Enemy is chasing!"));
        }
    }
    else if (LastKnownPlayerLocation != FVector::ZeroVector)
    {
        // 如果玩家不在视野范围内，但是之前有玩家位置信息，继续朝向上次玩家位置移动
        MoveToLocation(LastKnownPlayerLocation);
        if (FVector::Dist(ControlledEnemy->GetActorLocation(), LastKnownPlayerLocation) < EnemyCharacter->AttackRange)
        {
            LastKnownPlayerLocation = FVector::ZeroVector;
            UE_LOG(LogTemp, Warning, TEXT("Reached last known location, starting patrol."));
        }
    }
    else if (EnemyCharacter->IsSitting)
    {
        // 更新计时器
        EnemyCharacter->SittingTimer += DeltaTime;

        if (EnemyCharacter->SittingTimer >= 10.0f) // 如果坐下时间超过5秒
        {
            EnemyCharacter->IsSitting = false; // 结束坐下状态
            EnemyCharacter->SittingTimer = 0.0f; // 重置计时器
			EnemyCharacter->IsPatrol = true; // 开始巡逻
            Patrol();
            UE_LOG(LogTemp, Warning, TEXT("Enemy finished sitting, starting patrol."));
        }
    }
	else if (EnemyCharacter->IsPatrol)
	{
		EnemyCharacter->CurrentSpeed = EnemyCharacter->WalkSpeed;
		EnemyCharacter->PatrolTimer += DeltaTime;
        if (EnemyCharacter->PatrolTimer >= 20.0f) // 如果巡逻时间超过20秒
        {
            EnemyCharacter->IsPatrol = false;
            EnemyCharacter->PatrolTimer = 0.0f; // 重置计时器
            EnemyCharacter->IsSitting = true; // 开始坐下休息
            UE_LOG(LogTemp, Warning, TEXT("Enemy finished patrol, starting sitting."));
        }
        else
            Patrol();
	}
	else
    {
        // 如果未检测到玩家，执行巡逻/坐下休息
        if (FMath::RandRange(0, 99) < 30)
        {
			EnemyCharacter->CurrentSpeed = 0.0f;
			EnemyCharacter->IsSitting = true;
            UE_LOG(LogTemp, Warning, TEXT("Enemy is sitting down!"));
        }
        else
        {
            Patrol();
            UE_LOG(LogTemp, Warning, TEXT("Enemy is patrolling!"));
        }
    }
}

bool AEnemyAIController::DetectPlayer()
{
    if (ControlledEnemy == nullptr)
    {
		EnemyCharacter->PlayerInSight = false;
        return false;
    }

    // 假设场景中只有一个玩家，直接获取玩家
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);  // 获取玩家控制的角色（第一个玩家）

    if (Player == nullptr)
    {
        EnemyCharacter->PlayerInSight = false;
        return false;  // 如果没有玩家角色，返回 false
    }

    FVector DirectionToPlayer = Player->GetActorLocation() - ControlledEnemy->GetActorLocation();
    float DistanceToPlayer = DirectionToPlayer.Size();

    // 检查距离和视角
    if (DistanceToPlayer <= EnemyCharacter->DetectionRange)
    {
        DirectionToPlayer.Normalize();

        // 计算敌人与玩家之间的角度
        float DotProduct = FVector::DotProduct(ControlledEnemy->GetActorForwardVector(), DirectionToPlayer);
        float AngleToPlayer = FMath::RadiansToDegrees(FMath::Acos(DotProduct));

        // 判断玩家是否在检测角度范围内
        if (AngleToPlayer <= EnemyCharacter->DetectionAngle / 2)
        {
            // 进行视线检测，确保视线没有被遮挡
            FHitResult HitResult;
            FCollisionQueryParams CollisionParams;
            CollisionParams.AddIgnoredActor(ControlledEnemy);  // 忽略敌人自己

            // 发射射线从敌人到玩家，检查是否有障碍物
            bool bHit = GetWorld()->LineTraceSingleByChannel(
                HitResult,
                ControlledEnemy->GetActorLocation(),
                Player->GetActorLocation(),
                ECC_Visibility,  // 使用可见性通道进行检测
                CollisionParams
            );

            // 如果射线碰到其他物体（非玩家），则认为视线被阻挡
            if (bHit && HitResult.GetActor() != Player)
            {
                EnemyCharacter->PlayerInSight = false;
                return false;  // 如果视线被阻挡，返回 false
            }

            // 如果没有阻挡，返回 true，玩家在视野范围内
            TargetPlayer = Player;
            EnemyCharacter->PlayerInSight = true;
			LastKnownPlayerLocation = Player->GetActorLocation();
            return true;
        }
    }

    // 未检测到玩家
    EnemyCharacter->PlayerInSight = false;
    TargetPlayer = nullptr;
    return false;
}


void AEnemyAIController::Patrol()
{
    if (ControlledEnemy == nullptr || EnemyCharacter == nullptr)
        return;

    // 使用敌人的出生点作为巡逻点生成的基准
    FVector BaseLocation = EnemyCharacter->SpawnLocation;

    // 如果没有巡逻目标，或者接近当前目标，生成一个新的巡逻目标
    if (PatrolTarget.IsZero() || FVector::Dist(ControlledEnemy->GetActorLocation(), PatrolTarget) <= 500)
    {
        UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
        if (NavSys)
        {
            FNavLocation NewLocation;
            if (NavSys->GetRandomPointInNavigableRadius(BaseLocation, EnemyCharacter->PatrolRange, NewLocation))
            {
                PatrolTarget = NewLocation.Location;
            }
        }
    }

    // 移动到巡逻目标
    EnemyCharacter->CurrentSpeed = EnemyCharacter->WalkSpeed;
	//TurnTowards(PatrolTarget, GetWorld()->GetDeltaSeconds(), EnemyCharacter->RotationRate);
    MoveToLocation(PatrolTarget, EnemyCharacter->AttackRange);
}


void AEnemyAIController::ChasePlayer()
{
    if (ControlledEnemy == nullptr || TargetPlayer == nullptr)
        return;

    // 向玩家移动
	EnemyCharacter->CurrentSpeed = EnemyCharacter->RunSpeed;
    MoveToActor(TargetPlayer, EnemyCharacter->AttackRange);
}

void AEnemyAIController::AttackPlayer()
{
    if (ControlledEnemy == nullptr || TargetPlayer == nullptr)
        return;

    if (EnemyCharacter)
    {
        // 调用敌人角色的攻击函数
        EnemyCharacter->Attack();
    }
}

void AEnemyAIController::TurnTowards(const FVector& TargetLocation, float DeltaTime, float TurnRate)
{
    if (!ControlledEnemy)
        return;

    // 获取当前角色的旋转和位置
    FRotator CurrentRotation = ControlledEnemy->GetActorRotation();
    FVector CurrentLocation = ControlledEnemy->GetActorLocation();

    // 计算到目标位置的方向向量
    FVector DirectionToTarget = (TargetLocation - CurrentLocation).GetSafeNormal();
    // 计算目标旋转，但忽略俯仰（Pitch）变化
    FRotator TargetRotation = DirectionToTarget.ToOrientationRotator();
    TargetRotation.Pitch = 0.0f;  // 保持Pitch为0，确保只在水平方向上旋转

    // 使用RInterpTo进行平滑的插值旋转
    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, TurnRate);
    NewRotation.Pitch = 0.0f;  // 再次确保Pitch为0，以防万一

    // 设置新的旋转到角色上
    ControlledEnemy->SetActorRotation(NewRotation);
}

void AEnemyAIController::UpdateStatePerTick()
{
	if (ControlledEnemy == nullptr || EnemyCharacter == nullptr)
		return;
	EnemyCharacter->IsSitting = false;
}