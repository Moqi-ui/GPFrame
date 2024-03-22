// Copyright Epic Games, Inc. All Rights Reserved.

#include "GPFrameCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/SphereComponent.h"
#include "RotatingActor.h"
#include "Kismet/GameplayStatics.h"
#include "FireEffect.h"
#include "ExplosionEffect.h"
#include "GPFrameGameMode.h"

//////////////////////////////////////////////////////////////////////////
// AGPFrameCharacter

AGPFrameCharacter::AGPFrameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	//20240320
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	SphereComp->SetSphereRadius(200);

	Health = 100;
}

void AGPFrameCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	//FireDelegate.BindUFunction(this, FName("TakeFireDamage"));
	FireDelegate.BindUObject(this, &AGPFrameCharacter::TakeFireDamage);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AGPFrameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGPFrameCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGPFrameCharacter::Look);

	}

	//设置输入键操作，以调用Restart Player
	PlayerInputComponent->BindAction("Restart", IE_Pressed, this, &AGPFrameCharacter::CallRestartPlayer);
}

void AGPFrameCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AGPFrameCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AGPFrameCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (ARotatingActor* RotatingActor = Cast<ARotatingActor>(OtherActor))
	{
		RotatingActor->SetbCanRotator(true);
	}
}
void AGPFrameCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (ARotatingActor* RotatingActor = Cast<ARotatingActor>(OtherActor))
	{
		RotatingActor->SetbCanRotator(false);
	}
}

void AGPFrameCharacter::TakeFireDamage()
{
	if (Health <= 0)
	{
		GetWorld()->SpawnActor<AExplosionEffect>(GetActorLocation(), GetActorRotation());

		CallRestartPlayer();
	}
	else
	{
		Health = Health - 20.0f;
	}

}
void AGPFrameCharacter::IgniteFireTimer()
{
	GetWorldTimerManager().SetTimer(FireTimer, FireDelegate, 0.75, true);
	AActor* TempFireEffect = GetWorld()->SpawnActor<AFireEffect>(GetActorLocation(), GetActorRotation());
	TempFireEffect->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void AGPFrameCharacter::ClearFireTimer()
{
	GetWorldTimerManager().ClearTimer(FireTimer);
}


void AGPFrameCharacter::Destroyed()
{
	Super::Destroyed();

}

void AGPFrameCharacter::CallRestartPlayer()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "AGPFrameCharacter::CallRestartPlayer()");

	// 获得Pawn控制器的引用。
	AController* CortollerRef = GetController();

	//销毁玩家
	Destroy();

	//在世界中获得World和GameMode，以调用其重启玩家函数。
	if (UWorld* World = GetWorld())
	{
		if (AGPFrameGameMode* GameMode = Cast<AGPFrameGameMode>(World->GetAuthGameMode()))
		{
			GameMode->RestartPlayer(CortollerRef);
		}
	}
}