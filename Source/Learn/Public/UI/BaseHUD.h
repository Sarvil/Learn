// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

class UBaseHUDWidget;
class UOverlayWidgetController;
struct FWidgetControllerParams;
class APlayerState;
class APlayerController;
class UAbilitySystemComponent;
class UAttributeSet;
class UFloatingStatusBarWidget;
/**
 * 
 */
UCLASS()
class LEARN_API ABaseHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
	TObjectPtr<UFloatingStatusBarWidget> OverlayWidget;

	UFUNCTION()
	UOverlayWidgetController* GetUOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UFloatingStatusBarWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
