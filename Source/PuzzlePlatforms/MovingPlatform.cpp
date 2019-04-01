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

	GlobalStartLocation_ = GetActorLocation();
	GlobalTargetLocation_ = GetTransform().TransformPosition(TargetLocation_);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActiveTriggers > 0) {

		//HasAuthority(); // true means server, false means client
		if (!HasAuthority()) return;

		FVector Location = GetActorLocation();

		float JourneyLength = (GlobalTargetLocation_ - GlobalStartLocation_).Size();
		float JourneyTravelled = (Location - GlobalStartLocation_).Size();

		if (JourneyTravelled >= JourneyLength)
		{
			auto swap = GlobalStartLocation_;
			GlobalStartLocation_ = GlobalTargetLocation_;
			GlobalTargetLocation_ = swap;
		}

		FVector Direction = (GlobalTargetLocation_ - GlobalStartLocation_).GetSafeNormal();
		Location += Speed_ * DeltaTime * Direction;
		SetActorLocation(Location);

		//if (FVector::PointsAreNear(Location, GlobalTargetLocation_, 1.0f)) {
		//	auto tGlobalStartLocation_ = GlobalStartLocation_;
		//	GlobalStartLocation_ = GlobalTargetLocation_;
		//  GlobalTargetLocation_ = tGlobalStartLocation_;
		//}
	}

}


void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}


void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0) ActiveTriggers--;
}