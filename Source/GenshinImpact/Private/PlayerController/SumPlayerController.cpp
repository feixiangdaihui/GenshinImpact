// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/SumPlayerController.h"
#include "Hud/BaseHud.h"
#include "Character/PlayCharacter.h"
#include"GameSave/MyGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"



void ASumPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InitializeCharacterMessageAtBeginPlay();

	/*
	ACharacter* PlayerCharacter = Cast<ACharacter>(GetPawn());
	*/
	
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
	if(CheckIsAllCharacterDead())
	{
		GameOver();
		return;
	}
	int NextCharacterIndex = CurrentCharacterIndex;
	while (1)
	{
		NextCharacterIndex = (NextCharacterIndex + 1) % CHARACTERNUM;
		if (!Characters[NextCharacterIndex]->GetIsDead())
		{
			break;
		}
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
		for (auto PlayerCharacter:Characters)
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

void ASumPlayerController::ToggleGachaUI()
{
	if (GachaWidgetInstance == nullptr)
	{
		return;
	}

	if (!bIsGachaUIVisible)
	{
		GachaWidgetInstance->AddToViewport();
		
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(GachaWidgetInstance->TakeWidget());
		SetInputMode(InputMode);
		
		bShowMouseCursor = true;
		bIsGachaUIVisible = true;
	}
	else
	{
		GachaWidgetInstance->RemoveFromViewport();
		
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
		bShowMouseCursor = false;
		
		bIsGachaUIVisible = false;
	}
}

bool ASumPlayerController::CheckIsAllCharacterDead()
{
	for (auto PlayerCharacter : Characters)
	{
		if (!PlayerCharacter->GetIsDead())
		{
			return false;
		}
	}
	return true;
}

void ASumPlayerController::GameOver()
{
	//退出游戏
	SaveCharacterData();
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}

