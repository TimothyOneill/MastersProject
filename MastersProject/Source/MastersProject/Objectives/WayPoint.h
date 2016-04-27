#pragma once
#include "GameFramework/Actor.h"
#include "WayPointLocations.h"
#include "../Utilities/MastersProjectWorldSettings.h"
#include "WayPoint.generated.h"

/**
* Waypoint extends actor and movement logic and model of the points
* the player has to visit.

* UProperty() allows the model for the waypoint to be set in the editor.
* UDataTable() allows us to access the locations the waypoints should appear at.

* Collision Lock requried due to a bug in UE4Engine4.10 see http://tinyurl.com/hgmybn3 4.11 patch notes

**/

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
