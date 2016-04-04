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
    void Destroyed() override;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;

    UFUNCTION()
    virtual void OnOverlap(AActor* OtherActor);

    void ShowMarker() { Marker->SetActorHiddenInGame(false); };
    void HideMarker() { Marker->SetActorHiddenInGame(true); };

    UPROPERTY(EditAnywhere, Category = "Marker", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<AActor> MarkerBP;

private:
    FVector Target = FVector(0.0f,0.0f,0.0f);
    FVector DirectionVector = FVector(0.0f, 0.0f, 0.0f);
    AActor* Marker;
    const float Speed = 0.3f;
};
