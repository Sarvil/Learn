// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BasePlayerController.h"
#include "AbilitySystemComponent.h"
#include "LearnCharacter.h"
#include "UI/BaseHUDWidget.h"
#include "Player/BasePlayerState.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "Learn.h"
#include "Widgets/Input/SVirtualJoystick.h"

void ABasePlayerController::OnPossess(APawn * InPawn)
{
    Super::OnPossess(InPawn);
    ABasePlayerState* PS = GetPlayerState<ABasePlayerState>();
    if (PS)
    {
        PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
    }
}

void ABasePlayerController::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// only spawn touch controls on local player controllers
	if (SVirtualJoystick::ShouldDisplayTouchInterface() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogLearn, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!SVirtualJoystick::ShouldDisplayTouchInterface())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
}