#pragma once
#include "Projectile/Asteroid.h"
#include "DiegeticInterface.h"
#include "SpatialInterface.h"

/**
* Interfacemanager handles all the interface objects and which is display.

* By using an enum allows easy switching of interface through one method call
* Interface manager handles the rest.

* Non UClass() so can't be seen in editor.

**/

//Enum to manage which interface is to be display.
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

    UPROPERTY()
    USpatialInterface* SpatialInterface;
    UPROPERTY()
    UDiegeticInterface* DiegeticInterface;
    TSubclassOf<AHUD> MetaInterface;
    TSubclassOf<AHUD> NonDiegeticInterface;
};