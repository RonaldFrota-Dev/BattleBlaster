// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.h"
#include "EnemyTower.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API AEnemyTower : public ABasePawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float FireRange = 500.0f;

	UPROPERTY(EditAnywhere)
	float FireCooldown = 2.0f;

	ATank* Tank;

	void CheckFireCondition();
	bool IsInFireRange();
};
