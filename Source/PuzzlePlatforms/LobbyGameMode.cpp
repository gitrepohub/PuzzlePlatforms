// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("called PostLogin"));
	++NumberPlayers;
	if (NumberPlayers >= 3) UE_LOG(LogTemp, Warning, TEXT("PostLogin %i"), NumberPlayers);

	Super::PostLogin(NewPlayer);

}

void ALobbyGameMode::Logout(AController* Exiting)
{
	UE_LOG(LogTemp, Warning, TEXT("called Logout"));
	--NumberPlayers;

	Super::Logout(Exiting);
}
