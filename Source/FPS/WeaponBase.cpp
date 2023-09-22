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

void AWeaponBase::AttachWeapon(AFPSCharacter* Character, AWeaponBase* CurrentWeapon, AActor* WeaponActor)
{

	if (Character == nullptr) return;
	if (Weapon == nullptr) return;

	//Get player controller
	APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	if (PlayerController == nullptr) return;

	//Get subsytem
	UEnhancedInputLocalPlayerSubsystem* SubSytem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (SubSytem == nullptr) return;

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
	if (EnhancedInputComponent == nullptr) return;

	//Add fire mapping context
	SubSytem->AddMappingContext(FireContext, 1);

	if (WeaponActor == nullptr) return;
	//Attach weapon to character weapon socket
	WeaponActor->AttachToComponent(
		Character->GetMesh(),
		FAttachmentTransformRules::KeepRelativeTransform,
		"SOCKET_Weapon");

	//Disable collision
	WeaponActor->SetActorEnableCollision(false);

	EFireMode WeaponFireMode = CurrentWeapon->FireMode;
	switch (WeaponFireMode)
	{
	case Auto:

		break;
	case Semi:

		if (AWeaponPistol* Pistol = Cast<AWeaponPistol>(CurrentWeapon))
		{
			EnhancedInputComponent->BindAction(Pistol->FireAction, ETriggerEvent::Started, Pistol, &AWeaponPistol::OnFire);
			Pistol->OwnerCharacter = Character;
		}

		break;
	case Bolt:

		break;
	case Pump:

		break;
	default:
		break;
	}

	
}

void AWeaponBase::StopFire()
{
	OwnerCharacter->bIsShooting = false;
}

