// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;
class ABaseHUD;

/**
 * 
 */
UCLASS()
class LEARN_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	void CreateHUD();

	class UBaseHUDWidget* GetHUD();

protected:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnRep_PlayerState() override;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	/** Mobile controls widget to spawn */
	UPROPERTY(EditAnywhere, Category="Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to the mobile controls widget */
	TObjectPtr<UUserWidget> MobileControlsWidget;

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="GAS|UI")
	TSubclassOf<UBaseHUDWidget> UIHUDWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category="GAS|UI")
	class UBaseHUDWidget* UIHUDWidget;
};
