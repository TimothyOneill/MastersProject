#pragma once
#include "Projectile/Asteroid.h"
#include "DiegeticInterface.h"
#include "SpatialInterface.h"

enum class EInterfaceEnum : uint8
{
    IE_SpatialInterface,
    IE_DiegeticInterface,
    IE_NonDiegeticInterface,
    IE_MetaInterface,
    IE_NoInterface
};

class InterfaceManager
{
public:
    InterfaceManager();

    EInterfaceEnum GetInterface();

    void ChangeInterface(EInterfaceEnum NewInterface);
    void ClearInterface();

private:
    EInterfaceEnum CurrentInterface;

    USpatialInterface* SpatialInterface;
    UDiegeticInterface* DiegeticInterface;
    TSubclassOf<AHUD> MetaInterface;
    TSubclassOf<AHUD> NonDiegeticInterface;
};