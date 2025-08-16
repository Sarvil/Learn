// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseHUDWidget.generated.h"

class UFloatingStatusBarWidget;
class UOverlayWidgetController;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class LEARN_API UBaseHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMaxHealth(float MaxHealth);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentHealth(float CurrentHealth);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetHealthRegenRate(float HealthRegenRate);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetHealthPercentage(float HealthPercentage);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMaxMana(float MaxMana);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentMana(float CurrentMana);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetManaRegenRate(float ManaRegenRate);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetManaPercentage(float ManaPercentage);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMaxStamina(float MaxStamina);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentStamina(float CurrentStamina);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetStaminaRegenRate(float StaminaRegenRate);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetStaminaPercentage(float StaminaPercentage);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCharacterLevel(int32 CharacterLevel);

};
