// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "GameFramework/Actor.h"
#include "WayPointLocations.h"
#include "WayPoint.generated.h"

UCLASS()
class MASTERSPROJECT_API AWayPoint : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AWayPoint();
    void Destroyed() override;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;

    UFUNCTION()
    virtual void OnOverlap(AActor* OtherActor);

    void ShowMarker() { Marker->SetActorHiddenInGame(false); };
    void HideMarker() { Marker->SetActorHiddenInGame(true); };

    void ReportElapsedTime();
    void MoveNextLocation();

    UPROPERTY(EditAnywhere, Category = "Marker", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<AActor> MarkerBP;

private:
    AActor* Marker;
    UDataTable* WayPointLocations;
    FWayPointLocations* LocationsRow;
    int32 CollisionCount = 1;
    int32 NumberOfWaypoints = 1;
    int32 StartTime = 0;
    int32 PassedTime = 0;
    bool CollisionLock = false;
};
