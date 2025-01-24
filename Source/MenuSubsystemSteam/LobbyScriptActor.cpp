// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyScriptActor.h"

void ALobbyScriptActor::LobbySetup()
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString(TEXT("ALobbyScriptActor Created")));


		UWorld* World = GetWorld();
		if (World) {
			//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString::Printf(TEXT("WorldInfo %s"), World->GetDetailedInfo()));
			if (World->IsNetMode(ENetMode::NM_Client)) {

				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString(TEXT("ALobbyScriptActor Created Client")));
			}
			if (World->IsNetMode(ENetMode::NM_DedicatedServer)) {
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString(TEXT("ALobbyScriptActor Created Dedicated server")));

			/*	AddToViewport();
				SetVisibility(ESlateVisibility::Visible);
				bIsFocusable = true;

				UWorld* World = GetWorld();
				if (World) {
					APlayerController* PlayerController = World->GetFirstPlayerController();
					if (PlayerController) {
						FInputModeUIOnly InputModeData;
						InputModeData.SetWidgetToFocus(TakeWidget());
						InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
						PlayerController->SetInputMode(InputModeData);
						PlayerController->SetShowMouseCursor(true);
					}
				}

				UGameInstance* GameInstance = GetGameInstance();
				if (GameInstance) {
					MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
				}

				this->PlayerNumber = iPlayerNumber;
				this->MatchType = sMatchType;

				if (MultiplayerSessionsSubsystem) {
					MultiplayerSessionsSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
					MultiplayerSessionsSubsystem->MultiplayerOnFindSessionsComplete.AddUObject(this, &ThisClass::OnFindSessions);
					MultiplayerSessionsSubsystem->MultiplayerOnJoinSessionComplete.AddUObject(this, &ThisClass::OnJoinSession);
					MultiplayerSessionsSubsystem->MultiplayerOnDestroySessionComplete.AddDynamic(this, &ThisClass::OnDestroySession);
					MultiplayerSessionsSubsystem->MultiplayerOnStartSessionComplete.AddDynamic(this, &ThisClass::OnStartSession);
				}*/
			}
			if (World->IsNetMode(ENetMode::NM_ListenServer)) {
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString(TEXT("ALobbyScriptActor Created Listen server")));
			}
		}
	}
}

void ALobbyScriptActor::StartButtonActionned()
{

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 600.f, FColor::Yellow, FString(TEXT("Clicked On Start Session")));
	}
}

