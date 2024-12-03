#include "Enemy/EnemyAnim.h"
#include "Enemy/EnemyCharacter.h"

void UEnemyAnim::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    // 尝试获取动画实例的拥有者，并转换为AEnemyCharacter类型
    EnemyCharacter = Cast<AEnemyCharacter>(TryGetPawnOwner());
    if (EnemyCharacter)
    {
        WalkSpeed = EnemyCharacter->WalkSpeed;
	    RunSpeed = EnemyCharacter->RunSpeed;
    }
}

void UEnemyAnim::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (!EnemyCharacter)
        EnemyCharacter = Cast<AEnemyCharacter>(TryGetPawnOwner());

    if (EnemyCharacter)
    {
        // 更新动画状态变量
        CurrentSpeed = EnemyCharacter->GetVelocity().Size(); 
		//UE_LOG(LogTemp, Warning, TEXT("speed is %f"), CurrentSpeed);
        IsAttacking = EnemyCharacter->IsAttacking;         
        IsBeingAttacked = EnemyCharacter->IsBeingAttacked; 
		IsDead = EnemyCharacter->IsDead;
		IsPatrol = EnemyCharacter->IsPatrol;
		IsSitting = EnemyCharacter->IsSitting;
		PlayerInSight = EnemyCharacter->PlayerInSight;
    }
    else
    {
        IsDead = true;
    }
}
