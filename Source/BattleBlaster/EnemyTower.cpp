// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTower.h"
#include "Kismet/GameplayStatics.h"

void AEnemyTower::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle FireTimer;
	GetWorldTimerManager().SetTimer(FireTimer, this, &AEnemyTower::CheckFireCondition, FireCooldown, true);
}

void AEnemyTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (IsInFireRange()) { RotateTurret(Tank->GetActorLocation()); }
}

void AEnemyTower::CheckFireCondition()
{
	if (Tank && IsInFireRange() && Tank->IsAlive)
	{
		Fire();
	}
}

bool AEnemyTower::IsInFireRange()
{
	bool bIsInFireRange = false;
	if (Tank && FVector::Dist(GetActorLocation(), Tank->GetActorLocation()) <= FireRange)
	{
		bIsInFireRange = true;
	}
	
	return bIsInFireRange;
}

void AEnemyTower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}
