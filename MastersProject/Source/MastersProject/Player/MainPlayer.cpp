#include "MastersProject.h"
#include "MainPlayer.h"
#include "IHeadMountedDisplay.h"

AMainPlayer::AMainPlayer()
{
    //Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    //Capsule will be used as the root Component for collision
    UCapsuleComponent* CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootComponent"));
    CapsuleComponent->InitCapsuleSize(60.0f, 150.0f);
    CapsuleComponent->SetCollisionProfileName(TEXT("Pawn"));
    RootComponent = CapsuleComponent;

    //Setup the visual component of the player
    PlayerVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
    PlayerVisual->AttachTo(RootComponent);

    //Nullptr Check if we have a mesh set it
    if (PlayerStaticMesh)
    {
        PlayerVisual->SetStaticMesh(PlayerStaticMesh);
    }

    OurMovementComponent = CreateDefaultSubobject<UMainPlayerMovementComponent>(TEXT("CustomMovementComponent"));
    OurMovementComponent->UpdatedComponent = RootComponent;

    OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("DefaultSpringArmComponent"));
    OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 80.0f), FRotator(0.0f, 0.0f, 0.0f));
    OurCameraSpringArm->TargetArmLength = 0.0f;
    OurCameraSpringArm->AttachTo(RootComponent);

    OurCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("DefaultCameraComponent"));
    OurCameraComponent->AttachTo(OurCameraSpringArm, USpringArmComponent::SocketName);

    //Take Control of the default player
    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

//Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
    if (GEngine->HMDDevice.IsValid() && GEngine->HMDDevice->IsStereoEnabledOnNextFrame())
    {
        OurCameraSpringArm->DestroyComponent();
        OurCameraComponent->DestroyComponent();
    }
    Super::BeginPlay();
}

//Called every frame
void AMainPlayer::Tick( float DeltaTime )
{
    //If we have a Oculus Attached and enabled allow rotational movement with the Oculus.
    if (GEngine->HMDDevice.IsValid() && GEngine->HMDDevice->IsStereoEnabled())
    {
        TurnOculus();
    }
    Super::Tick( DeltaTime );
}

//Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
    InputComponent->BindAxis("PlayerMovementLTY", this, &AMainPlayer::MoveY);
    InputComponent->BindAxis("PlayerMovementLTX", this, &AMainPlayer::MoveX);

    //When setting up the users input if the Oculus movement Disable head movement on the right joystick.
    if (GEngine->HMDDevice.IsValid() && !GEngine->HMDDevice->IsStereoEnabledOnNextFrame())
    {
        InputComponent->BindAxis("PlayerMovementRTY", this, &AMainPlayer::TurnCameraY);
        InputComponent->BindAxis("PlayerMovementRTX", this, &AMainPlayer::TurnCameraX);
    }
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

// Gets the HMD's current rotation and applys it the the player moveing it and its sub components.
// Oculus handles users viewport seperatly elsewhere in the engine.
void AMainPlayer::TurnOculus()
{
    FQuat HMDOrientation;
    FVector HMDPosition;

    GEngine->HMDDevice->GetCurrentOrientationAndPosition(HMDOrientation, HMDPosition);

    FRotator NewViewRotation = GetActorRotation();
    NewViewRotation.Yaw = HMDOrientation.Rotator().Yaw;
    SetActorRotation(NewViewRotation);
}