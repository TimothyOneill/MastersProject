#pragma once
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameMode.h"
#include "MainMenuSystem.generated.h"

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
