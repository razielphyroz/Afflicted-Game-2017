// Fill out your copyright notice in the Description page of Project Settings.

#include "SA_Afflicted.h"
#include "Lanterna.h"
#include "Personagem.h"


// Sets default values
ALanterna::ALanterna()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->SetBoxExtent(FVector(20.0f, 20.0f, 20.0f));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ALanterna::OnOverlapBegin);
	RootComponent = CollisionComp;

	LanternMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LanternMesh"));
	LanternMesh->SetCollisionProfileName("NoCollision");
	LanternMesh->SetupAttachment(RootComponent);
	LanternMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -20.0f));
	LanternMesh->SetWorldScale3D(FVector(0.4f, 0.4f, 0.4f));

	ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	if (Mesh.Succeeded()) {
		LanternMesh->SetStaticMesh(Mesh.Object);
	}

}

// Called when the game starts or when spawned
void ALanterna::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();

}

// Called every frame
void ALanterna::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rodar();

}

void ALanterna::Rodar() {

	SetActorRotation(FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + 0.5f, GetActorRotation().Roll));

	if (Direction == 0) {
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 0.4f));
		if (GetActorLocation().Z >= InitialLocation.Z + 10) {
			Direction = 1;
		}
	}
	else {
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 0.4f));
		if (GetActorLocation().Z <= InitialLocation.Z - 10) {
			Direction = 0;
		}
	}

}

void ALanterna::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor->IsA(APersonagem::StaticClass())) {
		APersonagem* Personagem = Cast<APersonagem>(OtherActor);
		if (!Personagem->IsTemArma() && !Personagem->IsTemLanterna()) {
			Personagem->SetTemLanterna(true);
			UE_LOG(LogTemp, Warning, TEXT("Lanterna Coletada"));
			Destroy();
		} else {
			UE_LOG(LogTemp, Warning, TEXT("Você Ja Possui Uma Arma"));
		}
	}
}