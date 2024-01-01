// Fill out your copyright notice in the Description page of Project Settings.


#include "HeaderWidgetHUD.h"
#include "Components/Button.h"

void UHeaderWidgetHUD::NativeConstruct()
{
	Super::NativeConstruct();

	PlayButton->OnClicked.AddUniqueDynamic(this, &UHeaderWidgetHUD::OnPlayButtonClicked);
	InventoryButton->OnClicked.AddUniqueDynamic(this, &UHeaderWidgetHUD::OnInventoryButtonClicked);
	AnalyticsButton->OnClicked.AddUniqueDynamic(this, &UHeaderWidgetHUD::OnAnalyticsButtonClicked);
	SettingsButton->OnClicked.AddUniqueDynamic(this, &UHeaderWidgetHUD::OnSettingsButtonClicked);
}

void UHeaderWidgetHUD::OnPlayButtonClicked()
{
	OnButtonClickedDelegate.Broadcast((uint32)EMainMenuHUD::Play);
}

void UHeaderWidgetHUD::OnInventoryButtonClicked()
{
	OnButtonClickedDelegate.Broadcast((uint32)EMainMenuHUD::Inventory);
}

void UHeaderWidgetHUD::OnAnalyticsButtonClicked()
{
	OnButtonClickedDelegate.Broadcast((uint32)EMainMenuHUD::Analytics);
}

void UHeaderWidgetHUD::OnSettingsButtonClicked()
{
	OnButtonClickedDelegate.Broadcast((uint32)EMainMenuHUD::Settings);
}

