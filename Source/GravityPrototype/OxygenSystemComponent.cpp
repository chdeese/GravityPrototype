// Fill out your copyright notice in the Description page of Project Settings.


#include "OxygenSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

// Sets default values for this component's properties
UOxygenSystemComponent::UOxygenSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UOxygenSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	Oxygen = MaxOxygen;
	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	Player->GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &UOxygenSystemComponent::OnPlayerOverlap);
	Player->GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &UOxygenSystemComponent::OnPlayerEndOverlap);
}


// Called every frame
void UOxygenSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Checking if player's oxygen should be refilled or depleted
	DepletePlayerOxygen();
	RefillPlayerOxygen();

	FString S = FString::SanitizeFloat(Oxygen);

	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::White, *S);
}

void UOxygenSystemComponent::RefillPlayerOxygen()
{
	if (bPlayerIsInOrbit)
		return;

	Oxygen += 1.f;
	
	if (Oxygen >= MaxOxygen)
		Oxygen = MaxOxygen;
}

void UOxygenSystemComponent::DepletePlayerOxygen()
{
	if (!bPlayerIsInOrbit)
		return;

	Oxygen -= DepletionRate;

	if (Oxygen <= 0.f)
	{
		Oxygen = 0.f;
		CallEndState();
	}
}

void UOxygenSystemComponent::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->ComponentHasTag("OxygenField"))
		bPlayerIsInOrbit = false;
}

void UOxygenSystemComponent::OnPlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bPlayerIsInOrbit = true;
}

void UOxygenSystemComponent::CallEndState()
{
	
}

