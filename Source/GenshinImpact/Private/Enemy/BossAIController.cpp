#include "Enemy/BossAIController.h"
#include "Enemy/EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "EnemyComponent/MoveComponent.h" 
#include "EnemyComponent/AttackComponent.h"
#include "EnemyComponent/DetectComponent.h"
#include "EnemyComponent/EnemyHealthComponent.h"
#include "GlobalTypes/GlobalTypes.h"

ABossAIController::ABossAIController()
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

void ABossAIController::BeginPlay()
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

void ABossAIController::Tick(float DeltaTime)
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
        if (EnemyCharacter->HealthInterface->GetCurrentHealthPercent() < 0.25f && EnemyCharacter->AttackInterface->CanSkillAttack(SKILL_HEAL))
        {
            EnemyCharacter->HealthInterface->UseSkill(SKILL_HEAL);
            return;
        }
        else if (EnemyCharacter->HealthInterface->GetCurrentShieldPercent() < 0.5f && EnemyCharacter->AttackInterface->CanSkillAttack(SKILL_RESTORE_SHIELD))
        {
			EnemyCharacter->HealthInterface->UseSkill(SKILL_RESTORE_SHIELD);
            return;
        }

        for (int SkillOpt = SKILL_START; SkillOpt < SKILL_END; SkillOpt++)
        {
            if (EnemyCharacter->AttackInterface->CanSkillAttack(SKILL_START))
            {
                EnemyCharacter->AttackInterface->SkillAttack(SKILL_START);
                return;
            }
        }
        
        if (EnemyCharacter->AttackInterface->CanAttack())
        {
            EnemyCharacter->AttackInterface->NormalAttack();
        }
        else
        {
            EnemyCharacter->MoveInterface->ChasePlayer();
        }
    }
    else if (bCanDetectPlayer)
    {
        // 检测到玩家，选择追逐或攻击
        if (EnemyCharacter->AttackInterface->CanSkillAttack())
        {
            EnemyCharacter->AttackInterface->SkillAttack();
        }
        else if (EnemyCharacter->AttackInterface->CanAttack())
        {
            EnemyCharacter->AttackInterface->NormalAttack();
        }
        else if (EnemyCharacter->AttackInterface->IsInRange())
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
