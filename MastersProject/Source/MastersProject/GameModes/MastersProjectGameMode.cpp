// Fill out your copyright notice in the Description page of Project Settings.

#include "MastersProject.h"
#include "MastersProjectGameMode.h"

AMastersProjectGameMode::AMastersProjectGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    Interfaces = new InterfaceManager();
}

void AMastersProjectGameMode::StartPlay()
{
    Super::StartPlay();
    NumExperiments = Cast<AMastersProjectWorldSettings>(GetWorld()->GetWorldSettings())->GetNumExperiments();
    GenerateTestOrder();
    ChangeTestScenario();
}

void AMastersProjectGameMode::HandleMatchHasStarted()
{
    Super::HandleMatchHasStarted();
    GameTimer = Cast<AMastersProjectWorldSettings>(GetWorld()->GetWorldSettings())->GetGameTimer();
    RestartGameTimer();
}

void AMastersProjectGameMode::HandleMatchHasEnded()
{
    Super::HandleMatchHasEnded();
    StopGameTimer();
    UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}

void AMastersProjectGameMode::RestartGameTimer()
{
    GetWorldTimerManager().SetTimer(GameTimerHandle, this, &AMastersProjectGameMode::TimerFunction, GameTimer, true);
}

void AMastersProjectGameMode::StopGameTimer()
{
    GetWorldTimerManager().ClearTimer(GameTimerHandle);
}

void AMastersProjectGameMode::ChangeTestScenario()
{
    switch (*TestOrder.begin())
    {
    
    case 0 : TestOrder.erase(TestOrder.begin()), Interfaces->ChangeInterface(EInterfaceEnum::IE_DiegeticInterface), MetricTracker::Instance()->SetSectionName("Digetic Interface");
        break;
    case 1 : TestOrder.erase(TestOrder.begin()), Interfaces->ChangeInterface(EInterfaceEnum::IE_NonDiegeticInterface), MetricTracker::Instance()->SetSectionName("Non Digetic Interface");
        break;
    case 2 : TestOrder.erase(TestOrder.begin()), Interfaces->ChangeInterface(EInterfaceEnum::IE_MetaInterface), MetricTracker::Instance()->SetSectionName("Spatial Interface");
        break;
    case 3 : TestOrder.erase(TestOrder.begin()), Interfaces->ChangeInterface(EInterfaceEnum::IE_SpatialInterface), MetricTracker::Instance()->SetSectionName("Meta Interface");
        break;
    case 4 : TestOrder.erase(TestOrder.begin()), Interfaces->ChangeInterface(EInterfaceEnum::IE_NoInterface), MetricTracker::Instance()->SetSectionName("No Interface");
        break;
    default : StopGameTimer(), SetMatchState(MatchState::WaitingPostMatch);
        break;
    }
}

void AMastersProjectGameMode::TimerFunction()
{
    MetricTracker::Instance()->WriteMetricsToFile();
    MetricTracker::Instance()->ClearAllMetrics();
    ChangeTestScenario();
}

void AMastersProjectGameMode::GenerateTestOrder()
{
    while (TestOrder.size() != NumExperiments)
    {
        TestOrder.insert(FMath::RandRange(0, NumExperiments-1));
    }
}
