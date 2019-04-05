// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MenuInterface.h"

#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMenuInterface(IMenuInterface* NewMenuInterface);
	void Setup();


protected:
	virtual bool Initialize() override;
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu = nullptr;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenJoinMenu();

	IMenuInterface* MenuInterface = nullptr;

};
