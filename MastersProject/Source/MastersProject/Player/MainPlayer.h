// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "MainPlayerMovementComponent.h"
#include "MainPlayerCameraComponent.h"
#include "MainPlayer.generated.h"

UCLASS()
class MASTERSPROJECT_API AMainPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainPlayer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

    //Used to Return our custom input handler
    virtual UPawnMovementComponent* GetMovementComponent() const override;

    void MoveForward(float AxisValue);
    void MoveRight(float AxisValue);
    void Turn(float AxisXValue);

    UPROPERTY(EditAnywhere, Category = "Static Mesh")
    UStaticMesh* playerStaticMesh;

    UMainPlayerMovementComponent* OurMovementComponent;
    UMainPlayerCameraComponent* OurCameraComponent;
};
