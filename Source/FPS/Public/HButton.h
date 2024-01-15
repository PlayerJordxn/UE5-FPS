// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
/* HEADER MENU BUTTONS INTERACTION*/

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HButton.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHButtonClickedSignature, class UHButton*, Button);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHButtonHoveredSignature, class UHButton*, Button);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHButtonUnhoveredSignature, class UHButton*, Button);

UCLASS()
class FPS_API UHButton : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

public:

	UPROPERTY(BlueprintAssignable)
	FOnHButtonClickedSignature OnClickedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnHButtonHoveredSignature OnHoveredDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnHButtonUnhoveredSignature OnUnhoveredDelegate;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* MainButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MainText;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MenuIndex;
	
	UFUNCTION()
	void OnClickedNotify();

	UFUNCTION()
	void OnHoveredNotify();

	UFUNCTION()
	void OnUnhoveredNotify();

};
