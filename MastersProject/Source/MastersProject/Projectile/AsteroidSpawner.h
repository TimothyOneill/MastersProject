// Fill out your copyright notice in the Description page of Project Settings.
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
    // Sets default values for this actor's properties
    AAsteroidSpawner();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
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
    FVector DefaultLocation;
    FTimerHandle LocationTimerHandle;
    FTimerHandle SpawnerTimerHandle;
    std::vector<AAsteroid*> asteroids;
    USphereComponent* SpawnerVisual;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Target")
    AActor* target;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
    ETargetEnum TargetType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyBPForCPP")
    TSubclassOf<AAsteroid> AsteroidBP;
};
