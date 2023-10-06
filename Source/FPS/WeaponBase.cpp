// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "FPSCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


void AWeaponBase::AttachWeapon(AFPSCharacter* Character, AActor* CurrentWeaponActor, AWeaponBase* CurrentWeapon)
{
	OwnerCharacter = Character;
	if (Character == nullptr) return;
	if (Weapon == nullptr) return;

	//Get player controller
	APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	if (PlayerController == nullptr) return;

	//Input subsytem
	UEnhancedInputLocalPlayerSubsystem* SubSytem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (SubSytem == nullptr) return;

	//Add fire mapping context
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
	if (EnhancedInputComponent == nullptr) return;
	SubSytem->AddMappingContext(FireContext, 1);

	//Attach weapon to character weapon socket
	if (CurrentWeaponActor == nullptr) return;
	CurrentWeaponActor->AttachToComponent(
		Character->GetMesh(),
		FAttachmentTransformRules::KeepRelativeTransform,
		"SOCKET_Weapon");

	//Disable collision
	CurrentWeaponActor->SetActorEnableCollision(false);

	//Binds Fire Function
	BindWeaponInput(CurrentWeapon, CurrentWeaponActor, EnhancedInputComponent);

	//Play unholster montage (arm + weapon)
	if (ArmsUnholsterMontage && WeaponUnholsterMontage)
	{
		Character->GetMesh()->GetAnimInstance()->Montage_Play(ArmsUnholsterMontage, 1.0f);
		Weapon->GetAnimInstance()->Montage_Play(WeaponUnholsterMontage, 1.0f);
	}
	
}

void AWeaponBase::BindWeaponInput(AWeaponBase* CurrentWeapon, AActor* CurrentWeaponActor, UEnhancedInputComponent* EnhancedInputComponent)
{
	//Check the weapon fire mode
	UE_LOG(LogTemp, Warning, TEXT("Set Input Begin"));
	switch (CurrentWeapon->FireMode)
	{
	case Semi:
		EnhancedInputComponent->BindAction(CurrentWeapon->FireAction, ETriggerEvent::Started, CurrentWeapon, &AWeaponBase::OnFireSemiAutomatic);
		UE_LOG(LogTemp, Warning, TEXT("Set Input Semi"));

		break;
	case Auto:
		EnhancedInputComponent->BindAction(CurrentWeapon->FireAction, ETriggerEvent::Triggered, CurrentWeapon, &AWeaponBase::OnFireAutomatic);
		break;
	case Bolt:
		EnhancedInputComponent->BindAction(CurrentWeapon->FireAction, ETriggerEvent::Triggered, CurrentWeapon, &AWeaponBase::OnFireAutomatic);
		break;
	case Pump:
		EnhancedInputComponent->BindAction(CurrentWeapon->FireAction, ETriggerEvent::Triggered, CurrentWeapon, &AWeaponBase::OnFireAutomatic);
		break;
	default:
		break;
	}
}

void AWeaponBase::OnFireSemiAutomatic()
{
	if (OwnerCharacter == nullptr) return;
	if (OwnerCharacter->IsShooting()) return;

	OwnerCharacter->bIsShooting = true;
	GetWorld()->GetTimerManager().SetTimer(FireRateHandle, this, &AWeaponPistol::EndFire, GetFireRate(), false);

	FHitResult OutHit;
	FVector CameraLocation;
	FRotator CameraRotation;
	OwnerCharacter->GetController()->GetPlayerViewPoint(CameraLocation, CameraRotation);
	bool RayHit = GetWorld()->LineTraceSingleByChannel(OutHit, CameraLocation, CameraLocation + CameraRotation.Vector() * 7000, ECC_Visibility);
	if (RayHit)
	{
		DrawDebugPoint(GetWorld(), OutHit.Location, 15.f, FColor::Blue, true);
	}

	if (ArmsFireMontage != nullptr)
	{
		UAnimInstance* OwnerAnim = OwnerCharacter->GetMesh()->GetAnimInstance();
		OwnerAnim->Montage_Play(ArmsFireMontage);
	}

	if (WeaponFireMontage != nullptr)
	{
		Weapon->GetAnimInstance()->Montage_Play(WeaponFireMontage);
	}

	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, GetActorLocation());
	}

	if (MuzzleFlash != nullptr)
	{
		FName EmitterName = "Muzzle Flash";
		FVector Location = BarrelMesh->GetRelativeLocation();
		FRotator Rotation = MuzzleFlashSocket->GetRelativeRotation();
		FVector Scale = FVector(0.2f, 0.2f, 0.2f);
		UGameplayStatics::SpawnEmitterAttached(
			MuzzleFlash,
			MuzzleFlashSocket,
			EmitterName,
			Location, Rotation,
			Scale);
	}
}

void AWeaponBase::OnFireAutomatic()
{
}

void AWeaponBase::EndFire()
{
	OwnerCharacter->bIsShooting = false;
}

