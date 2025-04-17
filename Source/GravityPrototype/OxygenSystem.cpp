// Fill out your copyright notice in the Description page of Project Settings.


#include "OxygenSystem.h"
#include "GravityPrototypeCharacter.h"
#include "PropulsionComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AOxygenSystem::AOxygenSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOxygenSystem::BeginPlay()
{
	Super::BeginPlay();
	AGravityPrototypeCharacter* player = (AGravityPrototypeCharacter*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	UPropulsionComponent* comp = player->GetComponentByClass<UPropulsionComponent>();
	TSubclassOf<UPropulsionComponent> bpComp;
}

// Called every frame
void AOxygenSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

