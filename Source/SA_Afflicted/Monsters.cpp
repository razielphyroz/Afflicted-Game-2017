// Fill out your copyright notice in the Description page of Project Settings.

#include "SA_Afflicted.h"
#include "Monsters.h"
#include "Personagem.h"
#include "LuzesDropadas.h"


// Sets default values
AMonsters::AMonsters()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCompMonster"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMonsters::OnOverlapBegin);
	CollisionComp->SetCapsuleRadius(25.5f);
	CollisionComp->SetCapsuleHalfHeight(51.0f);
	RootComponent = CollisionComp;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionProfileName("NoCollision");
	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f,-50.0f));
	Mesh->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh>NewMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));

	if (NewMesh.Succeeded()) {
		Mesh->SetStaticMesh(NewMesh.Object);
	}

	GreenLife = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GreenLife"));
	GreenLife->bGenerateOverlapEvents = false;
	GreenLife->SetCollisionProfileName("OverlapAllDynamic");
	GreenLife->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
	GreenLife->SetRelativeScale3D(FVector(1.0f, 0.2f, 0.1f));
	GreenLife->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UMaterial> GreenMaterial(TEXT("Material'/Game/Materials/GreenLife.GreenLife'"));
	if (GreenMaterial.Succeeded()) {
		GreenLife->SetMaterial(0, GreenMaterial.Object);
	}
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshGreen(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));
	if (MeshGreen.Succeeded()) {
		GreenLife->SetStaticMesh(MeshGreen.Object);
	}

	Damage = 5.0f;
	Life = 100.0f;
	CorParaAparecer = FMath::FRandRange(1, 2);
}

// Called when the game starts or when spawned
void AMonsters::BeginPlay()
{
	Super::BeginPlay();
	Mesh->SetVisibility(false);
	GreenLife->SetVisibility(false);
	InitialPos = GetActorLocation();
	LifeInicial = Life;

}

// Called every frame
void AMonsters::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Update();

	UWorld* World = GetWorld();
	if (World) {
		APawn* Player = UGameplayStatics::GetPlayerPawn(World, 0);
		if (Player) {
			RodarBarraLife(FRotator(0.0f, Player->GetActorRotation().Yaw + 90.0f, 0.0f));
		}
	}
}

void AMonsters::SetVisible(bool Value)
{
	if (Mesh) {
		Mesh->SetVisibility(Value);
	}
	if (GreenLife) {
		GreenLife->SetVisibility(Value);
	}
}

bool AMonsters::IsVisible()
{
	if (Mesh != nullptr && Mesh != NULL) {
		return Mesh->IsVisible();
	}
	return false;
}

void AMonsters::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor->IsA(APersonagem::StaticClass())) {
		APersonagem* Personagem = Cast<APersonagem>(OtherActor);
		if (Personagem->GetLife() > 0) {
			Personagem->SetLife(Personagem->GetLife() - Damage);
			UE_LOG(LogTemp, Warning, TEXT("Voce perdeu %d de Life. Restam: %d"), Damage, Personagem->GetLife());
		}
	}
}

void AMonsters::Update() 
{
	if (Direction == 0) {
		SetActorLocation(FVector(GetActorLocation().X + 1, GetActorLocation().Y, GetActorLocation().Z));
		if (GetActorLocation().X >= InitialPos.X + 100) {
			Direction = 1;
		}
	} else {
		SetActorLocation(FVector(GetActorLocation().X - 1, GetActorLocation().Y, GetActorLocation().Z));
		if (GetActorLocation().X <= InitialPos.X - 100) {
			Direction = 0;
		}
	}
}

int8 AMonsters::GetCorParaAparecer() {
	return CorParaAparecer;
}

float AMonsters::GetLife()
{
	return Life;
}

void AMonsters::SetLife(float Value)
{
	Life = Value;
}

void AMonsters::Destruir()
{
	UWorld* World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParameters;
		ALuzesDropadas* Luz = World->SpawnActor<ALuzesDropadas>(GetActorLocation(), GetActorRotation(), SpawnParameters);
	}
	Destroy();
}

void AMonsters::RodarBarraLife(FRotator Vetor)
{
	GreenLife->SetRelativeRotation(Vetor);
}

void AMonsters::AtualizarBarraLife()
{
	float NewLife = Life / LifeInicial;
	if (NewLife >= 0.1f) {
		GreenLife->SetRelativeScale3D(FVector(NewLife, 0.2f, 0.1f));
	}
}
