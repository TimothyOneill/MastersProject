// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "GameFramework/GameMode.h"
#include <unordered_set>
#include "MastersProjectGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MASTERSPROJECT_API AMastersProjectGameMode : public AGameMode
{
    GENERATED_BODY()
public:

    AMastersProjectGameMode(const FObjectInitializer& ObjectInitializer);

    //Transitions to Waiting to Start.
    virtual void StartPlay() override;
    virtual void HandleMatchHasStarted();
    virtual void HandleMatchHasEnded();

    void RestartGameTimer();
    void StopGameTimer();
    void ChangeTestScenario();
    void GenerateTestOrder();

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

protected:

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main Menu")
    TSubclassOf<UUserWidget> StartingWidgetClass;
    UPROPERTY()
    UUserWidget* CurrentWidget;
    FTimerHandle GameTimerHandle;
    std::unordered_set<int> TestOrder;
    float GameTimer = 5.0f;
};
