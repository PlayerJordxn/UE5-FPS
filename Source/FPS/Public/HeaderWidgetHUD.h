// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HeaderWidgetHUD.generated.h"

/**
 * 
 */

class UTextBlock;
class UButton;

 DECLARE_MULTICAST_DELEGATE_OneParam(FOnButtonClickedSignature, uint8)
 DECLARE_MULTICAST_DELEGATE_OneParam(FOnButtonHoveredSignature, UButton*)
 DECLARE_MULTICAST_DELEGATE_FiveParams(FOnButtonUnhoveredSignature,
 	UButton*		/*Button Hovered*/, 
 	UTextBlock*		/*Button Title*/,
    UTextBlock*		/*Button Description*/,
 	float			/*Scale*/,
 	FColor			/*Button Color*/)

UCLASS()
class FPS_API UHeaderWidgetHUD : public UUserWidget
{
	GENERATED_BODY()

protected:

    void NativeConstruct() override;

public:

    UButton* PlayButton;
    UButton* InventoryButton;
    UButton* AnalyticsButton;
    UButton* SettingsButton;

    void OnPlayButtonClicked();
    void OnInventoryButtonClicked();
    void OnAnalyticsButtonClicked();
    void OnSettingsButtonClicked();

    FOnButtonClickedSignature OnButtonClickedDelegate;
    FOnButtonHoveredSignature OnButtonHoveredDelegate;
    FOnButtonUnhoveredSignature OnButtonUnhoveredDelegate;
};

 UENUM(BlueprintType)
enum class EMainMenuHUD : uint8
{
	Home = 0		UMETA(DisplayName = "Home Menu"),
	Play = 1		UMETA(DisplayName = "Play Menu"),
	Inventory = 2	UMETA(DisplayName = "Inventory Menu"),
	Progression = 3 UMETA(DisplayName = "Progression Menu"),
	Analytics = 4	UMETA(DisplayName = "Analytics Menu"),
	Settings = 5	UMETA(DisplayName = "Settings Menu"),
};
