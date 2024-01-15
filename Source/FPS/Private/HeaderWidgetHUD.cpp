// Fill out your copyright notice in the Description page of Project Settings.


#include "HeaderWidgetHUD.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"

void UHeaderWidgetHUD::NativeConstruct()
{
	Super::NativeConstruct();

	//PlayButton->OnClicked.AddDynamic(this, &UHeaderWidgetHUD::OnClickedEvent);
	//PlayButton->OnHovered.AddDynamic(this, &UHeaderWidgetHUD::OnHoveredEvent);
	//PlayButton->OnUnhovered.AddDynamic(this, &UHeaderWidgetHUD::OnUnhoveredEvent);

}

void UHeaderWidgetHUD::OnClickedEvent()
{
	//OnButtonClickedDelegate.Broadcast(PlayButton);
}

void UHeaderWidgetHUD::OnHoveredEvent()
{
	//OnButtonHoveredDelegate.Broadcast(PlayButton);
}

void UHeaderWidgetHUD::OnUnhoveredEvent()
{
	//OnButtonUnhoveredDelegate.Broadcast(PlayButton);
}
