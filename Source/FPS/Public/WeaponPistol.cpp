// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPistol.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"

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

	MuzzleFlashSocket = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Flash Socket"));
	MuzzleFlashSocket->SetupAttachment(Weapon);
	
	MagazineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magazine Mesh"));
	MagazineMesh->SetupAttachment(Weapon, "SOCKET_Magazine");

	GripMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grip Mesh"));
	GripMesh->SetupAttachment(BarrelMesh, "SOCKET_Grip");

}


