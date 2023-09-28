// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPistol.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"

AWeaponPistol::AWeaponPistol()
{
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(RootComponent);

	ForestockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Forestock Mesh"));
	ForestockMesh->SetupAttachment(Weapon, "SOCKET_Slide");

	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel Mesh"));
	BarrelMesh->SetupAttachment(Weapon, "SOCKET_Default");

	IronSightBackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Iront Sight Back Mesh"));
	IronSightBackMesh->SetupAttachment(Weapon, "SOCKET_Ironsights");

	IronSightFrontMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Iront Sight Front Mesh"));
	IronSightFrontMesh->SetupAttachment(ForestockMesh, "SOCKET_Ironsight_F");
}

void AWeaponPistol::BeginPlay()
{
	Super::BeginPlay();

	APawn* CharacterPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	OwnerCharacter = Cast<AFPSCharacter>(CharacterPawn);
	AttachWeapon(OwnerCharacter, this, FireMode);
}

void AWeaponPistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponPistol::OnFire()
{	
	if (OwnerCharacter != nullptr)
	{
		if (UAnimInstance* OwnerAnim = OwnerCharacter->GetMesh()->GetAnimInstance())
		{
			if (OwnerCharacter->IsShooting() == false)
			{
				OwnerAnim->Montage_Play(FireMontage, 1.0f);
				OwnerCharacter->bIsShooting = true;
				GetWorld()->GetTimerManager().SetTimer(FireRateHandle, this, &AWeaponBase::StopFire, WeaponData.FireRate, false);
			}
			
		}
	}
}


