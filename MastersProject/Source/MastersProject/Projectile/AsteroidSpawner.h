#pragma once
#include "GameFramework/Actor.h"
#include "Asteroid.h"
#include <vector>
#include "AsteroidSpawner.generated.h"

/**
* Asteroid spawner manages the varaious asteroids its spawns and calculates the targets they aim for.

* UProperty() allows the setting of the variable in the editor.

* FTimerhandle manages how ofter an asteroid is spawned.

* CalculateAroundTarget() calculates a point in a circle arounda centre point.
* CalculateNextPosition() Calculates where the spawner should move to next in a half hemisphere.

**/

//Enum to outline the various types of Asteroids.
UENUM(BlueprintType)
enum class ETargetEnum : uint8
{
    TT_Direct   UMETA(DisplayName="Direct"),
    TT_Around   UMETA(DisplayName="Around"),
};

UCLASS()
class MASTERSPROJECT_API AAsteroidSpawner : public AActor
{
    GENERATED_BODY()
public:

    AAsteroidSpawner();

    virtual void BeginPlay() override;
    virtual void Tick( float DeltaSeconds ) override;

    void RestartSpawnTimer();
    void StopSpawnTimer();
    void SpawnAsteroid();
    FVector CalculateAroundTarget();
    void CalculateNextPosition();
    std::vector<AAsteroid*> const &GetAsteroids() const { return Asteroids; };

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner Settings")
    float SpawnTimer = 1.5f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner Settings")
    int32 SpawnRange = 5000;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
    AActor* Target;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
    ETargetEnum TargetType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyBPForCPP")
    TSubclassOf<AAsteroid> AsteroidBP;

private :

    FVector DefaultLocation;
    FTimerHandle LocationTimerHandle;
    FTimerHandle SpawnerTimerHandle;
    std::vector<AAsteroid*> Asteroids;
    USphereComponent* SpawnerVisual;
};
