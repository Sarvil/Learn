// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/OverlayWidgetController.h"
#include "AttributeSets/BaseAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
    const UBaseAttributeSet* BaseAttributeSet = CastChecked<UBaseAttributeSet>(AttributeSet);
    OnHealthChanged.Broadcast(BaseAttributeSet->GetHealth());
    OnMaxHealthChanged.Broadcast(BaseAttributeSet->GetMaxHealth());
    OnHealthRegenRateChanged.Broadcast(BaseAttributeSet->GetHealthRegenRate());
    OnManaChanged.Broadcast(BaseAttributeSet->GetMana());
    OnMaxManaChanged.Broadcast(BaseAttributeSet->GetMaxMana());
    OnManaRegenRateChanged.Broadcast(BaseAttributeSet->GetManaRegenRate());
    OnStaminaChanged.Broadcast(BaseAttributeSet->GetStamina());
    OnMaxStaminaChanged.Broadcast(BaseAttributeSet->GetMaxStamina());
    OnStaminaRegenRateChanged.Broadcast(BaseAttributeSet->GetStaminaRegenRate());
    
}