// Fill out your copyright notice in the Description page of Project Settings.

#include "SA_Afflicted.h"
#include "Monsters.h"
#include "Personagem.h"


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

	CorParaAparecer = FMath::FRandRange(0, 5);
	Damage = 5;
	Life = 100;
}

// Called when the game starts or when spawned
void AMonsters::BeginPlay()
{
	Super::BeginPlay();
	Mesh->SetVisibility(false);
	InitialPos = GetActorLocation();
	CorParaAparecer = FMath::FRandRange(1, 6);
}

// Called every frame
void AMonsters::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Update();

}

void AMonsters::SetVisible(bool Value)
{
	if (Mesh != nullptr && Mesh != NULL) {
		Mesh->SetVisibility(Value);
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

int8 AMonsters::GetLife()
{
	return Life;
}

void AMonsters::SetLife(int8 Value)
{
	Life = Value;
}
