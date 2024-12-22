// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Equipment/Equipment.h"
#include "Widget/EquipmentWidget.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
// Sets default values
AEquipment::AEquipment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetVisibility(true);
	RootComponent = MeshComponent;
	//设置碰撞类型为Overlap
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//设置网格体大小
	MeshComponent->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(NeedToShowDistance);
	//设置碰撞类型为Overlap
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	PickupText = FString(TEXT("Press G to pick up"));

	EquipmentWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("EquipmentWidget"));
	EquipmentWidgetComponent->SetupAttachment(RootComponent);
	EquipmentWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	EquipmentWidgetComponent->SetDrawAtDesiredSize(true);

}

// Called when the game starts or when spawned
void AEquipment::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->SetSphereRadius(NeedToShowDistance);
	if (EquipmentWidgetComponent)
	{
		EquipmentWidgetComponent->InitWidget();
		EquipmentWidget = Cast<UEquipmentWidget>(EquipmentWidgetComponent->GetUserWidgetObject());
		if (EquipmentWidget)
		{
			EquipmentWidget->SetVisibility(ESlateVisibility::Visible);
			EquipmentWidget->SetTipsText(FText::FromString(PickupText));
		}
	}
	
}

// Called every frame
void AEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//如果离玩家很近，显示按键提示
	if (EquipmentWidget)
	{
		//FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		//if (FVector::Distance(PlayerLocation, GetActorLocation()) < NeedToShowDistance)
		//{
		//	SetVisibility(true);
		//	//转向文本面对玩家
		//	//FVector LookAt = PlayerLocation - GetActorLocation();
		//	//EquipmentWidget->SetTextRotation(LookAt);
		//}
		//else
		//{
		//	SetVisibility(false);
		//}
	}
	
}

void AEquipment::SetEquipmentType(EEquipmentType WantType)
{
	EquipmentType = WantType;
}

void AEquipment::SetIsHiden(bool IsHiden)
{
	SetActorHiddenInGame(IsHiden);
	SetActorEnableCollision(!IsHiden);
}

void AEquipment::InitializeData()
{
	MeshComponent->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
}





