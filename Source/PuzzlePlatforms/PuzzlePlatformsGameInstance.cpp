// Fill out your copyright notice in the Description page of ProjeMy Sct Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuWidget.h"

const static FName SESSION_NAME = TEXT("My Session Game");


UPuzzlePlatformsGameInstance::~UPuzzlePlatformsGameInstance()
{
	UE_LOG(LogTemp, Warning, TEXT("destroy"));

}


UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance"));
	ConstructorHelpers::FClassFinder<UUserWidget> WBPMainMenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(WBPMainMenuBPClass.Class != nullptr)) return;

	MenuClass = WBPMainMenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> WBPInGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_GameMenuSystem"));
	if (!ensure(WBPInGameMenuBPClass.Class != nullptr)) return;

	InGameMenuClass = WBPInGameMenuBPClass.Class;

}

void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Init"));

	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName());

	auto subsystem = IOnlineSubsystem::Get();

	if (subsystem == nullptr) { UE_LOG(LogTemp, Warning, TEXT("subsystem is NULL")); return; }

	UE_LOG(LogTemp, Warning, TEXT("SubSystem Type %s"), *subsystem->GetSubsystemName().ToString());

	SessionInterface = subsystem->GetSessionInterface();

	if (!SessionInterface.IsValid()) return;

	UE_LOG(LogTemp, Warning, TEXT("Found Interface "));

	// clear up old delegates
	SessionInterface->OnCreateSessionCompleteDelegates.Clear();
	SessionInterface->OnDestroySessionCompleteDelegates.Clear();
	SessionInterface->OnFindSessionsCompleteDelegates.Clear();
	SessionInterface->OnJoinSessionCompleteDelegates.Clear();


	FDelegateHandle res = SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnCreateSessionComplete);
	if (!res.IsValid()) { UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionCompleteDelegates FDelegateHandle not valid")); return; }

	res = SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnDestroySessionComplete);
	if (!res.IsValid()) { UE_LOG(LogTemp, Warning, TEXT("OnDestroySessionCompleteDelegates FDelegateHandle not valid")); return; }

	res = SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnFindSessionsComplete);
	if (!res.IsValid()) { UE_LOG(LogTemp, Warning, TEXT("OnFindSessionsCompleteDelegates FDelegateHandle not valid")); return; }

	res = SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnJoinSessionComplete);
	if (!res.IsValid()) { UE_LOG(LogTemp, Warning, TEXT("OnJoinSessionComplete FDelegateHandle not valid")); return; }


	SessionSearch = MakeShareable(new FOnlineSessionSearch());

}

void UPuzzlePlatformsGameInstance::RefreshServerList()
{
	if (SessionSearch.IsValid()) {
		EOnlineAsyncTaskState::Type state = SessionSearch->SearchState;
		if (state == EOnlineAsyncTaskState::InProgress) {
			UE_LOG(LogTemp, Warning, TEXT("Already InProgress"));
			return;
		}

		UE_LOG(LogTemp, Warning, TEXT("Starting Find Session"));
		//SessionSearch->bIsLanQuery = true;
		SessionSearch->MaxSearchResults = 100;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}


void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;

	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(Menu != nullptr)) return;

	Menu->Setup();
	Menu->SetMenuInterface(this);


}

void UPuzzlePlatformsGameInstance::InGameLoadMenu()
{
	if (!ensure(InGameMenuClass != nullptr)) return;

	auto menu = CreateWidget<UMenuWidget>(this, InGameMenuClass);
	if (!ensure(menu != nullptr)) return;

	menu->Setup();
	menu->SetMenuInterface(this);


}

void UPuzzlePlatformsGameInstance::CreateSession()
{
	UE_LOG(LogTemp, Warning, TEXT("CreateSession"));

	if (!SessionInterface.IsValid()) { UE_LOG(LogTemp, Warning, TEXT("session not valid")); return; }

	FOnlineSessionSettings SessionSettings;
	SessionSettings.bIsLANMatch = false; // true;
	SessionSettings.NumPublicConnections = 2;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUsesPresence = true;

	auto bres = SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);

	if (!bres) { UE_LOG(LogTemp, Warning, TEXT("Could not create session")); return; }
}


