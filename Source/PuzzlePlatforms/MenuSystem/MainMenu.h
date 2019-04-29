// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"

#include "MainMenu.generated.h"

USTRUCT()
struct FServerData
{
	GENERATED_BODY()

	FString Name;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	FString HostUsername;
};

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

public:
	UMainMenu(const FObjectInitializer& ObjectInitializer);

	void SetServerList(TArray<FServerData>& ServerNames);

	void SelectIndex(uint32 Index);

protected:
	virtual bool Initialize() override;

private:

	void UpdateChildren();

	TSubclassOf<class UUserWidget> ServerRowClass = nullptr;
	TOptional<uint32> SelectedIndex;


	// Main Menu Buttons
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton = nullptr;


	// Join Menu Buttons
	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* PlayButton = nullptr;


	// Host Menu Buttons
	UPROPERTY(meta = (BindWidget))
	class UButton* SBackButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* SHostButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* HostName = nullptr;


	// Menu Switchers
	// Holds menus listed below
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher = nullptr;

	// Scroller Widget apart of the Join Menu
	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* ServerList = nullptr;

	/*
	// Menus
	//      MainMenu 
	//      /       \
	//    JoinMenu   HostMenu
	*/
	UPROPERTY(meta = (BindWidget))
    class UWidget* MainMenu = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UWidget* HostMenu = nullptr;


	// Callback functions
	// Main Menu
	UFUNCTION()
	void OpenHostMenu();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void QuitGame();

	// Join + Host (Back Button)
	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void JoinServer();

	// Host
	UFUNCTION()
	void HostServer();



};
