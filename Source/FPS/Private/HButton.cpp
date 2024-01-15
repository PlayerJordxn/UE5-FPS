// Fill out your copyright notice in the Description page of Project Settings.


#include "HButton.h"
#include "Components/Button.h"

void UHButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (MainButton)
	{
		MainButton->OnClicked.AddDynamic(this, &UHButton::OnClickedNotify);
		MainButton->OnHovered.AddDynamic(this, &UHButton::OnHoveredNotify);
		MainButton->OnUnhovered.AddDynamic(this, &UHButton::OnUnhoveredNotify);
	}
}

void UHButton::OnClickedNotify()
{
	OnClickedDelegate.Broadcast(this);
}

void UHButton::OnHoveredNotify()
{
	OnHoveredDelegate.Broadcast(this);
}

void UHButton::OnUnhoveredNotify()
{
	OnUnhoveredDelegate.Broadcast(this);
}
