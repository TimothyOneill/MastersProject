#include "MastersProject.h"
#include "InterfaceManager.h"

InterfaceManager::InterfaceManager()
{
    SpatialInterface = NewObject<USpatialInterface>(USpatialInterface::StaticClass());
    DiegeticInterface = NewObject<UDiegeticInterface>(UDiegeticInterface::StaticClass());
    static ConstructorHelpers::FClassFinder<AHUD> NonDiegeticInterfaceBP(TEXT("Blueprint'/Game/StarterContent/Blueprints/Interfaces/NonDiegetic_Interface.NonDiegetic_Interface_C'"));
    if (NonDiegeticInterfaceBP.Class != NULL)
    {
        NonDiegeticInterface = NonDiegeticInterfaceBP.Class;
    }
    static ConstructorHelpers::FClassFinder<AHUD> MetaInterfaceBP(TEXT("Blueprint'/Game/StarterContent/Blueprints/Interfaces/Meta_Interface.Meta_Interface_C'"));
    if (MetaInterfaceBP.Class != NULL)
    {
        MetaInterface = MetaInterfaceBP.Class;
    }
}

EInterfaceEnum InterfaceManager::GetInterface()
{
    return CurrentInterface;
}

void InterfaceManager::ChangeInterface(EInterfaceEnum NewInterface)
{
    
    ClearInterface();
    CurrentInterface = NewInterface;
    switch (CurrentInterface)
    {
    case EInterfaceEnum::IE_SpatialInterface : SpatialInterface->EnableTick();
        break;
    case EInterfaceEnum::IE_DiegeticInterface : DiegeticInterface->Init(), DiegeticInterface->EnableTick();
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
