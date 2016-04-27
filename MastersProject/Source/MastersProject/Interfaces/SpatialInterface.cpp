#include "MastersProject.h"
#include "SpatialInterface.h"

USpatialInterface::USpatialInterface() {}

//Hides all the markers on the various game entities.
void USpatialInterface::HideMarkers()
{
    for (TActorIterator<AAsteroid> ActorItr(GWorld); ActorItr; ++ActorItr)
    {
        ActorItr->HideMarker();
    }

    for (TActorIterator<AWayPoint> ActorItr(GWorld); ActorItr; ++ActorItr)
    {
        ActorItr->HideMarker();
    }
}

//Shows all the markers on the various game entities.
void USpatialInterface::Tick(float DeltaTime)
{
    for (TActorIterator<AAsteroid> ActorItr(GWorld); ActorItr; ++ActorItr)
    {
        ActorItr->ShowMarker();
    }

    for (TActorIterator<AWayPoint> ActorItr(GWorld); ActorItr; ++ActorItr)
    {
        ActorItr->ShowMarker();
    }
}

bool USpatialInterface::IsTickable() const
{
    return CanTick;
}

TStatId USpatialInterface::GetStatId() const
{
    return TStatId();
}
