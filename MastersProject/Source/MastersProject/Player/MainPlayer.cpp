// Fill out your copyright notice in the Description page of Project Settings.

#include "MastersProject.h"
#include "MainPlayer.h"


// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    //Capsule will be used as the root Component for collision
    UCapsuleComponent* capsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootComponent"));
    capsuleComponent->InitCapsuleSize(2.0f, 20.0f);
    capsuleComponent->SetCollisionProfileName(TEXT("Pawn"));
    RootComponent = capsuleComponent;

    //Setup the visual component of the player
    UStaticMeshComponent* playerVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
    playerVisual->AttachTo(RootComponent);

    //Nullptr Check if we have a mesh set it
    if (playerStaticMesh)
    {
        playerVisual->SetStaticMesh(playerStaticMesh);
    }

    OurMovementComponent = CreateDefaultSubobject<UMainPlayerMovementComponent>(TEXT("CustomMovementComponent"));
    OurMovementComponent->UpdatedComponent = RootComponent;

    OurCameraComponent = CreateDefaultSubobject<UMainPlayerCameraComponent>(TEXT("PlayerCamera"));

    //Take Control of the default player
    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainPlayer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
    InputComponent->BindAxis("PlayerMovementLTY", this, &AMainPlayer::MoveForward);
    InputComponent->BindAxis("PlayerMovementLTX", this, &AMainPlayer::MoveRight);

	Super::SetupPlayerInputComponent(InputComponent);
}

UPawnMovementComponent* AMainPlayer::GetMovementComponent() const
{
    return OurMovementComponent;
}

void AMainPlayer::MoveForward(float AxisValue)
{
    if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
    {
        OurMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
    }
}

void AMainPlayer::MoveRight(float AxisValue)
{
    if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
    {
        OurMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
    }
}

void AMainPlayer::Turn(float AxisXValue)
{
    if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
    {
        OurMovementComponent->AddInputVector(GetActorRightVector() * AxisXValue);
    }
}

