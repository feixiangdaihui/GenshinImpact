#include "Enemy/EnemyAnim.h"
#include "Enemy/EnemyCharacter.h"
#include "EnemyComponent/MoveComponent.h" 
#include "EnemyComponent/AttackComponent.h"
#include "EnemyComponent/DetectComponent.h"
#include "EnemyComponent/EnemyHealthComponent.h"

void UEnemyAnim::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    APawn* OwnerPawn = TryGetPawnOwner();
    if (!OwnerPawn)
    {
        UE_LOG(LogTemp, Error, TEXT("PawnOwner is null during NativeInitializeAnimation"));
        return;
    }

    EnemyCharacter = Cast<AEnemyCharacter>(OwnerPawn);
    if (!EnemyCharacter)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to cast PawnOwner to AEnemyCharacter"));
    }
}


void UEnemyAnim::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    // 检查 EnemyCharacter 是否有效
	if (!EnemyCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("EnemyCharacter not found in the world!"));
		return;
	}

    // 确保接口有效
    if (EnemyCharacter->DetectInterface)
    {
        bCanDetectPlayer = EnemyCharacter->DetectInterface->GetCanDetectPlayer();
		//UE_LOG(LogTemp, Warning, TEXT("bCanDetectPlayer: %d"), bCanDetectPlayer);
    }
    if (EnemyCharacter->AttackInterface)
    {
        bIsAttacking = EnemyCharacter->AttackInterface->GetIsAttacking();
		bIsSkillAttacking = EnemyCharacter->AttackInterface->GetIsSkillAttacking();
		bIsInRange = EnemyCharacter->AttackInterface->IsInRange();
		//UE_LOG(LogTemp, Warning, TEXT("bIsAttacking: %d"), bIsAttacking);
		//UE_LOG(LogTemp, Warning, TEXT("bIsInRange: %d"), bIsInRange);
    }
    if (EnemyCharacter->HealthInterface)
    {
        bIsBeingAttacked = EnemyCharacter->HealthInterface->GetIsBeingAttacked();
        bIsDead = EnemyCharacter->HealthInterface->GetIsDead();
		bIsUsingHealthSkill = EnemyCharacter->HealthInterface->GetIsUsingSkill();
		//UE_LOG(LogTemp, Warning, TEXT("bIsBeingAttacked: %d"), bIsBeingAttacked);
		//UE_LOG(LogTemp, Warning, TEXT("bIsDead: %d"), bIsDead);
    }
    if (EnemyCharacter->MoveInterface)
    {
        bIsMoving = EnemyCharacter->MoveInterface->GetIsMoving();
        bIsChasing = EnemyCharacter->MoveInterface->GetIsChasing();
        bIsResting = EnemyCharacter->MoveInterface->GetIsResting();
		bIsIdling = EnemyCharacter->MoveInterface->GetIsIdling();
		//UE_LOG(LogTemp, Warning, TEXT("bIsMoving: %d"), bIsMoving);
		//UE_LOG(LogTemp, Warning, TEXT("bIsChasing: %d"), bIsChasing);
		//UE_LOG(LogTemp, Warning, TEXT("bIsResting: %d"), bIsResting);
		//UE_LOG(LogTemp, Warning, TEXT("bIsIdling: %d"), bIsIdling);
    }
	//UE_LOG(LogTemp, Warning, TEXT("--------------NativeUpdateAnimation called-----------------"));
}