void UPuzzlePlatformsGameInstance::Host()
{
	UE_LOG(LogTemp, Warning, TEXT("Host"));

	if (!SessionInterface.IsValid()) { UE_LOG(LogTemp, Warning, TEXT("session not valid")); return; }

	auto session = SessionInterface->GetNamedSession(SESSION_NAME);
	if (session != nullptr) {
		// remove the current session and create a new session on callback
		SessionInterface->DestroySession(SESSION_NAME);
	} else {
		CreateSession();
	}
}


void UPuzzlePlatformsGameInstance::OnFindSessionsComplete(bool res)
{
	UE_LOG(LogTemp, Warning, TEXT("OnFindSessionsComplete"));
	if (!res) { UE_LOG(LogTemp, Warning, TEXT("OnFindSessionsComplete failed")); return; };

	if (!SessionSearch.IsValid()) { UE_LOG(LogTemp, Warning, TEXT("SessionSearch not valid")); return; }

	UE_LOG(LogTemp, Warning, TEXT("Numer of Sessions Found: %i"), SessionSearch->MaxSearchResults);
	
	for (const auto& result : SessionSearch->SearchResults) {
		UE_LOG(LogTemp, Warning, TEXT("Found: %s"), *result.GetSessionIdStr());
	}

	if (Menu == nullptr) return;

	Menu->SetServerList(SessionSearch->SearchResults);

}


void UPuzzlePlatformsGameInstance::OnCreateSessionComplete(FName name, bool res)
{
	UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete"));
	if (!res) { UE_LOG(LogTemp, Warning, TEXT("Could not create session")); return; };

	auto engine = GetEngine();

	if (!ensure(engine != nullptr)) return;

	// http://api.unrealengine.com/INT/API/Runtime/Engine/Engine/UEngine/AddOnScreenDebugMessage/2/index.html
	engine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, TEXT("Hosting"));

	auto World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen"); //?listen

}


void UPuzzlePlatformsGameInstance::OnDestroySessionComplete(FName name, bool res)
{
	UE_LOG(LogTemp, Warning, TEXT("OnDestroySessionComplete"));
	if (!res) { UE_LOG(LogTemp, Warning, TEXT("Could not destroy session")); return; };
	CreateSession();
}


void UPuzzlePlatformsGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogTemp, Warning, TEXT("OnJoinSessionComplete"));

	if (Result != EOnJoinSessionCompleteResult::Success) { 
		UE_LOG(LogTemp, Warning, TEXT("Result is not success"));
		return;
	}

	if (!SessionInterface.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("SessionInterface is not valid"));

		return;
	}

	FString ConnectInfo = "";

	bool bResult = SessionInterface->GetResolvedConnectString(SessionName, ConnectInfo);
	if (!bResult) {
		UE_LOG(LogTemp, Warning, TEXT("GetResolvedConnectString failed"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("GetResolvedConnectString got %s"), *ConnectInfo);


	auto engine = GetEngine();

	if (!ensure(engine != nullptr)) return;

	engine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, FString::Printf(TEXT("Address is %s"), *ConnectInfo));

	auto PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(ConnectInfo, ETravelType::TRAVEL_Absolute);
}


void UPuzzlePlatformsGameInstance::Join(const uint32& index)
{
	UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance Join called with %i"), index);

	if (!SessionInterface.IsValid()) return;
	if (!SessionSearch.IsValid()) return;

	bool bResult = SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[index]);
}


void UPuzzlePlatformsGameInstance::OpenMainMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance OpenMainMenu called"));

	auto PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/MenuSystem/MainMenuLevel_BP", ETravelType::TRAVEL_Absolute);
}


void UPuzzlePlatformsGameInstance::QuitGame()
{
	UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance QuitGame called"));

	auto PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}