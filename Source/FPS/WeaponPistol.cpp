// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPistol.h"
#include "FPSCharacter.h"
AWeaponPistol::AWeaponPistol()
{
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(RootComponent);

	ForestockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Forestock Mesh"));
	ForestockMesh->SetupAttachment(Weapon, "SOCKET_Slide");

	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel Mesh"));
	BarrelMesh->SetupAttachment(Weapon, "SOCKET_Default");
}

void AWeaponPistol::BeginPlay()
{
}

void AWeaponPistol::Tick(float DeltaTime)
{
}

void AWeaponPistol::OnFire()
{	
	UE_LOG(LogTemp, Warning, TEXT("Shot Fired"));
	if (OwnerCharacter != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Shot Fired #2"));
		UAnimInstance* OwnerAnim = OwnerCharacter->GetMesh()->GetAnimInstance();
		if (OwnerAnim)
		{
			UE_LOG(LogTemp, Warning, TEXT("Shot Fired #3"));
			OwnerAnim->Montage_Play(FireMontage, 1.0f);
			OwnerCharacter->bIsShooting = true;
			GetWorld()->GetTimerManager().SetTimer(FireRateHandle, this, &AWeaponPistol::StopFire, FireRate, false);
		}
	}
	
}


