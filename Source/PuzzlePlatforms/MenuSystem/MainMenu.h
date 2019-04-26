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

protected:
	virtual bool Initialize() override;

private:
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

	// IP Address Text Widget
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* IPAddressField = nullptr;

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
