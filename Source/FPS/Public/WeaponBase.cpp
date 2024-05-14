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


void AWeaponBase::PlayWeaponUnholsterMontage(AFPSCharacter* Character, AWeaponBase* CurrentWeapon)
{
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

void AWeaponBase::SetupWeaponAttachment(AFPSCharacter* Character, AActor* CurrentWeaponActor)
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
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, Character, &AFPSCharacter::StartFire);
		break;
	case Auto:
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, Character, &AFPSCharacter::StopFire);
	}
}


void AWeaponBase::PlayWeaponSFX(const UWorld* World)
{
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(World, FireSound, GetActorLocation());
	}
}

void AWeaponBase::PlayFireMontages(AFPSCharacter* OwnerCharacter)
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




