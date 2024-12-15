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
	Hud = Cast<ABaseHud>(GetHUD());


}

void ASumPlayerController::InitializeCharacterMessageAtBeginPlay()
{
	APlayCharacter* FirstCharacter = Cast<APlayCharacter>(GetPawn());
	Characters.Add(FirstCharacter);
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
		}
	}

}

void ASumPlayerController::ChangeCharacter(int CharacterIndex)
{
	if (Characters.IsValidIndex(CharacterIndex))
	{
		//获取当前角色位置，控制现在的角色转移到这个位置
		FVector CurrentCharacterLocation = Characters[CurrentCharacterIndex]->GetActorLocation();
		FRotator CurrentCharacterRotation = Characters[CurrentCharacterIndex]->GetActorRotation();
		Characters[CharacterIndex]->SetActorLocationAndRotation(CurrentCharacterLocation, CurrentCharacterRotation);
		//隐藏当前角色
		SetCharacterVisibility(CurrentCharacterIndex, false);
		SetCharacterVisibility(CharacterIndex, true);
		CurrentCharacterIndex = CharacterIndex;

		OnPossess(Characters[CharacterIndex]);


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





