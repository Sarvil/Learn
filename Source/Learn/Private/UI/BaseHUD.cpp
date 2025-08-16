// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseHUD.h"
#include "UI/BaseHUDWidget.h"
#include "UI/OverlayWidgetController.h"
#include "UI/FloatingStatusBarWidget.h"

UOverlayWidgetController *ABaseHUD::GetUOverlayWidgetController(const FWidgetControllerParams &WCParams)
{
    if (OverlayWidgetController == nullptr)
    {
        OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
        OverlayWidgetController->SetWidgetControllerParams(WCParams);
        return OverlayWidgetController;
    }
    return OverlayWidgetController;
}

void ABaseHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
    checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass failed to Initialize. fill in BP_HUD"));
    checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass failed to Initialize. fill in BP_HUD"));
    UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
    OverlayWidget = Cast<UFloatingStatusBarWidget>(Widget);
    const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
    UOverlayWidgetController* WidgetController = GetUOverlayWidgetController(WidgetControllerParams);
    OverlayWidget->SetWidgetController(WidgetController);
    Widget->AddToViewport();
}