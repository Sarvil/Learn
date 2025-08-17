// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BaseCharacter.h"
#include "AttributeSets/BaseAttributeSet.h"
#include "Abilities/GASAbilitySystemComponent.h"
#include "Abilities/BaseGameplayAbility.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);
	bAlwaysRelevant = true;
}

UAbilitySystemComponent *ABaseCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent.Get();
}

int32 ABaseCharacter::GetAbilityLevel(EAbilityInputID AbilityID) const
{
    return 1;
}

void ABaseCharacter::RemoveCharacterAbilities()
{
	if(GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || !AbilitySystemComponent->bCharacterAbilitiesGiven)
	{
		return;
	}
	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if ((Spec.SourceObject == this) && CharacterAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}
	for (int32 i=0; i<AbilitiesToRemove.Num(); i++)
	{
		AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
	}
	AbilitySystemComponent->bCharacterAbilitiesGiven = false;
}

int32 ABaseCharacter::GetCharacterLevel() const
{
	if (BaseAttributeSet.IsValid())
	{
		return static_cast<int32>(BaseAttributeSet->GetCharacterLevel());
	}
	return 0;
}

float ABaseCharacter::GetHealth() const
{
	if(BaseAttributeSet.IsValid())
	{
		return BaseAttributeSet->GetHealth();
	}
	return 0.0f;
}

float ABaseCharacter::GetMaxHealth() const
{
	if(BaseAttributeSet.IsValid())
	{
		return BaseAttributeSet->GetMaxHealth();
	}
	return 0.0f;
}

float ABaseCharacter::GetMana() const
{
	if(BaseAttributeSet.IsValid())
	{
		return BaseAttributeSet->GetMana();
	}
	return 0.0f;
}

float ABaseCharacter::GetMaxMana() const
{
	if(BaseAttributeSet.IsValid())
	{
		return BaseAttributeSet->GetMaxMana();
	}
	return 0.0f;
}

float ABaseCharacter::GetStamina() const
{
	if(BaseAttributeSet.IsValid())
	{
		return BaseAttributeSet->GetStamina();
	}
	return 0.0f;
}
float ABaseCharacter::GetMaxStamina() const
{
	if(BaseAttributeSet.IsValid())
	{
		return BaseAttributeSet->GetMaxStamina();
	}
	return 0.0f;
}

float ABaseCharacter::GetMoveSpeed() const
{
	if(BaseAttributeSet.IsValid())
	{
		return BaseAttributeSet->GetMoveSpeed();
	}
	return 0.0f;
}

float ABaseCharacter::GetMoveSpeedBaseValue() const
{
	if(BaseAttributeSet.IsValid())
	{
		return BaseAttributeSet->GetMoveSpeedAttribute().GetGameplayAttributeData(BaseAttributeSet.Get())->GetBaseValue();
	}
    return 0.0f;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::AddCharacterAbilities()
{
	if(GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->bCharacterAbilitiesGiven)
	{
		return;
	}
	for (TSubclassOf<UBaseGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility, GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID), static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
	}
	AbilitySystemComponent->bCharacterAbilitiesGiven = true;
}

void ABaseCharacter::InitializeAttributes()
{
	if(!AbilitySystemComponent.IsValid())
	{
		return;
	}
	if(!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the Character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, GetCharacterLevel(), EffectContext);
	if(NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	}
}

void ABaseCharacter::AddStartupEffects()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->bStartupEffectsApplied)
	{
		return;
	}
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for(TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, GetCharacterLevel(), EffectContext);
		if(NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
		}
	}
	AbilitySystemComponent->bStartupEffectsApplied = true;
}

void ABaseCharacter::SetHealth(float Health)
{
	if(BaseAttributeSet.IsValid())
	{
		BaseAttributeSet->SetHealth(Health);
	}
}

void ABaseCharacter::SetMana(float Mana)
{
	if(BaseAttributeSet.IsValid())
	{
		BaseAttributeSet->SetMana(Mana);
	}
}

void ABaseCharacter::SetStamina(float Stamina)
{
	if(BaseAttributeSet.IsValid())
	{
		BaseAttributeSet->SetStamina(Stamina);
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

