// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "MastersProjectDemoMode.generated.h"

/**
 * 
 */
UCLASS()
class MASTERSPROJECT_API AMastersProjectDemoMode : public AGameMode
{
	GENERATED_BODY()
public:

    AMastersProjectDemoMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {};

    //Transitions to Waiting to Start.
    virtual void StartPlay() override;
    virtual void HandleMatchHasStarted();
    virtual void HandleMatchHasEnded();

    void RestartGameTimer();
    void StopGameTimer();

protected:

    FTimerHandle GameTimerHandle;
    float GameTimer = 5.0f;
};
