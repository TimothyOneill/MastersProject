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
    //TODO Change to get Sm size
    capsuleComponent->InitCapsuleSize(40.0f, 150.0f);
    capsuleComponent->SetCollisionProfileName(TEXT("Pawn"));
    RootComponent = capsuleComponent;
  
    //Setup the visual component of the player
    playerVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
    playerVisual->AttachTo(RootComponent);

    //Nullptr Check if we have a mesh set it
    if (playerStaticMesh)
    {
        playerVisual->SetStaticMesh(playerStaticMesh);
    }

    OurMovementComponent = CreateDefaultSubobject<UMainPlayerMovementComponent>(TEXT("CustomMovementComponent"));
    OurMovementComponent->UpdatedComponent = RootComponent;

    OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("DefaultSpringArmComponent"));
    OurCameraSpringArm->AttachTo(RootComponent);
    OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 40.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
    OurCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("DefaultCameraComponent"));
    OurCameraComponent->AttachTo(OurCameraSpringArm, USpringArmComponent::SocketName);

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
    InputComponent->BindAxis("PlayerMovementLTY", this, &AMainPlayer::MoveY);
    InputComponent->BindAxis("PlayerMovementLTX", this, &AMainPlayer::MoveX);
    InputComponent->BindAxis("PlayerMovementRTY", this, &AMainPlayer::TurnCameraY);
    InputComponent->BindAxis("PlayerMovementRTX", this, &AMainPlayer::TurnCameraX);

	Super::SetupPlayerInputComponent(InputComponent);
}

UPawnMovementComponent* AMainPlayer::GetMovementComponent() const
{
    return OurMovementComponent;
}

void AMainPlayer::MoveY(float AxisYValue)
{ 
    if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
    {
        OurMovementComponent->AddInputVector(GetActorForwardVector() * AxisYValue);
    }
}

void AMainPlayer::MoveX(float AxisXValue)
{
    if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
    {
        OurMovementComponent->AddInputVector(GetActorRightVector() * AxisXValue);
    }
}

void AMainPlayer::TurnCameraY(float AxisYValue)
{  
    FRotator NewRotation = OurCameraSpringArm->GetComponentRotation();
    NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + AxisYValue, -80.0f, 80.0f);
    OurCameraSpringArm->SetWorldRotation(NewRotation);
}

void AMainPlayer::TurnCameraX(float AxisXValue)
{
    FRotator NewRotation = GetActorRotation();
    NewRotation.Yaw += AxisXValue;
    SetActorRotation(NewRotation);
}
