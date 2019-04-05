// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success) return false;

	if (!ensure(Host != nullptr)) return false;
	if (!ensure(Join != nullptr)) return false;

	Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	Join->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	return true;
}


void UMainMenu::HostServer()
{
	UE_LOG(LogTemp, Warning, TEXT("HostServer called"));
}


void UMainMenu::JoinServer()
{
	UE_LOG(LogTemp, Warning, TEXT("JoinServer called"));
}