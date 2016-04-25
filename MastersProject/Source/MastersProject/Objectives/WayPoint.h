#pragma once
#include "GameFramework/Actor.h"
#include "WayPointLocations.h"
#include "../Utilities/MastersProjectWorldSettings.h"
#include "WayPoint.generated.h"

UCLASS()
class MASTERSPROJECT_API AWayPoint : public AActor
{
    GENERATED_BODY()
public:

    AWayPoint();
    void Destroyed() override;

    virtual void BeginPlay() override;
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
