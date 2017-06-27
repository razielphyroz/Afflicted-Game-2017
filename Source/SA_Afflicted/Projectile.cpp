// Fill out your copyright notice in the Description page of Project Settings.

#include "SA_Afflicted.h"
#include "Projectile.h"
#include "Monsters.h"
#include "Personagem.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);

	CollisionComp->SetWorldScale3D(FVector(0.75f, 0.75f, 0.75f));
	RootComponent = CollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->bGenerateOverlapEvents = false;
	MeshComp->SetCollisionProfileName("NoCollision");
	MeshComp->SetWorldScale3D(FVector(1.50f, 1.50f, 1.50f));
	MeshComp->SetWorldLocation(FVector(0.0f, 0.0f, -55.0f));
	ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/SA_things/coracaozao.coracaozao'"));
	if (Mesh.Succeeded()) {
		MeshComp->SetStaticMesh(Mesh.Object);
		MeshComp->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	}
	MeshComp->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->MaxSpeed = 2000.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 1.0f;

	Dano = 10.0f;
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
		if (Monster->IsVisible()) {
			if (Monster->GetLife() - Dano > 0.0f) {
				Monster->SetLife(Monster->GetLife() - Dano);
				Monster->AtualizarBarraLife();
			}
			else {
				Monster->Destruir();
			}
			Destroy();
		}
	}
}