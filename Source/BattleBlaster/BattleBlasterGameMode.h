// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Tank.h"
#include "ScreenMessage.h"
#include "BattleBlasterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ABattleBlasterGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UScreenMessage> ScreenMessageClass;

	UPROPERTY()
	UScreenMessage* ScreenMessageWidget;
	
	UPROPERTY(EditAnywhere)
	float GameOverDelay = 4.0f;

	UPROPERTY(EditAnywhere)
	int32 CountdownDelay = 4;

	int32 CountdownSeconds;
	FTimerHandle CountdownTimerHandle;

	bool isWin = false;
	
	ATank* Tank;
	int32 TowerCount;

	void ActorDied(AActor* DeadActor);

	void GameOverTimerTimeout();
	void OnCountdownTimerTimeout();
};
