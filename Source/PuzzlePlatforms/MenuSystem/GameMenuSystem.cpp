// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMenuSystem.h"

#include "Components/Button.h"


bool UGameMenuSystem::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success) return false;

	if (!ensure(CancelButton != nullptr)) return false;
	if (!ensure(MainMenuButton != nullptr)) return false;


	// buttons
	CancelButton->OnClicked.AddDynamic(this, &UGameMenuSystem::CancelGameMenu);
	MainMenuButton->OnClicked.AddDynamic(this, &UGameMenuSystem::OpenMainMenu);

	return true;
}

void UGameMenuSystem::OpenMainMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("OpenMainMenu called"));

	if (MenuInterface == nullptr) return;
	Teardown();

	MenuInterface->OpenMainMenu();

}


void UGameMenuSystem::CancelGameMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("CancelGameMenu called"));

	Teardown();

}