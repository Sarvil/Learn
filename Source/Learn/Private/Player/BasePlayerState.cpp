// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BasePlayerState.h"
#include "Abilities/GASAbilitySystemComponent.h"
#include "AttributeSets/BaseAttributeSet.h"
#include "LearnCharacter.h"
#include "Player/BasePlayerController.h"
#include "UI/BaseHUDWidget.h"
#include "UI/FloatingStatusBarWidget.h"

ABasePlayerState::ABasePlayerState()
{
    AbilitySystemComponent = CreateDefaultSubobject<UGASAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
    // Mixed mode means we only are replicated the GEs to ourself, not the GEs to simulated proxies. If another GDPlayerState (Hero) receives a GE,
	// we won't be told about it by the Server. Attributes, GameplayTags, and GameplayCues will still replicate to us.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// Create the attribute set, this replicates by default
	// Adding it as a subobject of the owning actor of an AbilitySystemComponent
	// automatically registers the AttributeSet with the AbilitySystemComponent
	BaseAttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("BaseAttributeSet"));

	// Set PlayerState's NetUpdateFrequency to the same as the Character.
	// Default is very low for PlayerStates and introduces perceived lag in the ability system.
	// 100 is probably way too high for a shipping game, you can adjust to fit your needs.
	SetNetUpdateFrequency(100.0f);
}

UAbilitySystemComponent *ABasePlayerState::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

UBaseAttributeSet* ABasePlayerState::GetBaseAttributeSet() const
{
    return BaseAttributeSet;
}

float ABasePlayerState::GetHealth() const
{
    return BaseAttributeSet->GetHealth();
}

float ABasePlayerState::GetMaxHealth() const
{
    return BaseAttributeSet->GetMaxHealth();
}

float ABasePlayerState::GetHealthRegenRate() const
{
    return BaseAttributeSet->GetHealthRegenRate();
}

float ABasePlayerState::GetMana() const
{
    return BaseAttributeSet->GetMana();
}

float ABasePlayerState::GetMaxMana() const
{
    return BaseAttributeSet->GetMaxMana();
}

float ABasePlayerState::GetManaRegenRate() const
{
    return BaseAttributeSet->GetManaRegenRate();
}

float ABasePlayerState::GetStamina() const
{
    return BaseAttributeSet->GetStamina();
}

float ABasePlayerState::GetMaxStamina() const
{
    return BaseAttributeSet->GetMaxStamina();
}

float ABasePlayerState::GetStaminaRegenRate() const
{
    return BaseAttributeSet->GetStaminaRegenRate();
}

float ABasePlayerState::GetArmor() const
{
    return BaseAttributeSet->GetArmor();
}



float ABasePlayerState::GetCharacterLevel() const
{
    return BaseAttributeSet->GetCharacterLevel();
}

float ABasePlayerState::GetMoveSpeed() const
{
    return BaseAttributeSet->GetMoveSpeed();
}

void ABasePlayerState::BeginPlay()
{
    Super::BeginPlay();

    if(AbilitySystemComponent)
    {
        HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetHealthAttribute()).AddUObject(this, &ABasePlayerState::HealthChanged);
        MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &ABasePlayerState::MaxHealthChanged);
        HealthRegenRateChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetHealthRegenRateAttribute()).AddUObject(this, &ABasePlayerState::HealthRegenRateChanged);
        ManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetManaAttribute()).AddUObject(this, &ABasePlayerState::ManaChanged);
        MaxManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetMaxManaAttribute()).AddUObject(this, &ABasePlayerState::MaxManaChanged);
        ManaRegenRateChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetManaRegenRateAttribute()).AddUObject(this, &ABasePlayerState::ManaRegenRateChanged);
        StaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetStaminaAttribute()).AddUObject(this, &ABasePlayerState::StaminaChanged);
        MaxStaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetMaxStaminaAttribute()).AddUObject(this, &ABasePlayerState::MaxStaminaChanged);
        StaminaRegenRateChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetStaminaRegenRateAttribute()).AddUObject(this, &ABasePlayerState::StaminaRegenRateChanged);
        CharacterLevelChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetCharacterLevelAttribute()).AddUObject(this, &ABasePlayerState::CharacterLevelChanged);
    }
}

void ABasePlayerState::HealthChanged(const FOnAttributeChangeData &Data)
{
    float Health = Data.NewValue;
    ALearnCharacter* Hero = Cast<ALearnCharacter>(GetPawn());
    if(Hero)
    {
        UFloatingStatusBarWidget* HeroFloatingStatusBar = Hero->GetFloatingStatusBar();
        if (HeroFloatingStatusBar)
		{
			HeroFloatingStatusBar->SetHealthPercentage(Health / GetMaxHealth());
		}
    }
}

