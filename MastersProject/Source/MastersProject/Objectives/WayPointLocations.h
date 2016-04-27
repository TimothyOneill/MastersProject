#pragma once
#include "WayPointLocations.generated.h"

/**
* Used to define the contents of the Datatable used to store the waypoint locations.
**/

USTRUCT (BlueprintType)
struct FWayPointLocations : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
public:

    FWayPointLocations() : Location(FVector(0,0,0)) {}

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Warpoints)
    FVector Location;
};