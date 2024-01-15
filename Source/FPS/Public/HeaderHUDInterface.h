// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HeaderHUDInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHeaderHUDInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FPS_API IHeaderHUDInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/*UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void Hovered(class UHeaderButton* HoveredButton) ;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void Clicked(class UHeaderButton* HoveredButton);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void Unhovered(class UHeaderButton* HoveredButton);*/

};
