#pragma once
#include "GameFramework/WorldSettings.h"
#include "MastersProjectWorldSettings.generated.h"

USTRUCT()
struct FSpecificProjectSettings
{
    GENERATED_USTRUCT_BODY()

    /**Used to Adjust the time for each each step of the whole experiment runs*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, config, Category = ExperimentSettings, AdvancedDisplay)
    float GameTimer;

    /**Used to Adjust the time the user has to play the demo of the experiment*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, config, Category = ExperimentSettings, AdvancedDisplay)
    float DemoTimer;

    /**Used to adjust the total number of steps of the whole experiment*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, config, Category = ExperimentSettings, AdvancedDisplay)
    int32 NumExperiments;

    /**Used to set the number of waypoints the user has to traverse*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, config, Category = ExperimentSettings, AdvancedDisplay)
    int32 NumWayPoints;

    /**Used to Set the filename to use for outputing the collected metrics*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, config, Category = ExperimentSettings, AdvancedDisplay)
    FString File;

    FSpecificProjectSettings() : GameTimer(300.0f), NumExperiments(5), NumWayPoints(10), File("DiscreteMetrics.txt") {}
};

UCLASS()
class MASTERSPROJECT_API AMastersProjectWorldSettings : public AWorldSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnyWhere, Category = ExperimentSettings)
    struct FSpecificProjectSettings ExperimentSettings;

public:
    float GetGameTimer()
    {
        return ExperimentSettings.GameTimer;
    }

    float GetDemoTimer()
    {
        return ExperimentSettings.DemoTimer;
    }

    int32 GetNumExperiments()
    {
        return ExperimentSettings.NumExperiments;
    }
    
    int32 GetNumWaypoints()
    {
        return ExperimentSettings.NumWayPoints;
    }

    FString GetFile()
    {
        return ExperimentSettings.File;
    }
};
