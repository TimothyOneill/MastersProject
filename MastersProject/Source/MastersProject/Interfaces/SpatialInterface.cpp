// Fill out your copyright notice in the Description page of Project Settings.

#include "MastersProject.h"
#include "SpatialInterface.h"

USpatialInterface::USpatialInterface()
{

}

void USpatialInterface::Tick(float DeltaTime)
{
    for (TActorIterator<AAsteroid> ActorItr(GWorld); ActorItr; ++ActorItr)
    {
        ActorItr->ShowMarker();
    }
}

bool USpatialInterface::IsTickable() const
{
    return bTick;
}

TStatId USpatialInterface::GetStatId() const
{
    return TStatId();
}
