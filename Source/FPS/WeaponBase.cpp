// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "FPSCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "WeaponPistol.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AWeaponBase::AttachWeapon(AFPSCharacter* Character, AActor* WeaponToEquip, EWeaponType WeaponType)
{
	AWeaponBase* WeaponBase = Cast<AWeaponBase>(WeaponToEquip);

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
	if (WeaponToEquip == nullptr) return;
	WeaponToEquip->AttachToComponent(
		Character->GetMesh(),
		FAttachmentTransformRules::KeepRelativeTransform,
		"SOCKET_Weapon");

	//Disable collision
	WeaponToEquip->SetActorEnableCollision(false);

	//Check the weapon
	switch (WeaponType)
	{
	case Rifle:

		break;
	case Pistol:

		if (AWeaponPistol* Pistol = Cast<AWeaponPistol>(WeaponToEquip))
		{
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, Pistol, &AWeaponPistol::OnFire);
		}

		break;
	case Sniper:
		break;
	case Shotgun:
		break;
	default:
		break;
	}
	
}

void AWeaponBase::StopFire()
{
	OwnerCharacter->bIsShooting = false;
}

