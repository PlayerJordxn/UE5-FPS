/* HOME MENU BUTTONS INTERACTION*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HMButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHMButtonClickedSignature, class UHMButton*, Button);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHMButtonHoveredSignature, class UHMButton*, Button);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHMButtonUnhoveredSignature, class UHMButton*, Button);

UCLASS()
class FPS_API UHMButton : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

public:

	UPROPERTY(BlueprintAssignable)
	FOnHMButtonClickedSignature OnClickedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnHMButtonHoveredSignature OnHoveredDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnHMButtonUnhoveredSignature OnUnhoveredDelegate;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* MainButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MainText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MainDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MenuIndex;

	UFUNCTION()
	void OnClickedNotify();

	UFUNCTION()
	void OnHoveredNotify();

	UFUNCTION()
	void OnUnhoveredNotify();


	
};
