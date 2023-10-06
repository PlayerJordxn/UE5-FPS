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

void AWeaponBase::AttachWeapon(AFPSCharacter* Character, AActor* CurrentWeaponActor, AWeaponBase* CurrentWeapon)
{
	AWeaponBase* WeaponBase = Cast<AWeaponBase>(CurrentWeaponActor);

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
	BindWeaponInput(CurrentWeaponActor, EnhancedInputComponent);

	//Play unholster montage (arm + weapon)
	if (ArmsUnholsterMontage && WeaponUnholsterMontage)
	{
		Character->GetMesh()->GetAnimInstance()->Montage_Play(ArmsUnholsterMontage, 1.0f);
		Weapon->GetAnimInstance()->Montage_Play(WeaponUnholsterMontage, 1.0f);
	}
	
}

void AWeaponBase::BindWeaponInput(AActor* CurrentWeaponActor, UEnhancedInputComponent* EnhancedInputComponent)
{

	//Check the weapon
	switch (WeaponType)
	{
	case Rifle:

		break;
	case Pistol:

		if (AWeaponPistol* Pistol = Cast<AWeaponPistol>(CurrentWeaponActor))
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

