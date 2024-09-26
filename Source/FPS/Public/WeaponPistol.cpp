// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPistol.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/SpringArmComponent.h"

AWeaponPistol::AWeaponPistol()
{
	WeaponBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	WeaponBody->SetupAttachment(RootComponent);

	ForestockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Forestock Mesh"));
	ForestockMesh->SetupAttachment(WeaponBody, "SOCKET_Slide");

	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel Mesh"));
	BarrelMesh->SetupAttachment(WeaponBody, "SOCKET_Default");

	IronSightBackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Iront Sight Back Mesh"));
	IronSightBackMesh->SetupAttachment(WeaponBody, "SOCKET_Ironsights");

	IronSightFrontMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Iront Sight Front Mesh"));
	IronSightFrontMesh->SetupAttachment(ForestockMesh, "SOCKET_Ironsight_F");

	MagazineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magazine Mesh"));
	MagazineMesh->SetupAttachment(WeaponBody, "SOCKET_Magazine");

	GripMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grip Mesh"));
	GripMesh->SetupAttachment(BarrelMesh, "SOCKET_Grip");

	MagazineReserveMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magazine Reserve Mesh"));
	MagazineReserveMesh->SetupAttachment(WeaponBody, "SOCKET_Magazine_Reserve");
}


