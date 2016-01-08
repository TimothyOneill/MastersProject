// Fill out your copyright notice in the Description page of Project Settings.

#include "MastersProject.h"
#include "MastersProjectGameMode.h"
#include "Player/MainPlayer.h"
#include "Projectile/Asteroid.h"

AMastersProjectGameMode::AMastersProjectGameMode(const FObjectInitializer& ObjectInitalizer) : Super(ObjectInitalizer)
{
}

void AMastersProjectGameMode::StartPlay()
{
    Super::StartPlay();
    GenerateTestOrder();
    ChangeMenuWidget(StartingWidgetClass);
}

void AMastersProjectGameMode::HandleMatchHasStarted()
{
    Super::HandleMatchHasStarted();
    RestartGameTimer();
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Game Mode Starting"));
}

void AMastersProjectGameMode::HandleMatchHasEnded()
{
    Super::HandleMatchHasEnded();
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Game Mode Ended"));
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
        case 0 : TestOrder.erase(TestOrder.begin()), GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Test Number 1"));
        break;
        case 1 : TestOrder.erase(TestOrder.begin()), GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Test Number 2"));
        break;
        case 2 : TestOrder.erase(TestOrder.begin()), GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Test Number 3"));
        break;
        case 3 : TestOrder.erase(TestOrder.begin()), GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Test Number 4"));
        break;
        case 4 : TestOrder.erase(TestOrder.begin()), GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Test Number 5"));
        break;
        default : StopGameTimer(), GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("End of Test Session!"));
    }
}

void AMastersProjectGameMode::GenerateTestOrder()
{
    while (TestOrder.size() != 5)
    {
        TestOrder.insert(FMath::RandRange(0, 4));
    }
}

void AMastersProjectGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
    if (CurrentWidget != nullptr)
    {
        CurrentWidget->RemoveFromViewport();
        CurrentWidget = nullptr;
    }
    if (NewWidgetClass != nullptr)
    {
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
        if (CurrentWidget != nullptr)
        {
            CurrentWidget->AddToViewport();
        }
    }
}

void AMastersProjectGameMode::LaunchDefaultGame()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Launching Game in NON STEREO"));
    UGameplayStatics::OpenLevel(GetWorld(), "Space_Scene");
}

void AMastersProjectGameMode::LaunchVRGame()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Launching Game in STEREO"));
    UGameplayStatics::OpenLevel(GetWorld(), "Space_Scene");
}

void AMastersProjectGameMode::LaunchDefaultDemo()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Launching Game in Default demo mode"));
    UGameplayStatics::OpenLevel(GetWorld(), "Space_Scene");
}

void AMastersProjectGameMode::LaunchVRDemo()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Launching Game in VR demo mode"));
    UGameplayStatics::OpenLevel(GetWorld(), "Space_Scene");
}