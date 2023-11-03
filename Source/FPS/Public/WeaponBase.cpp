// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "FPSCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "WeaponPistol.h"
#include "Kismet/GameplayStatics.h"
#include "GripDataAsset.h"
// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AWeaponBase::AttachWeapon(AFPSCharacter* Character, AActor* CurrentWeaponActor, AWeaponBase* CurrentWeapon)
{
	OwnerCharacter = Character;
	Character->CurrentWeapon = CurrentWeapon;

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
		"ik_hand_gun");

	//Disable collision
	CurrentWeaponActor->SetActorEnableCollision(false);

	//Binds Fire Function
	BindWeaponInput(CurrentWeaponActor, CurrentWeapon, EnhancedInputComponent);

	//Play unholster montage (arm + weapon)
	if (ArmsUnholsterMontage != nullptr)
	{
		Character->GetMesh()->GetAnimInstance()->Montage_Play(ArmsUnholsterMontage, 1.0f);
	}
	if (WeaponUnholsterMontage != nullptr)
	{
		CurrentWeapon->Weapon->GetAnimInstance()->Montage_Play(WeaponUnholsterMontage, 1.0f);
	}

	
}

void AWeaponBase::BindWeaponInput(AActor* CurrentWeaponActor, AWeaponBase* CurrentWeapon, UEnhancedInputComponent* EnhancedInputComponent)
{
	/* Bind Fire Mode */
	switch (CurrentWeapon->GetFireMode())
	{
	case Semi:
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AWeaponBase::OnFirePressed);
		break;
	case Auto:
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AWeaponBase::OnFirePressed);
	}
	


}

/* Fire Weapon */
void AWeaponBase::OnFirePressed()
{
	if (OwnerCharacter == nullptr) return;
	if (OwnerCharacter->IsShooting()) return;

	OwnerCharacter->bIsShooting = true;
	GetWorld()->GetTimerManager().SetTimer(FireRateHandle, this, &AWeaponBase::OnFireRelased, GetFireRate());

	/* Shoot */
	FHitResult OutHit;
	FVector CameraLocation;
	FRotator CameraRotation;
	OwnerCharacter->GetController()->GetPlayerViewPoint(CameraLocation, CameraRotation);
	bool RayHit = GetWorld()->LineTraceSingleByChannel(OutHit, CameraLocation, CameraLocation + CameraRotation.Vector() * 7000, ECC_Visibility);
	if (RayHit)
	{
		DrawDebugPoint(GetWorld(), OutHit.Location, 15.f, FColor::Blue, true);
	}

	/* Animation */
	if (ArmsFireMontage != nullptr)
	{
		UAnimInstance* OwnerAnim = OwnerCharacter->GetMesh()->GetAnimInstance();
		UAnimMontage* CurrentMontageToPlay;

		CurrentMontageToPlay = OwnerCharacter->bIsAiming ? ArmsAimFireMontage : ArmsFireMontage;
		OwnerAnim->Montage_Play(CurrentMontageToPlay, 1.0f);
	}

	if (WeaponFireMontage != nullptr)
	{
		Weapon->GetAnimInstance()->Montage_Play(WeaponFireMontage, 1.0f);
	}

	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, GetActorLocation());
	}

	if (MuzzleFlash != nullptr)
	{
		FName EmitterName = "Muzzle Flash";
		FVector Location = ForestockMesh->GetSocketLocation("SOCKET_Muzzle");
		FRotator Rotation = ForestockMesh->GetSocketRotation("SOCKET_Muzzle");
		FVector Scale = FVector(0.2f, 0.2f, 0.2f);
		UGameplayStatics::SpawnEmitterAttached(
			MuzzleFlash,
			MuzzleFlashSocket,
			EmitterName,
			Location, Rotation,
			Scale);
	}
}

/* End Firing Weapon */
void AWeaponBase::OnFireRelased()
{
	OwnerCharacter->bIsShooting = false;
}



