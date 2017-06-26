// Fill out your copyright notice in the Description page of Project Settings.

#include "SA_Afflicted.h"
#include "Parede.h"


// Sets default values
AParede::AParede()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("BlockAll");
	MeshComp->SetupAttachment(CollisionComp);

	ConstructorHelpers::FObjectFinder<UStaticMesh> LoadMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (LoadMesh.Succeeded()) {
		MeshComp->SetStaticMesh(LoadMesh.Object);

	}
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void AParede::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AParede::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int8 AParede::GetID()
{
	return Id;
}

void AParede::TrocarColisao(bool Value) 
{
	if (Value) {
		MeshComp->SetCollisionProfileName("BlockAll");
		MeshComp->SetVisibility(true);
	} else {
		MeshComp->SetCollisionProfileName("OverlapAllDynamic");
		MeshComp->SetVisibility(false);
	}
}