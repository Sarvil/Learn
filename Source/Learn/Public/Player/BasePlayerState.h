// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "BasePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_API ABasePlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
    
    ABasePlayerState();
    
    class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    
    class UBaseAttributeSet* GetBaseAttributeSet() const;
    
    //Attributes
    
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    float GetHealth() const;
    
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    float GetMaxHealth() const;
    
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    float GetHealthRegenRate() const;
    
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    float GetMana() const;
    
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    float GetMaxMana() const;
    
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    float GetManaRegenRate() const;
    
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    float GetStamina() const;
    
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    float GetMaxStamina() const;
    
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    float GetStaminaRegenRate() const;
    
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    float GetArmor() const;
    
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    float GetCharacterLevel() const;
    
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    float GetMoveSpeed() const;
    
protected:
    
    UPROPERTY()
    class UGASAbilitySystemComponent* AbilitySystemComponent;
    
    UPROPERTY()
    class UBaseAttributeSet* BaseAttributeSet;
    
    FDelegateHandle HealthChangedDelegateHandle;
    FDelegateHandle MaxHealthChangedDelegateHandle;
    FDelegateHandle HealthRegenRateChangedDelegateHandle;
    FDelegateHandle ManaChangedDelegateHandle;
    FDelegateHandle MaxManaChangedDelegateHandle;
    FDelegateHandle ManaRegenRateChangedDelegateHandle;
    FDelegateHandle StaminaChangedDelegateHandle;
    FDelegateHandle MaxStaminaChangedDelegateHandle;
    FDelegateHandle StaminaRegenRateChangedDelegateHandle;
    FDelegateHandle CharacterLevelChangedDelegateHandle;

    virtual void BeginPlay() override;

    virtual void HealthChanged(const FOnAttributeChangeData& Data);
    virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
    virtual void HealthRegenRateChanged(const FOnAttributeChangeData& Data);
    virtual void ManaChanged(const FOnAttributeChangeData& Data);
    virtual void MaxManaChanged(const FOnAttributeChangeData& Data);
    virtual void ManaRegenRateChanged(const FOnAttributeChangeData& Data);
    virtual void StaminaChanged(const FOnAttributeChangeData& Data);
    virtual void MaxStaminaChanged(const FOnAttributeChangeData& Data);
    virtual void StaminaRegenRateChanged(const FOnAttributeChangeData& Data);
    virtual void CharacterLevelChanged(const FOnAttributeChangeData& Data);
};
