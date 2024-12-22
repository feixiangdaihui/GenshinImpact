#include "Enemy/EnemyAIController.h"
#include "Enemy/EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "EnemyComponent/MoveComponent.h" 
#include "EnemyComponent/AttackComponent.h"
#include "EnemyComponent/DetectComponent.h"
#include "EnemyComponent/EnemyHealthComponent.h"

AEnemyAIController::AEnemyAIController()
{
	// 初始化变量
	EnemyCharacter = nullptr;
	bCanDetectPlayer = false;
	bIsAttacking = false;
	bIsBeingAttacked = false;
	bIsDead = false;
	bIsMoving = false;
	bIsChasing = false;
	bIsResting = false;
}

void AEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

	// 获取控制的敌人
	EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());
    if (EnemyCharacter == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("EnemyCharacter not found in AIController!"));
        return; // 确保控制器有控制的Pawn
    }
    else
		UE_LOG(LogTemp, Warning, TEXT("EnemyCharacter found in AIController!"));
}

void AEnemyAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (EnemyCharacter == nullptr)
    {
		UE_LOG(LogTemp, Error, TEXT("EnemyCharacter not found in AIController!"));
        return; // 确保控制器有控制的Pawn
    }


	// 更新状态变量
    if (EnemyCharacter->MoveInterface)
    {
        bIsMoving = EnemyCharacter->MoveInterface->GetIsMoving();
        bIsChasing = EnemyCharacter->MoveInterface->GetIsChasing();
        bIsResting = EnemyCharacter->MoveInterface->GetIsResting();
    }
    else
        UE_LOG(LogTemp, Error, TEXT("MoveInterface not found in AIController!"));

	if (EnemyCharacter->DetectInterface && !bIsResting)
    { 
	    EnemyCharacter->DetectInterface->DetectPlayer();
	    bCanDetectPlayer = EnemyCharacter->DetectInterface->GetCanDetectPlayer();
	}
    else if (bIsResting)
    {
		bCanDetectPlayer = false;
    }
	else
		UE_LOG(LogTemp, Error, TEXT("DetectInterface not found in AIController!"));

	if (EnemyCharacter->AttackInterface)
	    bIsAttacking = EnemyCharacter->AttackInterface->GetIsAttacking();
    else
		UE_LOG(LogTemp, Error, TEXT("AttackInterface not found in AIController!"));

    if (EnemyCharacter->HealthInterface)
    {
        bIsBeingAttacked = EnemyCharacter->HealthInterface->GetIsBeingAttacked();
        bIsDead = EnemyCharacter->HealthInterface->GetIsDead();
    }
    else
		UE_LOG(LogTemp, Error, TEXT("HealthInterface not found in AIController!"));

    // 行为决策逻辑
    if (bIsDead)
    {
        EnemyCharacter->MoveInterface->Stop();
    }
    else if (bIsBeingAttacked)
    {
        if (EnemyCharacter->AttackInterface->CanAttack())
        {
            EnemyCharacter->AttackInterface->NormalAttack();
        }
        else if (EnemyCharacter->AttackInterface->CanRemoteAttack())
        {
            EnemyCharacter->AttackInterface->NormalRemoteAttack();
        }
        else
        {
            EnemyCharacter->MoveInterface->ChasePlayer();
        }
    }
    else if (bCanDetectPlayer)
    {
        // 检测到玩家，选择追逐或攻击
        if (EnemyCharacter->AttackInterface->CanAttack())
        {
            EnemyCharacter->AttackInterface->NormalAttack();
			UE_LOG(LogTemp, Warning, TEXT("AI:Enemy is attacking!"));
        }
        else if (EnemyCharacter->AttackInterface->CanRemoteAttack())
        {
			EnemyCharacter->AttackInterface->NormalRemoteAttack();
        }
        else if (EnemyCharacter->AttackInterface->IsInRange() || EnemyCharacter->AttackInterface->IsInRemoteRange())
        {
            EnemyCharacter->MoveInterface->Stop();
        }
        else
        {
            EnemyCharacter->MoveInterface->ChasePlayer();
            UE_LOG(LogTemp, Warning, TEXT("AI:Enemy is chasing!"));
        }
    }
	else if (EnemyCharacter->DetectInterface->GetLastPerceptionLocation() != FVector::ZeroVector 
        && FVector::Dist(EnemyCharacter->GetActorLocation(), EnemyCharacter->DetectInterface->GetLastPerceptionLocation()) > 200.0f)
    {
		EnemyCharacter->MoveInterface->MoveTo(EnemyCharacter->DetectInterface->GetLastPerceptionLocation(), 100);
    }
    else
    {
        // 默认行为：巡逻
		//UE_LOG(LogTemp, Warning, TEXT("Enemy is patrolling!"));
        EnemyCharacter->MoveInterface->Patrol();
    }
}