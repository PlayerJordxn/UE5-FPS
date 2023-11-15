// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "FPSCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "WeaponPistol.h"
#include "Kismet/GameplayStatics.h"
#include "GripDataAsset.h"
#include "Camera/CameraComponent.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AWeaponBase::OnFirePressed()
{
	if (OwnerCharacter == nullptr) return;
	if (OwnerCharacter->IsShooting()) return;

	/* Fire Rate */
	UWorld* const World = GetWorld();
	OwnerCharacter->bIsShooting = true;
	World->GetTimerManager().SetTimer(FireRateHandle, this, &AWeaponBase::OnFireRelased, GetFireRate());

	/* Shoot */
	FHitResult OutHit;
	FVector CameraLocation;
	FRotator CameraRotation;
	OwnerCharacter->GetController()->GetPlayerViewPoint(CameraLocation, CameraRotation);
	bool RayHit = World->LineTraceSingleByChannel(OutHit, CameraLocation, CameraLocation + CameraRotation.Vector() * 100000, ECC_Visibility);
	if (RayHit)
	{
		DrawDebugSphere(World, OutHit.Location, 15.f, 16, FColor::Blue, true);
	}

	OnShoot.Broadcast();
}

/* End Firing Weapon */
void AWeaponBase::OnFireRelased()
{
	OwnerCharacter->bIsShooting = false;
}

void AWeaponBase::AttachWeapon(AFPSCharacter* Character, AActor* CurrentWeaponActor, AWeaponBase* CurrentWeapon)
{
	OwnerCharacter = Character;
	OwnerCharacter->CurrentWeapon = CurrentWeapon;
	UWorld* const World = GetWorld();

	if (CurrentWeaponActor == nullptr) return;
	if (OwnerCharacter == nullptr) return;
	if (CurrentWeaponActor == nullptr) return;
	if (CurrentWeapon == nullptr) return;
	if (World == nullptr) return;

	SetupWeaponAttachment(CurrentWeaponActor, Character);
	SetupWeaponInput(OwnerCharacter, CurrentWeaponActor, CurrentWeapon);
	SetupWeaponVFX(CurrentWeapon);
	SetupWeaponAnimations(World, OwnerCharacter, CurrentWeapon);

	World->GetTimerManager().SetTimer(FireRateHandle, this, &AWeaponBase::SetDesiredWeaponRotation, 0.2f, true);

	//Play unholster montage (arm + weapon)
	if (ArmsUnholsterMontage != nullptr)
	{
		Character->GetMesh()->GetAnimInstance()->Montage_Play(ArmsUnholsterMontage, 1.0f);
	}

	if (WeaponUnholsterMontage != nullptr)
	{
		CurrentWeapon->WeaponBody->GetAnimInstance()->Montage_Play(WeaponUnholsterMontage, 1.0f);
	}
}

void AWeaponBase::SetupWeaponAttachment(AActor* CurrentWeaponActor, AFPSCharacter* Character)
{
	CurrentWeaponActor->AttachToComponent(
		Character->GetMesh(),
		FAttachmentTransformRules::KeepRelativeTransform,
		"ik_hand_gun");
}

void AWeaponBase::SetupWeaponInput(AFPSCharacter* Character, AActor* CurrentWeaponActor, AWeaponBase* CurrentWeapon)
{
	/* Setup Weapon Input */
	APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	if (PlayerController == nullptr) return;

	UEnhancedInputLocalPlayerSubsystem* SubSytem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (SubSytem == nullptr) return;

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
	if (EnhancedInputComponent == nullptr) return;
	SubSytem->AddMappingContext(FireContext, 1);

	CurrentWeaponActor->SetActorEnableCollision(false);

	switch (CurrentWeapon->GetFireMode())
	{
	case Semi:
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AWeaponBase::OnFirePressed);
		break;
	case Auto:
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AWeaponBase::OnFirePressed);
	}
}

void AWeaponBase::SetupWeaponVFX(AWeaponBase* CurrentWeapon)
{
	if (bHasMuzzle)
	{
		OnShoot.AddUObject(this, &AWeaponBase::SpawnMuzzleFlash);
	}
}

void AWeaponBase::SetupWeaponAnimations(UWorld* const& World, AFPSCharacter* Character, AWeaponBase* CurrentWeapon)
{
	OnShoot.AddUObject(this, &AWeaponBase::PlayFireMontages);
	OnShoot.AddUObject(this, &AWeaponBase::PlayWeaponSFX);
}

void AWeaponBase::PlayWeaponSFX()
{
	UWorld* const& World = GetWorld();
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(World, FireSound, GetActorLocation());
	}
}

void AWeaponBase::SetDesiredWeaponRotation()
{
	float WeaponSwayX = OwnerCharacter->GetControlRotation().Yaw;
	float WeaponSwayY = OwnerCharacter->GetFirstPersonCameraComponent()->GetRelativeRotation().Pitch;
	WeaponSwayRotation = FRotator(WeaponSwayX, WeaponSwayY, 0);
}

void AWeaponBase::PlayFireMontages()
{
	if (ArmsFireMontage != nullptr)
	{
		UAnimInstance* OwnerAnim = OwnerCharacter->GetMesh()->GetAnimInstance();
		UAnimMontage* CurrentMontageToPlay;

		CurrentMontageToPlay = OwnerCharacter->bIsAiming ? ArmsAimFireMontage : ArmsFireMontage;
		OwnerAnim->Montage_Play(CurrentMontageToPlay, 1.0f);
	}

	if (WeaponFireMontage != nullptr)
	{
		WeaponBody->GetAnimInstance()->Montage_Play(WeaponFireMontage, 1.0f);
	}
}

void AWeaponBase::SpawnMuzzleFlash()
{
	if (MuzzleFlash != nullptr)
	{
		FName SocketName = "SOCKET_Muzzle";
		FVector Location = BarrelMesh->GetRelativeLocation();
		FRotator Rotation = BarrelMesh->GetRelativeRotation();
		Rotation.Yaw = Rotation.Yaw + 90.f;
		FVector Scale = FVector(.1f, .1f, .1f);
		UGameplayStatics::SpawnEmitterAttached(
			MuzzleFlash,
			BarrelMesh,
			SocketName,
			Location, Rotation,
			Scale);
	}
}