void ABasePlayerState::MaxHealthChanged(const FOnAttributeChangeData &Data)
{
    float MaxHealth = Data.NewValue;
    ALearnCharacter* Hero = Cast<ALearnCharacter>(GetPawn());
    if(Hero)
    {
        UFloatingStatusBarWidget* HeroFloatingStatusBar = Hero->GetFloatingStatusBar();
        if (HeroFloatingStatusBar)
		{
			HeroFloatingStatusBar->SetHealthPercentage(GetHealth() / MaxHealth);
		}
    }
    ABasePlayerController* PC = Cast<ABasePlayerController>(GetOwner());
    if(PC)
    {
        UBaseHUDWidget* HUD = PC->GetHUD();
        if(HUD)
        {
            HUD->SetMaxHealth(MaxHealth);
        }
    }
}

void ABasePlayerState::HealthRegenRateChanged(const FOnAttributeChangeData &Data)
{
    float HealthRegenRate = Data.NewValue;
    ABasePlayerController* PC = Cast<ABasePlayerController>(GetOwner());
    if(PC)
    {
        UBaseHUDWidget* HUD = PC->GetHUD();
        if(HUD)
        {
            HUD->SetHealthRegenRate(HealthRegenRate);
        }
    }
}

void ABasePlayerState::ManaChanged(const FOnAttributeChangeData &Data)
{
    float Mana = Data.NewValue;
    ALearnCharacter* Hero = Cast<ALearnCharacter>(GetPawn());
    if(Hero)
    {
        UFloatingStatusBarWidget* HeroFloatingStatusBar = Hero->GetFloatingStatusBar();
        if (HeroFloatingStatusBar)
		{
			HeroFloatingStatusBar->SetManaPercentage(Mana / GetMaxMana());
		}
    }
}

void ABasePlayerState::MaxManaChanged(const FOnAttributeChangeData &Data)
{
    float MaxMana = Data.NewValue;
    ALearnCharacter* Hero = Cast<ALearnCharacter>(GetPawn());
    if(Hero)
    {
        UFloatingStatusBarWidget* HeroFloatingStatusBar = Hero->GetFloatingStatusBar();
        if (HeroFloatingStatusBar)
		{
			HeroFloatingStatusBar->SetManaPercentage(GetMana() / MaxMana);
		}
    }
    ABasePlayerController* PC = Cast<ABasePlayerController>(GetOwner());
    if(PC)
    {
        UBaseHUDWidget* HUD = PC->GetHUD();
        if(HUD)
        {
            HUD->SetMaxMana(MaxMana);
        }
    }
}

void ABasePlayerState::ManaRegenRateChanged(const FOnAttributeChangeData &Data)
{
    float ManaRegenRate = Data.NewValue;
    ABasePlayerController* PC = Cast<ABasePlayerController>(GetOwner());
    if(PC)
    {
        UBaseHUDWidget* HUD = PC->GetHUD();
        if(HUD)
        {
            HUD->SetManaRegenRate(ManaRegenRate);
        }
    }
}

void ABasePlayerState::StaminaChanged(const FOnAttributeChangeData &Data)
{
    float Stamina = Data.NewValue;
    ALearnCharacter* Hero = Cast<ALearnCharacter>(GetPawn());
    if(Hero)
    {
        UFloatingStatusBarWidget* HeroFloatingStatusBar = Hero->GetFloatingStatusBar();
        if (HeroFloatingStatusBar)
		{
			HeroFloatingStatusBar->SetStaminaPercentage(Stamina / GetMaxStamina());
		}
    }
}

void ABasePlayerState::MaxStaminaChanged(const FOnAttributeChangeData &Data)
{
    float MaxStamina = Data.NewValue;
    ALearnCharacter* Hero = Cast<ALearnCharacter>(GetPawn());
    if(Hero)
    {
        UFloatingStatusBarWidget* HeroFloatingStatusBar = Hero->GetFloatingStatusBar();
        if (HeroFloatingStatusBar)
		{
			HeroFloatingStatusBar->SetStaminaPercentage(GetStamina() / MaxStamina);
		}
    }
    ABasePlayerController* PC = Cast<ABasePlayerController>(GetOwner());
    if(PC)
    {
        UBaseHUDWidget* HUD = PC->GetHUD();
        if(HUD)
        {
            HUD->SetMaxStamina(MaxStamina);
        }
    }
}

void ABasePlayerState::StaminaRegenRateChanged(const FOnAttributeChangeData &Data)
{
    float StaminaRegenRate = Data.NewValue;
    ABasePlayerController* PC = Cast<ABasePlayerController>(GetOwner());
    if(PC)
    {
        UBaseHUDWidget* HUD = PC->GetHUD();
        if(HUD)
        {
            HUD->SetStaminaRegenRate(StaminaRegenRate);
        }
    }
}

void ABasePlayerState::CharacterLevelChanged(const FOnAttributeChangeData &Data)
{
    float CharacterLevel = Data.NewValue;
    ABasePlayerController* PC = Cast<ABasePlayerController>(GetOwner());
    if(PC)
    {
        UBaseHUDWidget* HUD = PC->GetHUD();
        if(HUD)
        {
            HUD->SetCharacterLevel(CharacterLevel);
        }
    }
}
