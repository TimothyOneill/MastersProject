// Fill out your copyright notice in the Description page of Project Settings.

#include "MastersProject.h"
#include "MastersProjectGameMode.h"
#include "Player/MainPlayer.h"

AMastersProjectGameMode::AMastersProjectGameMode(const FObjectInitializer& ObjectInitalizer) : Super(ObjectInitalizer)
{
    DefaultPawnClass = AMainPlayer::StaticClass();
}

void AMastersProjectGameMode::StartPlay()
{
    Super::StartPlay();

    StartMatch();
}