// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Asteroid.h"
#include <vector>
#include "AsteroidSpawner.generated.h"

UCLASS()
class MASTERSPROJECT_API AAsteroidSpawner : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AAsteroidSpawner();

    void Init();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;

    void RestartSpawnTimer();
    void StopSpawnTimer();
    void SpawnAsteroid();
    void CalculateNextPosition();

    float SpawnTimer = 3.0f;
    int16 SpawnRange = 5000;
    FVector DefaultLocation;
    FTimerHandle LocationTimerHandle;
    FTimerHandle SpawnerTimerHandle;
    std::vector<AAsteroid*> asteroids;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Target")
    AActor* target;
};
