// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "Engine/Engine.h"
#include "TimerManager.h"

#include "PuzzlePlatformsGameInstance.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UE_LOG(LogTemp, Warning, TEXT("called PostLogin"));
	++NumberPlayers;
	if (NumberPlayers >= 2) {
		UE_LOG(LogTemp, Warning, TEXT("PostLogin %i"), NumberPlayers);
		auto World = GetWorld();
		if (!ensure(World != nullptr)) return;

		if (TimerHandler.IsValid() == false) {
			GetWorldTimerManager().SetTimer(TimerHandler, this, &ALobbyGameMode::ServerTravel, 10.0f);
		}
	}

}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	UE_LOG(LogTemp, Warning, TEXT("called Logout"));
	--NumberPlayers;

}


void ALobbyGameMode::ServerTravel()
{
	auto GameInstance = Cast<UPuzzlePlatformsGameInstance>(GetGameInstance());
	if (!ensure(GameInstance != nullptr)) return;

	GameInstance->StartSession();

	UE_LOG(LogTemp, Warning, TEXT("called ServerTravel"));
	auto World = GetWorld();
	if (!ensure(World != nullptr)) return;
	GetWorldTimerManager().ClearTimer(TimerHandler);

	bUseSeamlessTravel = true;
	World->ServerTravel("/Game/PuzzlePlatforms/Maps/Game?listen"); //?listen
}