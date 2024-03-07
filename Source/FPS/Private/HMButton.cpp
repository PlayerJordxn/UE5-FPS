// Fill out your copyright notice in the Description page of Project Settings.


#include "HMButton.h"
#include "Components/Button.h"

void UHMButton::NativeConstruct()
{
	Super::NativeConstruct();

	/*if (MainButton)
	{
		MainButton->OnClicked.AddDynamic(this, &UHMButton::OnClickedNotify);
		MainButton->OnHovered.AddDynamic(this, &UHMButton::OnHoveredNotify);
		MainButton->OnUnhovered.AddDynamic(this, &UHMButton::OnUnhoveredNotify);
	}*/
}

void UHMButton::OnClickedNotify()
{
	OnClickedDelegate.Broadcast(this);
}

void UHMButton::OnHoveredNotify()
{
	OnHoveredDelegate.Broadcast(this);
}

void UHMButton::OnUnhoveredNotify()
{
	OnUnhoveredDelegate.Broadcast(this);
}

