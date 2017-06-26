// Fill out your copyright notice in the Description page of Project Settings.

#include "SA_Afflicted.h"
#include "ProjectilBoss.h"
#include "Personagem.h"


// Sets default values
AProjectilBoss::AProjectilBoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->bGenerateOverlapEvents = true;
	MeshComp->SetCollisionProfileName("OverlapAllDynamic");
	MeshComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectilBoss::OnOverlapBegin);

	ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (Mesh.Succeeded()) {
		MeshComp->SetStaticMesh(Mesh.Object);
	}
	RootComponent = MeshComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->MaxSpeed = 1000.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 2.0f;
}

// Called when the game starts or when spawned
void AProjectilBoss::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectilBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectilBoss::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor->IsA(APersonagem::StaticClass())) {
		APersonagem* Personagem = Cast<APersonagem>(OtherActor);
		if (Personagem) {
			//FimDeJogo
		}
	}
}