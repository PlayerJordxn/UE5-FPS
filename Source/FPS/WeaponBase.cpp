// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "FPSCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::AttachWeapon(AFPSCharacter* Character, AActor* WeaponBP)
{
	
	APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	if (PlayerController == nullptr) return;
	
	UEnhancedInputLocalPlayerSubsystem* SubSytem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (SubSytem == nullptr) return;

	SubSytem->AddMappingContext(FireContext, 1);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
	if (EnhancedInputComponent == nullptr) return;

	//Bind fire input
	switch (WeaponFireMode)
	{
	case FireMode::Auto:

		break;
	case FireMode::Bolt:

		break;
	case FireMode::Semi:

		break;

	default:

		break;
	}	
}

