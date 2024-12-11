#include "EnemyComponent/DetectComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

UDetectComponent::UDetectComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
	bCanDetectPlayer = false;
	LastPerceptionLocation = FVector::ZeroVector;
	SightRadius = 1000.0f;
	SightAngle = 150.0f;
}

void UDetectComponent::BeginPlay()
{
    UActorComponent::BeginPlay();

    // 缓存玩家角色
    PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!PlayerCharacter)
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerCharacter not found in the world!"));
    }
}

bool UDetectComponent::DetectPlayer()
{
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);  // 获取玩家控制的角色（第一个玩家）

    if (Player == nullptr)
    {
        bCanDetectPlayer = false;
        return false;  // 如果没有玩家角色，返回 false
    }

    FVector DirectionToPlayer = Player->GetActorLocation() - GetOwner()->GetActorLocation();
    float DistanceToPlayer = DirectionToPlayer.Size();

    // 检查距离和视角
    if (DistanceToPlayer <= SightRadius)
    {
        DirectionToPlayer.Normalize();

        // 计算敌人与玩家之间的角度
        float DotProduct = FVector::DotProduct(GetOwner()->GetActorForwardVector(), DirectionToPlayer);
        float AngleToPlayer = FMath::RadiansToDegrees(FMath::Acos(DotProduct));

        // 判断玩家是否在检测角度范围内
        if (AngleToPlayer <= SightAngle / 2)
        {
            // 进行视线检测，确保视线没有被遮挡
            FHitResult HitResult;
            FCollisionQueryParams CollisionParams;
            CollisionParams.AddIgnoredActor(GetOwner());  // 忽略敌人自己

            // 发射射线从敌人到玩家，检查是否有障碍物
            bool bHit = GetWorld()->LineTraceSingleByChannel(
                HitResult,
                GetOwner()->GetActorLocation(),
                Player->GetActorLocation(),
                ECC_Visibility,  // 使用可见性通道进行检测
                CollisionParams
            );

            // 如果射线碰到其他物体（非玩家），则认为视线被阻挡
            if (bHit && HitResult.GetActor() != Player)
            {
                bCanDetectPlayer = false;
                return false;  // 如果视线被阻挡，返回 false
            }

            // 如果没有阻挡，返回 true，玩家在视野范围内
            PlayerCharacter = Player;
            bCanDetectPlayer = true;
            LastPerceptionLocation = PlayerCharacter->GetActorLocation();
            
            return true;
        }
    }

    // 未检测到玩家
    bCanDetectPlayer = false;
    return false;
}


bool UDetectComponent::DetectSound()
{
    return false;
}