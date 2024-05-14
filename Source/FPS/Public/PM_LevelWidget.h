// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PM_LevelWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPMButtonClickedSignature, class UPM_LevelWidget*, Button);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPMButtonHoveredSignature, class UPM_LevelWidget*, Button);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPMButtonUnhoveredSignature, class UPM_LevelWidget*, Button);

UCLASS()
class FPS_API UPM_LevelWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	//UPROPERTY(BlueprintAssignable)
	//FOnPMButtonClickedSignature OnClickedDelegate;
	//
	//UPROPERTY(BlueprintAssignable)
	//FOnPMButtonClickedSignature OnClickedDelegate;

	//UPROPERTY(BlueprintAssignable)
	//FOnPMButtonClickedSignature OnClickedDelegate;

};
