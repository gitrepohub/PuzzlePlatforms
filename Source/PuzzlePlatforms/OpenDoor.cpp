// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"

#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("UOpenDoor"));

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	auto actor = GetOwner();

	if (actor == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("actor is null"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("UOpenDoor Reporter reporting for duty on %s"), *actor->GetName());
	if (!actor->HasAuthority()) return;

	actor->SetReplicates(true);
	actor->SetReplicateMovement(true);
	
}


void UOpenDoor::CloseDoor()
{
	// Find the owning Actor
	AActor* Owner = GetOwner();
	if (Owner == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Owner is null"));
		return;
	}


	// Create a rotator
	FRotator NewRotation = FRotator(0.f, 0.f, 0.f);

	// Set the door rotation
	Owner->SetActorRotation(NewRotation);

}


void UOpenDoor::OpenDoor()
{
	// Find the owning Actor
	AActor* Owner = GetOwner();
	if (Owner == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Owner is null"));
		return;
	}


	// Create a rotator
	FRotator NewRotation = FRotator(0.f, -90.f, 0.f);

	// Set the door rotation
	Owner->SetActorRotation(NewRotation);

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto actor = GetOwner();

	if (actor == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("actor is null"));
		return;
	}

	if (!actor->HasAuthority()) return;

	if (ActiveTriggers > 0) {
		OpenDoor();
	} else {
		CloseDoor();
    }

	// Poll the Trigger Volume
// If the ActorThatOpens is in the volume
	/*
	auto person = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (person == nullptr) UE_LOG(LogTemp, Warning, TEXT("person is null"));

	if (PressurePlate->IsOverlappingActor(person))
	{
		OpenDoor();
	}
	*/
}


void UOpenDoor::AddActiveTrigger()
{
	ActiveTriggers++;

}


void UOpenDoor::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0) ActiveTriggers--;

}