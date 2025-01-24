// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "LobbyScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class MENUSUBSYSTEMSTEAM_API ALobbyScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void LobbySetup();

protected:
	UFUNCTION(BlueprintCallable)
	void StartButtonActionned();

private:
	bool bIsHost{false};
};
