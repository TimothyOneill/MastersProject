// Fill out your copyright notice in the Description page of Project Settings.

#include "MastersProject.h"
#include "MainMenuSystem.h"

AMainMenuSystem::AMainMenuSystem(const FObjectInitializer& ObjectInitalizer) : Super(ObjectInitalizer) {}

void AMainMenuSystem::StartPlay()
{
    Super::StartPlay();
    ChangeMenuWidget(StartingWidgetClass);
}

void AMainMenuSystem::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
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

void AMainMenuSystem::LaunchDefaultGame()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Launching Game in NON STEREO"));
    UGameplayStatics::OpenLevel(GetWorld(), "Space_Scene");
}

void AMainMenuSystem::LaunchVRGame()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Launching Game in STEREO"));
    UGameplayStatics::OpenLevel(GetWorld(), "Space_Scene");
}

void AMainMenuSystem::LaunchDefaultDemo()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Launching Game in Default demo mode"));
    UGameplayStatics::OpenLevel(GetWorld(), "Space_Scene");
}

void AMainMenuSystem::LaunchVRDemo()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Launching Game in VR demo mode"));
    UGameplayStatics::OpenLevel(GetWorld(), "Space_Scene");
}