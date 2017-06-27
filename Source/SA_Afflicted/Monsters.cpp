// Fill out your copyright notice in the Description page of Project Settings.

#include "SA_Afflicted.h"
#include "Monsters.h"
#include "Personagem.h"
#include "LuzesDropadas.h"
#include "Parede.h"
#include "Lente.h"
#include "ProjectilBoss.h"
#include "MyHUD.h"


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
	Atirar();

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
		if (Id == 2) {
			SetActorLocation(FVector(GetActorLocation().X + 10, GetActorLocation().Y, GetActorLocation().Z));
		} else if (Id == 3) {
			SetActorLocation(FVector(GetActorLocation().X + 25, GetActorLocation().Y-15, GetActorLocation().Z));
		} else {
			SetActorLocation(FVector(GetActorLocation().X + 5, GetActorLocation().Y, GetActorLocation().Z));
		}
		
		if (GetActorLocation().X >= InitialPos.X + 100) {
			Direction = 1;
		}
	} else {
		if (Id == 2) {
			SetActorLocation(FVector(GetActorLocation().X - 10, GetActorLocation().Y, GetActorLocation().Z));
		}
		else if (Id == 3) {
			SetActorLocation(FVector(GetActorLocation().X - 25, GetActorLocation().Y+15, GetActorLocation().Z));
		}
		else {
			SetActorLocation(FVector(GetActorLocation().X - 5, GetActorLocation().Y, GetActorLocation().Z));
		}
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

int8 AMonsters::GetId()
{
	return Id;
}

void AMonsters::SetId(int8 Value)
{
	Id = Value;
}

void AMonsters::Destruir()
{
	AMyHUD * hud = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (Id == 1 || Id == 2) { //Primeiro Monstro
		TArray<AActor*> FoundParede;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AParede::StaticClass(), FoundParede);

		for (int i = 0; i < FoundParede.Num(); i++) {
			AParede* Parede = Cast<AParede>(FoundParede[i]);
			if (Id == 1 && Parede->GetID() == 2) {
				//Destroe a segunda parede
				if (hud) {
					hud->AtivarTexto(2);
				}
				Parede->SetAbaixavel(true);
				break;
			} else if (Id == 2 && Parede->GetID() == 3) {
				//Destroe a teceira parede
				UWorld* World = GetWorld();
				if (World) {
					FActorSpawnParameters SpawnParameters;
					ALente* Lente = World->SpawnActor<ALente>(GetActorLocation(), GetActorRotation(), SpawnParameters);
				}
				if (hud) {
					hud->AtivarTexto(4);
				}
				Parede->SetAbaixavel(true);
				break;
			}
		}
	} else if (Id == 3) {
		
		if (hud) {
			hud->AtivarTexto(7);
		}
	}

	UWorld* World = GetWorld();
	if (World) {
		APawn* Pawn = UGameplayStatics::GetPlayerPawn(World, 0);
		if (Pawn) {
			APersonagem* Personagem = Cast<APersonagem>(Pawn);
			if (Personagem) {
				Personagem->SetMonstrosMortos(Personagem->GetMonstrosMortos() + 1);
				if (Personagem->GetMonstrosMortos() == 6 || Personagem->GetMonstrosMortos() == 18) {
					TArray<AActor*> FoundParede;
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), AParede::StaticClass(), FoundParede);
					for (int i = 0; i < FoundParede.Num(); i++) {
						AParede* Parede = Cast<AParede>(FoundParede[i]);
						if ((Personagem->GetMonstrosMortos() == 6 && Parede->GetID() == 5) || (Personagem->GetMonstrosMortos() == 18 && Parede->GetID() == 4)) {
							if (Parede->GetID() == 5) {
								if (hud) {
									hud->AtivarTexto(3);
								}
							} else {
								if (hud) {
									hud->AtivarTexto(6);
								}
							}
							Parede->SetAbaixavel(true);
							break;
						}
					}
				}
			}
		}
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

void AMonsters::Atirar() {
	if (Id == 3) {
		int8 Random = FMath::RandRange(1, 20);
		UWorld* World = GetWorld();
		if (World && Random == 1) {
			FActorSpawnParameters SpawnParameters;
			FRotator Rotation = GetActorRotation();
			Rotation.Roll = FMath::RandRange(0, 360);
			Rotation.Pitch = FMath::RandRange(0, 360);
			Rotation.Yaw = FMath::RandRange(0, 360);
			AProjectilBoss* Projectile = World->SpawnActor<AProjectilBoss>(GetActorLocation(), Rotation, SpawnParameters);
		}
	}
}