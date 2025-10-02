// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameInstance.h"

#include "Kismet/GameplayStatics.h"

void UBattleBlasterGameInstance::ChangeCurrentLevel(int32 Index)
{
	if (Index > 0 && Index <= LastLevelIndex)
	{
		CurrentLevelIndex = Index;

		FString LevelNameString = FString::Printf(TEXT("Level_%d"), CurrentLevelIndex);
		if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
		{
			UGameplayStatics::OpenLevel(PlayerController, FName(*LevelNameString));
		}
	}
}

void UBattleBlasterGameInstance::LoadNextLevel()
{
	if (CurrentLevelIndex < LastLevelIndex)
	{
		ChangeCurrentLevel(CurrentLevelIndex + 1);
	}
	else
	{
		RestartGame();
	}
}

void UBattleBlasterGameInstance::RestartCurrentLevel()
{
	ChangeCurrentLevel(CurrentLevelIndex);
}

void UBattleBlasterGameInstance::RestartGame()
{
	ChangeCurrentLevel(1);
}
