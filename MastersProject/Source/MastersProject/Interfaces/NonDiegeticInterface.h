#pragma once
#include "InterfaceMarker.h"
#include <deque>
#include <vector>
#include "NonDiegeticInterface.generated.h"

/**
 * 
 */
UCLASS(BluePrintable)
class MASTERSPROJECT_API UNonDiegeticInterface : public UObject, public FTickableGameObject
{
    GENERATED_BODY()
public:
    UNonDiegeticInterface();
    void Init();
    void EnableTick() { bTick = true; };
    void DisableTick() { bTick = false; };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NonDiegeticModel")
    TSubclassOf<AActor> RadarBP;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InterfaceVisual")
    TSubclassOf<AActor> InterfaceVisualBP;

private:
    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override;
    virtual TStatId GetStatId() const override;

    bool bTick = false;

    AActor* NonDiegeticModel;
    std::deque<AActor*> PendingMarks;
    std::vector<AInterfaceMarker*> InterfaceMarks;
    APlayerController* OwningPlayer;
};
