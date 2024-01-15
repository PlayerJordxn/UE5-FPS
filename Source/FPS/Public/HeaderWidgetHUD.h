// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Delegates/Delegate.h"
#include "HeaderWidgetHUD.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class FPS_API UHeaderWidgetHUD : public UUserWidget
{
	GENERATED_BODY()

protected:

    virtual void NativeConstruct() override;

public:

	//TArray<>

    void OnClickedEvent();
    void OnHoveredEvent();
    void OnUnhoveredEvent();



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
