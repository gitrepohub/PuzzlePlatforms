// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"

#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

public:
	UMainMenu(const FObjectInitializer& ObjectInitializer);

	void SetServerList(TArray<FOnlineSessionSearchResult>& ServerNames);

	void SelectIndex(uint32 Index);

protected:
	virtual bool Initialize() override;

private:

	TSubclassOf<class UUserWidget> ServerRowClass = nullptr;
	TOptional<uint32> SelectedIndex;


	// Menu Buttons
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* PlayButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton = nullptr;

	// Scroller Widget
	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* ServerList = nullptr;

	// Menu Switchers
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher = nullptr;

	// Menus
	UPROPERTY(meta = (BindWidget))
    class UWidget* MainMenu = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu = nullptr;


	// Callback functions
	// Main Menu
	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void QuitGame();

	// Join
	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void JoinServer();

};
