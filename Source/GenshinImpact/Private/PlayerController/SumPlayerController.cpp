// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/SumPlayerController.h"
#include "Hud/BaseHud.h"
#include "Character/PlayCharacter.h"
#include"GameSave/MyGameInstance.h"


void ASumPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InitializeCharacterMessageAtBeginPlay();
	LoadCharacterData();


	ACharacter* PlayerCharacter = Cast<ACharacter>(GetPawn());
	if (PlayerCharacter)
	{
		UCPP_InventoryComponent* FoundInventoryComponent = PlayerCharacter->FindComponentByClass<UCPP_InventoryComponent>();
		if (FoundInventoryComponent)
		{
			InventoryComponent = FoundInventoryComponent;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("InventoryComponent not found on PlayerCharacter."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerPawn is not a valid ACharacter."));
	}
}


void ASumPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector CurrentCharacterLocation = Characters[CurrentCharacterIndex]->GetActorLocation();
	FRotator CurrentCharacterRotation = Characters[CurrentCharacterIndex]->GetActorRotation();
	for (int Index = 0;Index < CHARACTERNUM;Index++)
	{
		if (Index != CurrentCharacterIndex)
			Characters[Index]->SetActorLocationAndRotation(CurrentCharacterLocation, CurrentCharacterRotation);

	}
		
	
}

void ASumPlayerController::InitializeCharacterMessageAtBeginPlay()
{
	APlayCharacter* FirstCharacter = Cast<APlayCharacter>(GetPawn());
	Characters.Add(FirstCharacter);
	FirstCharacter->SetCharacterIndex(0);
	CurrentCharacterIndex = 0;
	FVector CurrentCharacterLocation = FirstCharacter->GetActorLocation();
	FRotator CurrentCharacterRotation = FirstCharacter->GetActorRotation();
	for (int i = 1; i < CharacterClasses.Num(); i++)
	{
		if (CharacterClasses[i])
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;
			APlayCharacter* NewCharacter = GetWorld()->SpawnActor<APlayCharacter>(CharacterClasses[i], CurrentCharacterLocation, CurrentCharacterRotation, SpawnParameters);
			Characters.Add(NewCharacter);
			SetCharacterVisibility(i, false);
			NewCharacter->SetCharacterIndex(i);
		}
	}
	LoadCharacterData();

}

void ASumPlayerController::ChangeCharacter(int CharacterIndex)
{
	if (Characters.IsValidIndex(CharacterIndex))
	{

		//隐藏当前角色
		SetCharacterVisibility(CurrentCharacterIndex, false);
		SetCharacterVisibility(CharacterIndex, true);
		
		CurrentCharacterIndex = CharacterIndex;

		OnPossess(Characters[CharacterIndex]);
		ABaseHud* BaseHud = Cast<ABaseHud>(GetHUD());
		if (BaseHud)
		{
			BaseHud->ChangeCharacterUI();
		}
	}

}

void ASumPlayerController::SetCharacterVisibility(int32 CharacterIndex, bool bVisible)
{
	if (Characters.IsValidIndex(CharacterIndex))
	{
		Characters[CharacterIndex]->SetActorHiddenInGame(!bVisible);
		Characters[CharacterIndex]->SetActorEnableCollision(bVisible);
		Characters[CharacterIndex]->SetActorTickEnabled(bVisible);
	}
}

void ASumPlayerController::SeqChangeCharacter()
{
	int NextCharacterIndex = CurrentCharacterIndex + 1;
	if (NextCharacterIndex >= Characters.Num())
	{
		NextCharacterIndex = 0;
	}
	ChangeCharacter(NextCharacterIndex);

}

void ASumPlayerController::SaveCharacterData()
{
	for (auto PlayerCharacter : Characters)
	{
		FCharacterData CharacterData = PlayerCharacter->SaveCharacterData();
		UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
		if (GameInstance)
		{
			GameInstance->SaveCharacterData(PlayerCharacter->GetName(), CharacterData);
		}
	}
}

void ASumPlayerController::LoadCharacterData()
{
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		for (auto PlayerCharacter : Characters)
		{
			FCharacterData CharacterData;
			if (GameInstance->GetCharacterData(PlayerCharacter->GetName(), CharacterData))
			{
				PlayerCharacter->LoadCharacterData(CharacterData);
			}
		}
	}
}

void ASumPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	SaveCharacterData();
}

void ASumPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// 绑定 ToggleInventoryAction 到 ToggleInventoryWidget
		EnhancedInputComponent->BindAction(ToggleInventoryAction, ETriggerEvent::Triggered, this, &ASumPlayerController::ToggleInventory);
	}
}


void ASumPlayerController::ToggleInventory()
{
	if (InventoryComponent)
	{
		// 使用反射调用蓝图函数
		FName FunctionName = FName("ToggleInventoryWidget");
		UFunction* Function = InventoryComponent->FindFunction(FunctionName);
		if (Function)
		{
			InventoryComponent->ProcessEvent(Function, nullptr);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Function %s not found in InventoryComponent."), *FunctionName.ToString());
		}
	}
}

