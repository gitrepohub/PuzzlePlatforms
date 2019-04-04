// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformTrigger.h"
#include "Components/BoxComponent.h"

#include "MovingPlatform.h"
#include "OpenDoor.h"

// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));

	if (!ensure(TriggerVolume != nullptr)) return;

	RootComponent = TriggerVolume;

}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(TriggerVolume != nullptr)) return;

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapEnd);

}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void APlatformTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (auto MovingPlatforms : PlatformsToTrigger)
	{
		if (!ensure(MovingPlatforms != nullptr)) return;
		MovingPlatforms->AddActiveTrigger();
	}

	for (auto OpenDoor : DoorsToTrigger)
	{
		if (!ensure(OpenDoor != nullptr)) return;

		auto thedoor = OpenDoor->FindComponentByClass<UOpenDoor>();

		thedoor->AddActiveTrigger();
	}
}


void APlatformTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	for (auto MovingPlatform : PlatformsToTrigger)
	{
		if (!ensure(MovingPlatform != nullptr)) return;
		MovingPlatform->RemoveActiveTrigger();
	}

	for (auto OpenDoor : DoorsToTrigger)
	{
		if (!ensure(OpenDoor != nullptr)) return;
		auto thedoor = OpenDoor->FindComponentByClass<UOpenDoor>();

		thedoor->RemoveActiveTrigger();
	}
}