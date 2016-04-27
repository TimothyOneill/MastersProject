#pragma once
#include "DiegeticInterface.generated.h"

/**
* Diegetic interface managers the various parts of the Diegetic interface
* Made up of a standard Uobject and extended with tick functionality so it can perform updates.

* UProperty() allows us to set the Visual parts of the interface in the editor 

* Interaface consists of a model and a 3D widget for the interface.
* 3D widgets are experimental unreal engine classes.

**/

UCLASS(Blueprintable)
class MASTERSPROJECT_API UDiegeticInterface : public UObject, public FTickableGameObject
{
    GENERATED_BODY()
public:

    UDiegeticInterface();

    void Init();
    void EnableTick() { CanTick = true; };
    void DisableTick() { CanTick = false; };

    UPROPERTY()
    TSubclassOf<AActor> HandScannerBP;
    UPROPERTY()
    TSubclassOf<AActor> WidgetBP;

private:

    virtual void Tick(float DeltaTime) override {};
    virtual bool IsTickable() const override;
    virtual TStatId GetStatId() const override;
    virtual void BeginDestroy() override;

    AActor* DiegeticModel;
    AActor* Interface3D;
    APlayerController* OwningPlayer;

    bool CanTick = false;
};
