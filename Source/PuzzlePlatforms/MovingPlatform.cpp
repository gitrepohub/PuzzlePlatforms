// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"



AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority()) return;

	SetReplicates(true);
	SetReplicateMovement(true);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//HasAuthority(); // true means server, false means client
	if (!HasAuthority()) return;

	FVector Location = GetActorLocation();

    FVector GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation_);
	FVector Direction = (GlobalTargetLocation - Location).GetSafeNormal();
	Location += Speed_ * DeltaTime * Direction;

	SetActorLocation(Location);


}