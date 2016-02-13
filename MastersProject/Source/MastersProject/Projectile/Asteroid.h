// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

UCLASS()
class MASTERSPROJECT_API AAsteroid : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AAsteroid();
    void Init(FVector Target);

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;

    UFUNCTION()
    virtual void OnCollision(AActor *SelfActor, AActor *OtherActor, FVector NormalImpulse, const FHitResult& Hit);
    UFUNCTION()
    virtual void OnOverlap(AActor* OtherActor);

    UStaticMesh* AsteroidStaticMesh;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SM Assets")
    UStaticMeshComponent* AsteroidVisual;

private:
    FVector Target = FVector(0.0f,0.0f,0.0f);
    FVector DirectionVector = FVector(0.0f, 0.0f, 0.0f);
    const float Speed = 0.15f;
};
