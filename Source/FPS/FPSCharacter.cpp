// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSCharacter.h"
#include "FPSProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "WeaponBase.h"

AFPSCharacter::AFPSCharacter()
{
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->bUsePawnControlRotation = false;

	MeshPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Mesh Pivot"));
	MeshPivot->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	MeshPivot->SetupAttachment(FirstPersonCameraComponent);
	GetMesh()->SetupAttachment(MeshPivot);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
}

void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitalizeInput();
	InitalizeWeapon();

	
}

void AFPSCharacter::InitalizeInput()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
			if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
			{
				//Jumping
				if (bEnableJumping)
				{
					EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
					EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
				}

				//Moving
				if (bEnableMovement)
				{
					EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Move);
				}

				if (bEnableSprinting)
				{
					EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AFPSCharacter::StartSprint);
					EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AFPSCharacter::StopSprint);
				}
			}
		}
	}
}

void AFPSCharacter::InitalizeWeapon()
{
	if (CurrentWeapon != nullptr)
	{
		AActor* WeaponActor = GetWorld()->SpawnActor(CurrentWeapon);
		if (AWeaponBase* Weapon = Cast<AWeaponBase>(WeaponActor))
		{
			Weapon->AttachWeapon(this, WeaponActor, Weapon);
		}

	}
}

void AFPSCharacter::DisablePlayerInput()
{

}

void AFPSCharacter::EnablePlayerInput()
{
}

void AFPSCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Look);

		//Aiming
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &AFPSCharacter::StartAim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AFPSCharacter::StopAim);
	}
}


void AFPSCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FVector ForwardDirection = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	const FVector RightDirection= FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AFPSCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		FRotator Rotation = GetFirstPersonCameraComponent()->GetRelativeRotation();
		FRotator RotationOffset = FRotator(FMath::Clamp(Rotation.Pitch + -LookAxisVector.Y, -90.f, 90.f), Rotation.Yaw, Rotation.Roll);
		GetFirstPersonCameraComponent()->SetRelativeRotationExact(RotationOffset);
	}
}

void AFPSCharacter::StartAim(const FInputActionValue& Value)
{
	bIsAiming = true;
}

void AFPSCharacter::StopAim(const FInputActionValue& Value)
{
	bIsAiming = false;
}

void AFPSCharacter::StartSprint(const FInputActionValue& Value)
{
	bIsSprinting = true;
}

void AFPSCharacter::StopSprint(const FInputActionValue& Value)
{
	bIsSprinting = false;
}

