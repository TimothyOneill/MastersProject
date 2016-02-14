// Fill out your copyright notice in the Description page of Project Settings.

#include "MastersProject.h"
#include "MastersProjectGameMode.h"
#include "Player/MainPlayer.h"
#include "Projectile/Asteroid.h"
#include "MastersProjectWorldSettings.h"
#include "MetricTracker.h"

void AMastersProjectGameMode::StartPlay()
{
    Super::StartPlay();
    NumExperiments = Cast<AMastersProjectWorldSettings>(GetWorld()->GetWorldSettings())->GetNumExperiments();
    GenerateTestOrder();
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
    GetWorldTimerManager().SetTimer(GameTimerHandle, this, &AMastersProjectGameMode::ChangeTestScenario, GameTimer, true);
}

void AMastersProjectGameMode::StopGameTimer()
{
    GetWorldTimerManager().ClearTimer(GameTimerHandle);
}

void AMastersProjectGameMode::ChangeTestScenario()
{
    switch (*TestOrder.begin())
    {
    case 0 : TestOrder.erase(TestOrder.begin()), GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Digetic Interface")), MetricTracker::Instance()->SetSectionName("Digetic Interface"), MetricTracker::Instance()->WriteMetricsToFile();
        break;
        case 1 : TestOrder.erase(TestOrder.begin()), GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Non Diegetic Interface")), MetricTracker::Instance()->SetSectionName("Non Diegetic Interface"), MetricTracker::Instance()->WriteMetricsToFile();;
        break;
        case 2 : TestOrder.erase(TestOrder.begin()), GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Spatial Interface")), MetricTracker::Instance()->SetSectionName("Spatial Interface"), MetricTracker::Instance()->WriteMetricsToFile();;
        break;
        case 3 : TestOrder.erase(TestOrder.begin()), GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Meta Interface")), MetricTracker::Instance()->SetSectionName("Meta Interface"), MetricTracker::Instance()->WriteMetricsToFile();;
        break;
        case 4 : TestOrder.erase(TestOrder.begin()), GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("No Interface")), MetricTracker::Instance()->SetSectionName("No Interface"), MetricTracker::Instance()->WriteMetricsToFile();;
        break;
        default : StopGameTimer(), SetMatchState(MatchState::WaitingPostMatch), GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("End of Test Session!"));
    }
}

void AMastersProjectGameMode::GenerateTestOrder()
{
    while (TestOrder.size() != NumExperiments)
    {
        TestOrder.insert(FMath::RandRange(0, NumExperiments-1));
    }
}
