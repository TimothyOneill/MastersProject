#pragma once
#include "GameFramework/Actor.h"
#include "Asteroid.h"
#include <vector>
#include "AsteroidSpawner.generated.h"

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
    std::vector<AAsteroid*> const &GetAsteroids() const { return asteroids; };

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner Settings")
    float SpawnTimer = 1.5f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner Settings")
    int32 SpawnRange = 5000;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
    AActor* target;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
    ETargetEnum TargetType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyBPForCPP")
    TSubclassOf<AAsteroid> AsteroidBP;

private :

    FVector DefaultLocation;
    FTimerHandle LocationTimerHandle;
    FTimerHandle SpawnerTimerHandle;
    std::vector<AAsteroid*> asteroids;
    USphereComponent* SpawnerVisual;
};
