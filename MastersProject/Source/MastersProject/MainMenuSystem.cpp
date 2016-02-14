// Fill out your copyright notice in the Description page of Project Settings.

#include "MastersProject.h"
#include "MainMenuSystem.h"
#include "IHeadMountedDisplay.h"

AMainMenuSystem::AMainMenuSystem(const FObjectInitializer& ObjectInitalizer) : Super(ObjectInitalizer) {}

void AMainMenuSystem::StartPlay()
{
    Super::StartPlay();
    EnableVirtualReality(false);
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
    EnableVirtualReality(false);
    UGameplayStatics::OpenLevel(GetWorld(), "Space_Scene");
}

void AMainMenuSystem::LaunchVRGame()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Launching Game in STEREO"));
    EnableVirtualReality(true);
    UGameplayStatics::OpenLevel(GetWorld(), "Space_Scene");
}

void AMainMenuSystem::LaunchDefaultDemo()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Launching Game in NON STEREO demo mode"));
    EnableVirtualReality(false);
    UGameplayStatics::OpenLevel(GetWorld(), "Space_Scene_Demo");
}

void AMainMenuSystem::LaunchVRDemo()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Launching Game in STEREO demo mode"));
    EnableVirtualReality(true);
    UGameplayStatics::OpenLevel(GetWorld(), "Space_Scene_Demo");
}

void AMainMenuSystem::EnableVirtualReality(bool val)
{
    if (GEngine->HMDDevice.IsValid())
    {
        GEngine->HMDDevice->EnableHMD(val);
        GEngine->HMDDevice->EnableStereo(val);
    }
}