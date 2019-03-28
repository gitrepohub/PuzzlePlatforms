// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"



AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//HasAuthority(); // true means server, false means client
	if (!HasAuthority()) return;

	FVector Location = GetActorLocation();
	Location += FVector(Speed_ * DeltaTime, 0, 0);

	SetActorLocation(Location);


}