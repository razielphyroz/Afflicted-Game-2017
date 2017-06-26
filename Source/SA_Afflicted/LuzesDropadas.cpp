// Fill out your copyright notice in the Description page of Project Settings.

#include "SA_Afflicted.h"
#include "LuzesDropadas.h"


// Sets default values
ALuzesDropadas::ALuzesDropadas()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Luz"));
	Light->SetIntensity(5000.0f);
	MoveDistance = 240.0f;
}

// Called when the game starts or when spawned
void ALuzesDropadas::BeginPlay()
{
	Super::BeginPlay();
	InitialPos = GetActorLocation();
}

// Called every frame
void ALuzesDropadas::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Levitar();
}

void ALuzesDropadas::Levitar() {
	if (GetActorLocation().Z < InitialPos.Z + MoveDistance) {
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 5.0f));
	}
}