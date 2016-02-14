// Fill out your copyright notice in the Description page of Project Settings.

#include "MastersProject.h"
#include "MastersProjectWorldSettings.h"
#include "MetricTracker.h"
#include "MastersProjectDemoMode.h"

void AMastersProjectDemoMode::StartPlay()
{
    Super::StartPlay();
}

void AMastersProjectDemoMode::HandleMatchHasStarted()
{
    Super::HandleMatchHasStarted();
    GameTimer = Cast<AMastersProjectWorldSettings>(GetWorld()->GetWorldSettings())->GetDemoTimer();
    RestartGameTimer();
}

void AMastersProjectDemoMode::HandleMatchHasEnded()
{
    Super::HandleMatchHasEnded();
    StopGameTimer();
    MetricTracker::Instance()->ClearMetrics();
    UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}

void AMastersProjectDemoMode::RestartGameTimer()
{
    GetWorldTimerManager().SetTimer(GameTimerHandle, this, &AMastersProjectDemoMode::HandleMatchHasEnded, GameTimer, true);
}

void AMastersProjectDemoMode::StopGameTimer()
{
    GetWorldTimerManager().ClearTimer(GameTimerHandle);
}