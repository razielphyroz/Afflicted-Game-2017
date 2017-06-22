// Fill out your copyright notice in the Description page of Project Settings.

#include "SA_Afflicted.h"
#include "Projectile.h"
#include "Monsters.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->bGenerateOverlapEvents = true;
	MeshComp->SetCollisionProfileName("OverlapAllDynamic");
	MeshComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
	MeshComp->SetWorldScale3D(FVector(0.3f, 0.3f, 0.3f));

	ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (Mesh.Succeeded()) {
		MeshComp->SetStaticMesh(Mesh.Object);
	}
	RootComponent = MeshComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->MaxSpeed = 2000.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 3.0f;

	Dano = 10;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor->IsA(AMonsters::StaticClass())) {
		AMonsters* Monster = Cast<AMonsters>(OtherActor);
		if (Monster->GetLife() - Dano > 0) {
			Monster->SetLife(Monster->GetLife() - Dano);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("Monstro Destruido."));
			Monster->Destroy();
		}
		Destroy();
	}
} 

void AProjectile::InitVelocity(const FVector& ShootDirection)
{
	if (ProjectileMovement)
	{
		ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
	}
}