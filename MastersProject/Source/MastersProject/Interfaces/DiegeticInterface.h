#pragma once
#include "InterfaceMarker.h"
#include <deque>
#include <vector>
#include "DiegeticInterface.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MASTERSPROJECT_API UDiegeticInterface : public UObject, public FTickableGameObject
{
    GENERATED_BODY()
public:
    UDiegeticInterface();
    void Init();
    void EnableTick() { bTick = true; };
    void DisableTick() { bTick = false; };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DiegeticModel")
    TSubclassOf<AActor> HandScannerBP;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InterfaceVisual")
    TSubclassOf<AActor> InterfaceVisualBP;
private:
    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override;
    virtual TStatId GetStatId() const override;

    bool bTick = false;

    AActor* DiegeticModel;
    std::deque<AActor*> PendingMarks;
    std::vector<AInterfaceMarker*> InterfaceMarks;
    APlayerController* OwningPlayer;
};
