// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"


bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success) return false;

	if (!ensure(HostButton != nullptr)) return false;
	if (!ensure(JoinButton != nullptr)) return false;
	if (!ensure(BackButton != nullptr)) return false;


	// Main Menu buttons
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	// Join Menu buttons
	BackButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	PlayButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);


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


void UMainMenu::JoinServer()
{
	UE_LOG(LogTemp, Warning, TEXT("JoinServer called"));
	if (!ensure(IPAddressField != nullptr)) return;
	if (MenuInterface == nullptr) return;

	// TextWidget 
	auto ipaddress = IPAddressField->GetText().ToString();
	if (ipaddress == "" || ipaddress.Len() < 7) return;

	MenuInterface->Join(ipaddress);

}


void UMainMenu::OpenJoinMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("OpenJoinMenu called"));

	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(JoinMenu);

}


void UMainMenu::OpenMainMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("OpenMainMenu called"));

	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(MainMenu);

}