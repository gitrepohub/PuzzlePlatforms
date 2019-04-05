// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"


bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success) return false;

	if (!ensure(HostButton != nullptr)) return false;
	if (!ensure(JoinButton != nullptr)) return false;

	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	return true;
}


void UMainMenu::SetMenuInterface(IMenuInterface* NewMenuInterface)
{
	this->MenuInterface = NewMenuInterface;
}


void UMainMenu::Setup()
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


void UMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
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


void UMainMenu::HostServer()
{
	UE_LOG(LogTemp, Warning, TEXT("HostServer called"));
	
	if (MenuInterface == nullptr) return;

	MenuInterface->Host();

}


void UMainMenu::OpenJoinMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("JoinServer called"));

	if (!ensure(MenuSwitcher != nullptr)) return;

	MenuSwitcher->SetActiveWidget(nullptr);

}