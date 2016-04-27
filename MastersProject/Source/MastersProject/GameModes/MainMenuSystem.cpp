#include "MastersProject.h"
#include "MainMenuSystem.h"
#include "IHeadMountedDisplay.h"

AMainMenuSystem::AMainMenuSystem(const FObjectInitializer& ObjectInitalizer) : Super(ObjectInitalizer) {}

//Called on level load.
void AMainMenuSystem::StartPlay()
{
    Super::StartPlay();
    EnableVirtualReality(false);
    ChangeMenuWidget(StartingWidgetClass);
}

//Changes the current menu widget being displayed blueprint callable.
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
    EnableVirtualReality(false);
    UGameplayStatics::OpenLevel(GetWorld(), "L_Space");
}

void AMainMenuSystem::LaunchVRGame()
{
    EnableVirtualReality(true);
    UGameplayStatics::OpenLevel(GetWorld(), "L_Space");
}

void AMainMenuSystem::LaunchDefaultDemo()
{
    EnableVirtualReality(false);
    UGameplayStatics::OpenLevel(GetWorld(), "L_SpaceDemo");
}

void AMainMenuSystem::LaunchVRDemo()
{
    EnableVirtualReality(true);
    UGameplayStatics::OpenLevel(GetWorld(), "L_SpaceDemo");
}

//Helper function to enable and disable rendering to the VR headset.
void AMainMenuSystem::EnableVirtualReality(bool Val)
{
    if (GEngine->HMDDevice.IsValid())
    {
        GEngine->HMDDevice->EnableHMD(Val);
        GEngine->HMDDevice->EnableStereo(Val);
    }
}