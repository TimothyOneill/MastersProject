#include "MastersProject.h"
#include "InterfaceManager.h"

InterfaceManager::InterfaceManager()
{
    //Non UClass() so The two huds must be set in this manner.
    static ConstructorHelpers::FClassFinder<AHUD> NonDiegeticInterfaceBP(TEXT("Blueprint'/Game/MastersProject/Blueprints/HUDs/HUD_NonDiegetic.HUD_NonDiegetic_C'"));
    if (NonDiegeticInterfaceBP.Class != NULL)
    {
        NonDiegeticInterface = NonDiegeticInterfaceBP.Class;
    }
    static ConstructorHelpers::FClassFinder<AHUD> MetaInterfaceBP(TEXT("Blueprint'/Game/MastersProject/Blueprints/HUDs/HUD_MetaInterface.HUD_MetaInterface_C'"));
    if (MetaInterfaceBP.Class != NULL)
    {
        MetaInterface = MetaInterfaceBP.Class;
    }
}

EInterfaceEnum InterfaceManager::GetInterface()
{
    return CurrentInterface;
}

//Handles the changing of the interfaces, the interfaces have different constructions.
void InterfaceManager::ChangeInterface(EInterfaceEnum NewInterface)
{
    ClearInterface();
    CurrentInterface = NewInterface;
    switch (CurrentInterface)
    {
    case EInterfaceEnum::IE_SpatialInterface : SpatialInterface = NewObject<USpatialInterface>(AActor::StaticClass(),"SpatialInterface", EObjectFlags::RF_RootSet), SpatialInterface->EnableTick();
        break;
    case EInterfaceEnum::IE_DiegeticInterface : DiegeticInterface = NewObject<UDiegeticInterface>(UObject::StaticClass(), "DiegeticInterface", EObjectFlags::RF_RootSet), DiegeticInterface->Init(), DiegeticInterface->EnableTick();
        break;
    case EInterfaceEnum::IE_NonDiegeticInterface : GWorld->GetFirstPlayerController()->ClientSetHUD(NonDiegeticInterface);
        break;
    case EInterfaceEnum::IE_MetaInterface : GWorld->GetFirstPlayerController()->ClientSetHUD(MetaInterface);
        break;
    case EInterfaceEnum::IE_NoInterface :
        break;
    default :
        break;
    }
}

//Tidys up the current interface in the specific manner of that interface.
void InterfaceManager::ClearInterface()
{
    switch (CurrentInterface)
    {
    case EInterfaceEnum::IE_SpatialInterface : SpatialInterface->HideMarkers(), SpatialInterface->DisableTick();
        break;
    case EInterfaceEnum::IE_DiegeticInterface: DiegeticInterface->DisableTick(), DiegeticInterface->ConditionalBeginDestroy();
        break;
    case EInterfaceEnum::IE_NonDiegeticInterface : GWorld->GetFirstPlayerController()->ClientSetHUD(NULL);
        break;
    case EInterfaceEnum::IE_MetaInterface : GWorld->GetFirstPlayerController()->ClientSetHUD(NULL);
        break;
    case EInterfaceEnum::IE_NoInterface :
        break;
    default:
        break;
    }
}
