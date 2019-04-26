// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/TextBlock.h"
#include "OnlineSessionSettings.h"

#include "ServerRow.h"


UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("UMainMenu"));
	ConstructorHelpers::FClassFinder<UUserWidget> WBPServerRowBPClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if (!ensure(WBPServerRowBPClass.Class != nullptr)) return;

	ServerRowClass = WBPServerRowBPClass.Class;
}


bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success) return false;

	// Main Menu Buttons
	if (!ensure(HostButton != nullptr)) return false;
	if (!ensure(JoinButton != nullptr)) return false;
	if (!ensure(QuitButton != nullptr)) return false;

	// Join Menu Buttons
	if (!ensure(BackButton != nullptr)) return false;
	if (!ensure(PlayButton != nullptr)) return false;

	// Main Menu buttons
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);


	// Join Menu buttons
	BackButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	PlayButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);


	return true;
}


void UMainMenu::HostServer()
{
	UE_LOG(LogTemp, Warning, TEXT("HostServer called"));
	
	if (MenuInterface == nullptr) return;

	MenuInterface->Host();

}

void UMainMenu::QuitGame()
{
	UE_LOG(LogTemp, Warning, TEXT("QuitGame called"));

	if (MenuInterface == nullptr) return;

	MenuInterface->QuitGame();

}


void UMainMenu::JoinServer()
{
	UE_LOG(LogTemp, Warning, TEXT("JoinServer called"));

	if (SelectedIndex.IsSet())
	{
		UE_LOG(LogTemp, Warning, TEXT("SelectedIndex: %d"), SelectedIndex.GetValue());

	} else {
		UE_LOG(LogTemp, Warning, TEXT("SelectedIndex Not Set"));
		return;
	}
	if (!ensure(ServerList != nullptr)) return;
	if (MenuInterface == nullptr) return;

	// TextWidget 
	//const FString& ipaddress = IPAddressField->GetText().ToString();
	//if (ipaddress == "" || ipaddress.Len() < 7) return;
	//MenuInterface->Join(ipaddress);

	MenuInterface->Join(SelectedIndex.GetValue());
}


void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
}


void UMainMenu::SetServerList(TArray<FOnlineSessionSearchResult>& ServerNames)
{

	if (!ensure(ServerRowClass != nullptr)) return;
	if (!ensure(ServerList != nullptr)) return;
	ServerList->ClearChildren();

	uint32 i = 0;
	for (const FOnlineSessionSearchResult& ServerName : ServerNames)
	{
		
		auto ServerRow = CreateWidget<UServerRow>(this, ServerRowClass);
		if (!ensure(ServerRow != nullptr)) return;
		if (!ensure(ServerRow->ServerName != nullptr)) return;
		

		ServerRow->ServerName->SetText(FText::FromString(ServerName.GetSessionIdStr()));
		ServerRow->Setup(this, i);
		++i;
		ServerList->AddChild(ServerRow);
	}
}



void UMainMenu::OpenJoinMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("OpenJoinMenu called"));

	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(JoinMenu);

	if (MenuInterface == nullptr) return;
	MenuInterface->RefreshServerList();

}


void UMainMenu::OpenMainMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("OpenMainMenu called"));

	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(MainMenu);

}