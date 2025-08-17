// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseEffectActor.h"
#include "Components/SphereComponent.h"
#include "AttributeSets/BaseAttributeSet.h"
#include "Abilities/GASAbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

void ABaseEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		UAbilitySystemComponent* AbilitySystemComponent = ASCInterface->GetAbilitySystemComponent();
		if (GetLocalRole() != ROLE_Authority || AbilitySystemComponent == nullptr)
		{
			return;
		}
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		for(TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
		{
			FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
			if(NewHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
			}
			Destroy();
		}
	}
}

void ABaseEffectActor::EndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
}

ABaseEffectActor::ABaseEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(GetRootComponent());
}

void ABaseEffectActor::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseEffectActor::OnOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseEffectActor::EndOverlap);
}

