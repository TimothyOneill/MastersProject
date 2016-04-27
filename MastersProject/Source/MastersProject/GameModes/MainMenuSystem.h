#pragma once
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameMode.h"
#include "MainMenuSystem.generated.h"

/**
* MainMenuSystem defines the functionality to launch both the VR and NON VR experiment
* it also allows easy switching between widgest allowing for multple menu screens.

* UFUNCTION(BlueprintCallable, Category = "Main Menu") - are callable in blueprints
* allowing easy event driven scripting.

* UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main Menu") - allows the variable
* to be set in the editor for easy of setting the default widget to intially load.
**/

UCLASS()
class MASTERSPROJECT_API AMainMenuSystem : public AGameMode
{
    GENERATED_BODY()
public:

    AMainMenuSystem(const FObjectInitializer& ObjectInitializer);

    virtual void StartPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Main Menu")
    void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);
    UFUNCTION(BlueprintCallable, Category = "Main Menu")
    void LaunchDefaultGame();
    UFUNCTION(BlueprintCallable, Category = "Main Menu")
    void LaunchVRGame();
    UFUNCTION(BlueprintCallable, Category = "Main Menu")
    void LaunchDefaultDemo();
    UFUNCTION(BlueprintCallable, Category = "Main Menu")
    void LaunchVRDemo();
    void EnableVirtualReality(bool Val);

protected:

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main Menu")
    TSubclassOf<UUserWidget> StartingWidgetClass;
    UPROPERTY()
    UUserWidget* CurrentWidget;
};
