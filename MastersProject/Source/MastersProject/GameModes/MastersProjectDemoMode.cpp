// Fill out your copyright notice in the Description page of Project Settings.

#include "MastersProject.h"
#include "MastersProjectWorldSettings.h"
#include "MetricTracker.h"
#include "MastersProjectDemoMode.h"

AMastersProjectDemoMode::AMastersProjectDemoMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    Interfaces = new InterfaceManager();
}

void AMastersProjectDemoMode::StartPlay()
{
    Super::StartPlay();
    ChangeTestScenario();
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
    MetricTracker::Instance()->ClearAllMetrics();
    StopGameTimer();
    UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}

void AMastersProjectDemoMode::RestartGameTimer()
{
    GetWorldTimerManager().SetTimer(GameTimerHandle, this, &AMastersProjectDemoMode::ChangeTestScenario, GameTimer, true);
}

void AMastersProjectDemoMode::StopGameTimer()
{
    GetWorldTimerManager().ClearTimer(GameTimerHandle);
}

void AMastersProjectDemoMode::ChangeTestScenario()
{
    switch (CurrentInterface)
    {
    case 0: Interfaces->ChangeInterface(EInterfaceEnum::IE_DiegeticInterface);
        break;
    case 1: Interfaces->ChangeInterface(EInterfaceEnum::IE_NonDiegeticInterface);
        break;
    case 2: Interfaces->ChangeInterface(EInterfaceEnum::IE_MetaInterface);
        break;
    case 3: Interfaces->ChangeInterface(EInterfaceEnum::IE_SpatialInterface);
        break;
    case 4: Interfaces->ChangeInterface(EInterfaceEnum::IE_NoInterface);
        break;
    default: StopGameTimer(), SetMatchState(MatchState::WaitingPostMatch);
        break;
    }
    CurrentInterface++;
}