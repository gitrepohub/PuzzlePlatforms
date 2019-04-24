// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

void UMenuWidget::SetMenuInterface(IMenuInterface* NewMenuInterface)
{
	this->MenuInterface = NewMenuInterface;
}


void UMenuWidget::Setup()
{
	auto World = GetWorld();

	if (!ensure(World != nullptr)) return;

	this->bIsFocusable = true;
	this->AddToViewport();

	auto PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->bShowMouseCursor = true;

	//FInputModeUIOnly InputMode;
	//InputMode.SetWidgetToFocus(this->TakeWidget());
	//InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	this->SetUserFocus(PlayerController);
}


void UMenuWidget::Teardown()
{
	this->RemoveFromViewport();

	UWorld* World = GetWorld();

	if (!ensure(World != nullptr)) return;

	APlayerController * PlayerController = World->GetFirstPlayerController();

	if (!ensure(PlayerController != nullptr)) return;

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;

}


void UMenuWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	UE_LOG(LogTemp, Warning, TEXT("OnLevelRemovedFromWorld called"));

	this->RemoveFromViewport();

	if (InWorld) {
		auto PlayerController = InWorld->GetFirstPlayerController();
		if (!ensure(PlayerController != nullptr)) return;

		FInputModeGameOnly inputMode;
		PlayerController->SetInputMode(inputMode);
		PlayerController->bShowMouseCursor = false;
	}

	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

}