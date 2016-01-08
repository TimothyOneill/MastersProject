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
    ChangeMenuWidget(StartingWidgetClass);
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