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

bool UDetectComponent::DetectPlayer(const FVector& OwnerLocation, const FVector& OwnerForwardVector, float SightRadius, float SightAngle)
{
    if (!PlayerCharacter)
    {
		bCanDetectPlayer = false;
        return false; // 如果未找到玩家，直接返回
    }

    // 获取玩家位置
    FVector PlayerLocation = PlayerCharacter->GetActorLocation();
    FVector DirectionToPlayer = (PlayerLocation - OwnerLocation).GetSafeNormal();

    // 距离检查
    float DistanceToPlayer = FVector::Dist(PlayerLocation, OwnerLocation);
    if (DistanceToPlayer > SightRadius)
    {
        bCanDetectPlayer = false;
        return false; // 超出视力半径范围
    }

    // 角度检查
    float DotProduct = FVector::DotProduct(OwnerForwardVector, DirectionToPlayer);
    float AngleToPlayer = FMath::RadiansToDegrees(FMath::Acos(DotProduct));
    if (AngleToPlayer > SightAngle / 2.0f)
    {
        bCanDetectPlayer = false;
        return false; // 超出视力角度范围
    }

    // 直视检查（射线检测）
    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(GetOwner()); // 忽略自身

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        OwnerLocation,
        PlayerLocation,
        ECC_Visibility,
        QueryParams
    );

    // 如果射线命中目标，检查是否命中玩家
    if (bHit && HitResult.GetActor() == PlayerCharacter)
    {
        LastPerceptionLocation = PlayerLocation;
        bCanDetectPlayer = true;
        return true; // 玩家在视野范围内且可以直视
    }

    bCanDetectPlayer = false;
    return false; // 玩家被遮挡
}

bool UDetectComponent::DetectSound(const FVector& OwnerLocation, float HearingRadius)
{
    return false;
}