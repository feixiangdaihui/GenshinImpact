#include "EnemyComponent/ImmobileMoveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UImmobileMoveComponent::UImmobileMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SpawnLocation = FVector::ZeroVector;
	CurrentSpeed = 0.0f;
	RestTime = 10.0f;
	TurnRate = 5.0f;
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

void UImmobileMoveComponent::TurnTo(const FVector& Direction, float DeltaTime)
{
	if (AActor* Owner = GetOwner())
	{
		FRotator CurrentRotation = Owner->GetActorRotation();
		FRotator TargetRotation = Direction.Rotation();
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, TurnRate);
		Owner->SetActorRotation(NewRotation);
	}
}

void UImmobileMoveComponent::ChasePlayer()
{
	bIsResting = false;
	bIsIdling = false;
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	TurnTo(Player->GetActorLocation(), 0.05f);
	//
}

void UImmobileMoveComponent::RenewState()
{
	bIsResting = !bIsResting;
	bIsIdling = !bIsIdling;
}