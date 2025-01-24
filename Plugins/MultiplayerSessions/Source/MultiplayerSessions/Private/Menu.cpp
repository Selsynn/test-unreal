// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu.h"
#include "Components/Button.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MultiplayerSessionsSubsystem.h"

void UMenu::MenuSetup(int32 iPlayerNumber, FString sMatchType)
{
	AddToViewport();
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
	}
}
/*
void UMenu::MenuStartSetupForHost()
{
	AddToViewport();
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



	if (StartButton) {
		StartButton->OnClicked.AddDynamic(this, &ThisClass::StartButtonClicked);
	}


	//UWorld* World = GetWorld();
	//if (World) {
	//	APlayerController* PlayerController = World->GetFirstPlayerController();
	//	if (PlayerController) {
	//		FInputModeUIOnly InputModeData;
	//		InputModeData.SetWidgetToFocus(TakeWidget());
	//		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//		PlayerController->SetInputMode(InputModeData);
	//		PlayerController->SetShowMouseCursor(true);
	//	}
	//}

	//UGameInstance* GameInstance = GetGameInstance();
	//if (GameInstance) {
	//	MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	//}

	//this->PlayerNumber = iPlayerNumber;
	//this->MatchType = sMatchType;

	//if (MultiplayerSessionsSubsystem) {
	//	MultiplayerSessionsSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
	//	MultiplayerSessionsSubsystem->MultiplayerOnFindSessionsComplete.AddUObject(this, &ThisClass::OnFindSessions);
	//	MultiplayerSessionsSubsystem->MultiplayerOnJoinSessionComplete.AddUObject(this, &ThisClass::OnJoinSession);
	//	MultiplayerSessionsSubsystem->MultiplayerOnDestroySessionComplete.AddDynamic(this, &ThisClass::OnDestroySession);
	//	MultiplayerSessionsSubsystem->MultiplayerOnStartSessionComplete.AddDynamic(this, &ThisClass::OnStartSession);
	//}
}

*/
bool UMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (HostButton) {
		HostButton->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
	}
	if (JoinButton) {
		JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
	}
	return true;
}

void UMenu::NativeDestruct()
{
	MenuTearDown();

	Super::NativeDestruct();
}

void UMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful) {
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString(TEXT("Session created successfully ")));
		}

		UWorld* World = GetWorld();
		if (World) {
			World->ServerTravel(FString("/Game/ThirdPerson/Maps/Lobby?listen?host"));
		}
	}
	else {
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Failed to create session")));
		}

	}
}

void UMenu::OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful)
{

	if (MultiplayerSessionsSubsystem == nullptr) return;
	for (auto Result : SessionResults) {
		FString Id = Result.GetSessionIdStr();
		FString User = Result.Session.OwningUserName;
		FString SettingsValue;
		Result.Session.SessionSettings.Get(FName("MatchType"), SettingsValue);
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("Session Id: %s, User: %s"), *Id, *User));
		}
		if (SettingsValue == MatchType) {
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("Joining a %s"), *MatchType));
			}

			MultiplayerSessionsSubsystem->JoinSession(Result);
			return;
		}
	}
}

void UMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("Join Session %d"), (int)Result));

		if (Result == EOnJoinSessionCompleteResult::UnknownError) {

			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Unknown error while Join Session")));
		}
	}
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (!Subsystem) { return; }

	IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
	
	if (!SessionInterface.IsValid()) {
		return;
	}

	FString Address;
	SessionInterface->GetResolvedConnectString(NAME_GameSession, Address);
	APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
	if (PlayerController)
	{
		PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}

void UMenu::OnDestroySession(bool bWasSuccessful)
{
}

void UMenu::OnStartSession(bool bWasSuccessful)
{
}

void UMenu::HostButtonClicked()
{

	if (MultiplayerSessionsSubsystem) {
		MultiplayerSessionsSubsystem->CreateSession(PlayerNumber, MatchType);

	}
}

void UMenu::JoinButtonClicked()
{
	if (MultiplayerSessionsSubsystem) {
		MultiplayerSessionsSubsystem->FindSessions(10000);
	}


}

/*
void UMenu::MenuStartSetupForHost()
{
	AddToViewport();
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



	if (StartButton) {
		StartButton->OnClicked.AddDynamic(this, &ThisClass::StartButtonClicked);
	}


	//UWorld* World = GetWorld();
	//if (World) {
	//	APlayerController* PlayerController = World->GetFirstPlayerController();
	//	if (PlayerController) {
	//		FInputModeUIOnly InputModeData;
	//		InputModeData.SetWidgetToFocus(TakeWidget());
	//		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//		PlayerController->SetInputMode(InputModeData);
	//		PlayerController->SetShowMouseCursor(true);
	//	}
	//}

	//UGameInstance* GameInstance = GetGameInstance();
	//if (GameInstance) {
	//	MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	//}

	//this->PlayerNumber = iPlayerNumber;
	//this->MatchType = sMatchType;

	//if (MultiplayerSessionsSubsystem) {
	//	MultiplayerSessionsSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
	//	MultiplayerSessionsSubsystem->MultiplayerOnFindSessionsComplete.AddUObject(this, &ThisClass::OnFindSessions);
	//	MultiplayerSessionsSubsystem->MultiplayerOnJoinSessionComplete.AddUObject(this, &ThisClass::OnJoinSession);
	//	MultiplayerSessionsSubsystem->MultiplayerOnDestroySessionComplete.AddDynamic(this, &ThisClass::OnDestroySession);
	//	MultiplayerSessionsSubsystem->MultiplayerOnStartSessionComplete.AddDynamic(this, &ThisClass::OnStartSession);
	//}
}

*/


void UMenu::MenuTearDown()
{
	RemoveFromParent();
	UWorld* World = GetWorld();
	if (World) {
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController) {
			FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(false);
		}
	}
}
