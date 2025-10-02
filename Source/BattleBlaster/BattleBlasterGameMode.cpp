// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyTower.h"
#include "BattleBlasterGameInstance.h"

void ABattleBlasterGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyTower::StaticClass(), Towers);
	TowerCount = Towers.Num();
	UE_LOG(LogTemp, Log, TEXT("TowerCount: %d"), TowerCount);
	
	if (APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		Tank = Cast<ATank>(PlayerPawn);
		if (!Tank)
		{
			UE_LOG(LogTemp, Error, TEXT("No Tank found!"));
		}
	}

	int32 LoopIndex = 0;
	while (LoopIndex < TowerCount)
	{
		AActor* TowerActor = Towers[LoopIndex];
		if (TowerActor)
		{
			AEnemyTower* Tower = Cast<AEnemyTower>(TowerActor);
			if (Tower && Tank)
			{
				Tower->Tank = Tank;
				UE_LOG(LogTemp, Display, TEXT("%s setting the Tank variable"), *Tower->GetName());
			}
		}
		
		LoopIndex++;
	}
}

void ABattleBlasterGameMode::ActorDied(AActor* DeadActor)
{
	bool isGameOver = false;
	
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		isGameOver = true;
	}
	else
	{
		AEnemyTower* DeadTower = Cast<AEnemyTower>(DeadActor);
		if (DeadTower)
		{
			DeadTower->HandleDestruction();
			
			TowerCount--;
			if (TowerCount == 0)
			{
				UE_LOG(LogTemp, Display, TEXT("Victory"));
				isGameOver = true;
				isWin = true;
			}
		}
	}

	if (isGameOver)
	{
		FString GameOverString = isWin ? "You Win!" : "You Lose!";
		UE_LOG(LogTemp, Display, TEXT("%s"), *GameOverString);

		FTimerHandle GameOverTimerHandle;
		GetWorldTimerManager().SetTimer(GameOverTimerHandle, this, &ABattleBlasterGameMode::GameOverTimerTimeout, GameOverDelay, false);
	}
}

void ABattleBlasterGameMode::GameOverTimerTimeout()
{
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		UBattleBlasterGameInstance* BattleBlasterGameInstance = Cast<UBattleBlasterGameInstance>(GameInstance);
		if (BattleBlasterGameInstance)
		{
			if (isWin)
			{
				BattleBlasterGameInstance->LoadNextLevel();
			}
			else
			{
				BattleBlasterGameInstance->RestartCurrentLevel();
			}
		}
	}
}
