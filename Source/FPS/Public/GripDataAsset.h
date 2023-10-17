// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GripDataAsset.generated.h"

class UAnimationSequence;

UCLASS()
class FPS_API UGripDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* IdlePose;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* AimPose;
	
};
