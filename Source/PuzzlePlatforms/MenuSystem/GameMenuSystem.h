// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"

#include "MenuInterface.h"

#include "GameMenuSystem.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UGameMenuSystem : public UMenuWidget
{
	GENERATED_BODY()


protected:
	virtual bool Initialize() override;

private:
	// Menu Buttons
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuButton = nullptr;

	// Callback functions
	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void CancelGameMenu();
	
};
