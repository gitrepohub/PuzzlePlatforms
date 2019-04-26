// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerRow.h"
#include "MainMenu.h"
#include "Components/Button.h"

bool UServerRow::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success) return false;

	if (!ensure(ServerButton != nullptr)) return false;
	ServerButton->OnClicked.AddDynamic(this, &UServerRow::OnClick);


	return true;
}


void UServerRow::Setup(UMainMenu* InParent, uint32& InIndex)
{
	Parent = InParent;
	Index = InIndex;
}


void UServerRow::OnClick()
{
	if (Parent) Parent->SelectIndex(Index);
}
