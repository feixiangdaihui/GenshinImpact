#include "EnemyComponent/ImmobileMoveComponent.h"

UImmobileMoveComponent::UImmobileMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SpawnLocation = FVector::ZeroVector;
	CurrentSpeed = 0.0f;
	RestTime = 10.0f;
	bIsResting = true;
	bIsIdling = false;
}

void UImmobileMoveComponent::BeginPlay()
{
	UActorComponent::BeginPlay();
	if (AActor* Owner = GetOwner())
		SpawnLocation = Owner->GetActorLocation();
}

void UImmobileMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	UActorComponent::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GetWorld()->GetTimerManager().SetTimer(
		RestTimerHandle,
		this,
		&UImmobileMoveComponent::RenewState,
		RestTime,
		false);
}

void UImmobileMoveComponent::RenewState()
{
	bIsResting = !bIsResting;
	bIsIdling = !bIsIdling;
}