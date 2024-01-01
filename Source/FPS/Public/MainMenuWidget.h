// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

UCLASS()
class FPS_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	void NativeConstruct() override;

public:

	class UHeaderWidgetHUD* HeaderWidget;

};

//UENUM(BlueprintType)
//enum class EMainMenuHUD : uint8
//{
//	Home = 0		UMETA(DisplayName = "Home Menu"),
//	Play = 1		UMETA(DisplayName = "Play Menu"),
//	Inventory = 2	UMETA(DisplayName = "Inventory Menu"),
//	Progression = 3 UMETA(DisplayName = "Progression Menu"),
//	Analytics = 4	UMETA(DisplayName = "Analytics Menu"),
//	Settings = 5	UMETA(DisplayName = "Settings Menu"),
//};