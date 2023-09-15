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
	if (WeaponActor == nullptr) return;

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

	//Attach weapon to character weapon socket
	WeaponActor->AttachToComponent(
		Character->GetMesh(), 
		FAttachmentTransformRules::KeepRelativeTransform, 
		"SOCKET_Weapon");


	switch (CurrentWeapon->WeaponType)
	{
		case Rifle:

			break;
		case Pistol:
		
			if (AWeaponPistol* Pistol = Cast<AWeaponPistol>(Weapon))
			{
				//EnhancedInputComponent->BindAction(Pistol->FireAction, ETriggerEvent::Started, Pistol, &AWeaponPistol::OnFire);
			}

			break;
		case Sniper:

			break;
		default:
			break;
	}
	
}

