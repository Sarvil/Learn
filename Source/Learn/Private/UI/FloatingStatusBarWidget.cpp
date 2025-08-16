// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FloatingStatusBarWidget.h"

void UFloatingStatusBarWidget::SetWidgetController(UObject* InWidgetController)
{
    WidgetController = InWidgetController;
    WidgetControllerSet();
}
