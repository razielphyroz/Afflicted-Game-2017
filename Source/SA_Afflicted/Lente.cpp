// Fill out your copyright notice in the Description page of Project Settings.

#include "SA_Afflicted.h"
#include "Lente.h"
#include "Personagem.h"


// Sets default values
ALente::ALente()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ALente::OnOverlapBegin);
	CollisionComp->SetBoxExtent(FVector(0.1f, 0.1f, 0.1f));
	RootComponent = CollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoCollision");
	MeshComp->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
	MeshComp->SetupAttachment(CollisionComp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> LoadMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (LoadMesh.Succeeded()) {
		MeshComp->SetStaticMesh(LoadMesh.Object);

	}
	

}

// Called when the game starts or when spawned
void ALente::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALente::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ALente::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor != nullptr && OtherActor->IsA(APersonagem::StaticClass())) {
		APersonagem*Personagem = Cast<APersonagem>(OtherActor);
		Personagem->AdicionarCorDisponivel();
		Destroy();
	}
}

