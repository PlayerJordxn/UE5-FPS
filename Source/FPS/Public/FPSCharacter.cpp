// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "WeaponBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AFPSCharacter::AFPSCharacter()
{
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	LeanPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Lean Pivot"));
	LeanPivot->SetupAttachment(GetCapsuleComponent());
	LeanPivot->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(LeanPivot);
	FirstPersonCameraComponent->bUsePawnControlRotation = false;

	MeshPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Mesh Pivot"));
	MeshPivot->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	MeshPivot->SetupAttachment(FirstPersonCameraComponent);

	GetMesh()->SetupAttachment(MeshPivot);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
}

void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitalizeWeapon();
	ToggleInput();
}

void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSCharacter::InitalizeWeapon()
{
	AActor* WeaponActor = GetWorld()->SpawnActor(SelectedWeapon);
	CurrentWeapon = Cast<AWeaponBase>(WeaponActor);

	if (CurrentWeapon != nullptr && SelectedWeapon != nullptr)
	{
		CurrentWeapon->SetupWeaponAttachment(this, WeaponActor);
		CurrentWeapon->SetupWeaponInput(this, WeaponActor, CurrentWeapon);
		CurrentWeapon->PlayWeaponUnholsterMontage(this, CurrentWeapon);
	}
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

		//Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AFPSCharacter::StartFire);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &AFPSCharacter::StopFire);

		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &AFPSCharacter::StartReload);

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
	FVector2D LookAxisVector = Value.Get<FVector2D>() * SensitivityMultiplier;

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
	OnAimStart();
}

void AFPSCharacter::StopAim(const FInputActionValue& Value)
{
	OnAimEnd();
}
void AFPSCharacter::StartCrouch(const FInputActionValue& Value)
{
	OnCrouchBegin();
}

void AFPSCharacter::StopCrouch(const FInputActionValue& Value)
{
	OnCrouchFinished();
}

void AFPSCharacter::StartFire(const FInputActionValue& Value)
{

	if (bIsReloading) return;
	if (IsShooting()) return;

	UWorld* const World = GetWorld();


	if (IsSprinting())
	{
		OnSprintEnd();
		bIsShooting = true;
		World->GetTimerManager().SetTimer(CurrentWeapon->ShootDelayHandle, this, &AFPSCharacter::ShootRay, CurrentWeapon->GetShootDelay());
		World->GetTimerManager().SetTimer(CurrentWeapon->FireRateHandle, this, &AFPSCharacter::StopFire, CurrentWeapon->GetFireRate());
	}
	else
	{
		/* Fire Rate */
		bIsShooting = true;
		World->GetTimerManager().SetTimer(CurrentWeapon->FireRateHandle, this, &AFPSCharacter::StopFire, CurrentWeapon->GetFireRate());
		ShootRay();
	}
	
}

void AFPSCharacter::ShootRay()
{
	UWorld* const World = GetWorld();


	/* Shoot */
	FHitResult OutHit;
	FVector CameraLocation;
	FRotator CameraRotation;

	//Get Center Screen 
	GetController()->GetPlayerViewPoint(CameraLocation, CameraRotation);

	bool RayHit = World->LineTraceSingleByChannel(OutHit, CameraLocation, CameraLocation + CameraRotation.Vector() * 100000, ECC_Visibility);
	if (RayHit)
	{
		DrawDebugSphere(World, OutHit.Location, 15.f, 16, FColor::Blue, true);
	}


	//CurrentWeapon->SpawnMuzzleFlash();
	CurrentWeapon->PlayFireMontages(this);
	CurrentWeapon->PlayWeaponSFX(World);
}

/* End Firing Weapon */
void AFPSCharacter::StopFire()
{
	bIsShooting = false;
}

void AFPSCharacter::StartJump(const FInputActionValue& Value)
{
	bPressedJump = true;
	OnSprintEnd();
}

void AFPSCharacter::StopJump(const FInputActionValue& Value)
{
	bPressedJump = false;
}

void AFPSCharacter::StartLeanLeft(const FInputActionValue& Value)
{
	OnLeanLeftBegin();
}

void AFPSCharacter::StartLeanRight(const FInputActionValue& Value)
{
	OnLeanRightBegin();
}

void AFPSCharacter::StopLeanLeft(const FInputActionValue& Value)
{
	OnLeanLeftFinished();
}

void AFPSCharacter::StopLeanRight(const FInputActionValue& Value)
{
	OnLeanRightFinished();
}

void AFPSCharacter::StartSprint(const FInputActionValue& Value)
{
	OnSprintBegin();
}

void AFPSCharacter::StopSprint(const FInputActionValue& Value)
{
	OnSprintEnd();
}

void AFPSCharacter::StartReload(const FInputActionValue& Value)
{
	if (bIsReloading) return;
	OnReloadStart();
}

/*INPUT METHODS*/

void AFPSCharacter::ToggleInput()
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
					EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AFPSCharacter::StartJump);
					EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AFPSCharacter::StopJump);
				}

				//Moving
				if (bEnableMovement)
				{
					EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Move);
				}

				//Sprinting
				if (bEnableSprinting)
				{
					EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AFPSCharacter::StartSprint);
					EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AFPSCharacter::StopSprint);
				}

				//Crouching
				if (bEnableCrouching)
				{
					EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AFPSCharacter::StartCrouch);
					EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AFPSCharacter::StopCrouch);
				}

				//Leaning
				if (bEnableLeaning)
				{
					EnhancedInputComponent->BindAction(LeanLeftAction, ETriggerEvent::Started, this, &AFPSCharacter::StartLeanLeft);
					EnhancedInputComponent->BindAction(LeanRightAction, ETriggerEvent::Started, this, &AFPSCharacter::StartLeanRight);

					EnhancedInputComponent->BindAction(LeanLeftAction, ETriggerEvent::Completed, this, &AFPSCharacter::StopLeanLeft);
					EnhancedInputComponent->BindAction(LeanRightAction, ETriggerEvent::Completed, this, &AFPSCharacter::StopLeanRight);
				}

			}
		}
	}


}



