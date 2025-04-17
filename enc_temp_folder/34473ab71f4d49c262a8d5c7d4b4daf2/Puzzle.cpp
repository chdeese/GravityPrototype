// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


#define DELAY(time, block)\
{\
FTimerHandle TimerHandle;\
GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()block, time, false);\
}

// Sets default values
APuzzle::APuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	sceneComponent->SetupAttachment(RootComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(sceneComponent);
	StaticMesh->SetMobility(EComponentMobility::Stationary);

	TriggerBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	TriggerBounds->SetupAttachment(StaticMesh);
	TriggerBounds->SetMobility(EComponentMobility::Stationary);
	TriggerBounds->SetRelativeScale3D({ 2.f, 2.f, 3.f });
}

// Called when the game starts or when spawned
void APuzzle::BeginPlay()
{
	Super::BeginPlay();
	
	//UMaterial meh = StaticMesh->GetMaterial();
	
	TriggerBounds->OnComponentBeginOverlap.AddDynamic(this, &APuzzle::OnTriggerOverlap);
	TriggerBounds->OnComponentEndOverlap.AddDynamic(this, &APuzzle::OnTriggerOverlapEnd);
}

// Called every frame
void APuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APuzzle::OnTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PuzzleType == EPuzzleType::Switch)
		PuzzleActivated();
	else if (PuzzleType == EPuzzleType::Timer)
		bCountdownStarted = true; BeginCountdown();
}

void APuzzle::OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (PuzzleType == EPuzzleType::Switch)
		PuzzleDeactivated();
	else if (PuzzleType == EPuzzleType::Timer)
		return;
}

void APuzzle::BeginCountdown()
{
	if (!bCountdownStarted)
		return;

	PuzzleActivated();

	DELAY(Countdown, { PuzzleDeactivated(); });
}

void APuzzle::PuzzleActivated()
{
	if (bIsTriggered)
		return;

	OnPuzzleActivate.Broadcast();

	bCountdownStarted = false;
	bIsTriggered = true;

	//StaticMesh->SetMaterial()
	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::White, "Activate");
}

void APuzzle::PuzzleDeactivated()
{
	//Unactivate puzzle
	bIsTriggered = false;
	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::White, "UnActivate");
}

