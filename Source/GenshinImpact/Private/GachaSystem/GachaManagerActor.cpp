
#include "GachaSystem/GachaManagerActor.h"
#include "Engine/Engine.h"

// Sets default values
AGachaManagerActor::AGachaManagerActor()
{
    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // create GachaSystemInstance
    GachaSystemInstance = CreateDefaultSubobject<UGachaSystem>(TEXT("GachaSystem"));
}

// Called when the game starts or when spawned
void AGachaManagerActor::BeginPlay()
{
    Super::BeginPlay();

    if (GachaSystemInstance)
    {
        GachaSystemInstance->InitializeGacha();
        UE_LOG(LogTemp, Warning, TEXT("GachaSystem initialized in GachaManagerActor."));

        // Called at begin time
        // FGachaItem TestDraw = PerformGacha();

    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("GachaSystemInstance is null!"));
    }
}

// Called every frame
void AGachaManagerActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

FGachaItem AGachaManagerActor::PerformGacha()
{
    if (GachaSystemInstance)
    {
        FGachaItem DrawnItem = GachaSystemInstance->DrawGacha();
        UE_LOG(LogTemp, Warning, TEXT("Drawn Item: %s"), *DrawnItem.ItemName);
        return DrawnItem;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("GachaSystemInstance is null!"));
        return FGachaItem();
    }
}


