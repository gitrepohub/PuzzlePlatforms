// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "PlatformTrigger.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance"));
	ConstructorHelpers::FClassFinder<UUserWidget> WBPMainMenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(WBPMainMenuBPClass.Class != nullptr)) return;


	MenuClass = WBPMainMenuBPClass.Class;

}

void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Init"));

	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName());

}


void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;

	auto menu = CreateWidget<UUserWidget>(this, MenuClass);
	if (!ensure(menu != nullptr)) return;

	menu->bIsFocusable = true;
	menu->AddToViewport();

	auto PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->bShowMouseCursor = true;

	//FInputModeUIOnly InputMode;
	//InputMode.SetWidgetToFocus(menu->TakeWidget());
	//InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	menu->SetUserFocus(PlayerController);


}


void UPuzzlePlatformsGameInstance::Host()
{
	auto engine = GetEngine();

	if (!ensure(engine != nullptr)) return;

	// http://api.unrealengine.com/INT/API/Runtime/Engine/Engine/UEngine/AddOnScreenDebugMessage/2/index.html
	engine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, TEXT("Hosting"));

	auto World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen"); //?listen

}

void UPuzzlePlatformsGameInstance::Join(const FString & address)
{
	auto engine = GetEngine();

	if (!ensure(engine != nullptr)) return;

	// http://api.unrealengine.com/INT/API/Runtime/Engine/Engine/UEngine/AddOnScreenDebugMessage/2/index.html
	engine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, FString::Printf(TEXT("Address is %s"), *address));

	auto PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(address, ETravelType::TRAVEL_Absolute);

}

