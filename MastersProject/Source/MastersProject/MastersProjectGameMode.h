// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "MastersProjectGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MASTERSPROJECT_API AMastersProjectGameMode : public AGameMode
{
    GENERATED_BODY()
public:
    virtual void StartPlay() override;

    AMastersProjectGameMode(const FObjectInitializer& ObjectInitializer);
};
