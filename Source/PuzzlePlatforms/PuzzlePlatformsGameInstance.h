// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"

#include "MenuSystem/MenuInterface.h"

#include "PuzzlePlatformsGameInstance.generated.h"
/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer);
	~UPuzzlePlatformsGameInstance();

	virtual void Init();

	UFUNCTION(BlueprintCallable)
	void LoadMenu();


	UFUNCTION(BlueprintCallable)
	void InGameLoadMenu();

	UFUNCTION(Exec)
	virtual void Host() override;

	UFUNCTION(Exec)
	virtual void Join(const FString &address) override;

	virtual void OpenMainMenu() override;
	virtual void QuitGame() override;


private:
	TSubclassOf<class UUserWidget> MenuClass = nullptr;
	TSubclassOf<class UUserWidget> InGameMenuClass = nullptr;
	IOnlineSessionPtr SessionInterface = nullptr;
	class UMainMenu* Menu = nullptr;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	void CreateSession();

	void OnCreateSessionComplete(FName name, bool res);
	void OnDestroySessionComplete(FName name, bool res);
	void OnFindSessionsComplete(bool res);
};
