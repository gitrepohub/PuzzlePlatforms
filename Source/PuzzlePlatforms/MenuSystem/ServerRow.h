// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UServerRow : public UUserWidget
{
	GENERATED_BODY()

public:
	void Setup(class UMainMenu* InParent, uint32& InIndex);

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HostUser = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ConnectionFraction = nullptr;

	UPROPERTY(BlueprintReadOnly)
	bool Selected = false;

protected:
	virtual bool Initialize() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* ServerButton = nullptr;

	UFUNCTION()
	void OnClick();

private:

	UPROPERTY()
	class UMainMenu* Parent;

	uint32 Index;
	
};
