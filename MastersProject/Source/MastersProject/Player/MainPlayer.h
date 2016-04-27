#pragma once
#include "GameFramework/Pawn.h"
#include "MainPlayerMovementComponent.h"
#include "MainPlayer.generated.h"

/**
* MainPlayer extends pawn it lays out the how the user can navigate the world.

* UPawnMovemntComponent allows us to change the players movement on the fly if future work requried it.
* Allows for extentability.

* UProperty() allows us to set the players model in the editor.

**/

UCLASS()
class MASTERSPROJECT_API AMainPlayer : public APawn
{
    GENERATED_BODY()
public:

    //Sets default values for this pawn's properties
    AMainPlayer();

    //Called when the game starts or when spawned
    virtual void BeginPlay() override;

    //Called every frame
    virtual void Tick( float DeltaSeconds ) override;

    //Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

    //Used to Return our custom input handler
    virtual UPawnMovementComponent* GetMovementComponent() const override;

    void MoveY(float AxisYValue);
    void MoveX(float AxisXValue);
    void TurnCameraY(float AxisYValue);
    void TurnCameraX(float AxisXValue);

    void TurnOculus();

    UStaticMesh* PlayerStaticMesh;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SM Assets")
    UStaticMeshComponent* PlayerVisual;

private:

    UMainPlayerMovementComponent* OurMovementComponent;
    USpringArmComponent* OurCameraSpringArm;
    UCameraComponent* OurCameraComponent;
};
