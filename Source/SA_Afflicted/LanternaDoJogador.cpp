// Fill out your copyright notice in the Description page of Project Settings.

#include "SA_Afflicted.h"
#include "LanternaDoJogador.h"
#include "Monsters.h"
#include "Parede.h"


// Sets default values
ALanternaDoJogador::ALanternaDoJogador()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionProfileName("NoCollision");
	Mesh->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
	RootComponent = Mesh;
	ConstructorHelpers::FObjectFinder<UStaticMesh>NewMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (NewMesh.Succeeded()) {
		Mesh->SetStaticMesh(NewMesh.Object);
	}

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionCompLanterna"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	//CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ALanternaDoJogador::OnOverlapBegin);
	//CollisionComp->OnComponentEndOverlap.AddDynamic(this, &ALanternaDoJogador::OnEndOverlap);
	CollisionComp->SetRelativeScale3D(FVector(30.0f, 15.0f, 15.0f));
	CollisionComp->SetRelativeLocation(FVector(1200.0f, 0.0f, 40.0f));
	CollisionComp->SetupAttachment(RootComponent);

	LuzLanterna = CreateDefaultSubobject<USpotLightComponent>(TEXT("LuzDaLanterna"));
	LuzLanterna->SetupAttachment(RootComponent);

	LuzLanterna->SetRelativeLocation(FVector(150.0f, 0.0f, 150.0f));

	LuzLanterna->bUseTemperature = true;

	LuzLanterna->SetIntensity(100000.0f);
	LuzLanterna->SetInnerConeAngle(25.0f);
	LuzLanterna->SetOuterConeAngle(55.0f);
	LuzLanterna->SetAttenuationRadius(2500.0f);

	CoresDisponiveis = 2;

}

// Called when the game starts or when spawned
void ALanternaDoJogador::BeginPlay()
{
	Super::BeginPlay();
	CorAtual = 1;

}

void ALanternaDoJogador::AdicionarCorDisponivel() {
	if (CoresDisponiveis <= 5) {
		CoresDisponiveis += 1;
	}
}

//void ALanternaDoJogador::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
//{
//	if (OtherActor != nullptr && OtherActor->IsA(AMonsters::StaticClass())) {
//		AMonsters* Monstro = Cast<AMonsters>(OtherActor);
//		if (Monstro->IsVisible() == false && Monstro->GetCorParaAparecer() == CorAtual) {
//			Monstro->SetVisible(true);
//		}	
//	} else if (OtherActor != nullptr && OtherActor->IsA(AParede::StaticClass())) {
//		AParede* Parede = Cast<AParede>(OtherActor);
//		if (Parede->GetID() == 1 && CorAtual == 2) {
//			Parede->TrocarColisao(false);
//		} else {
//			Parede->TrocarColisao(true);
//		}
//	}
//}
//
//void ALanternaDoJogador::OnEndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
//{
//	if (OtherActor != nullptr && OtherActor->IsA(AMonsters::StaticClass())) {
//		AMonsters* Monstro = Cast<AMonsters>(OtherActor);
//		if (Monstro->IsVisible() == true) {
//			Monstro->SetVisible(false);
//		}
//	}
//}

void ALanternaDoJogador::MudarCorDaLuz()
{

	if (CorAtual == CoresDisponiveis) {
		CorAtual = 1;
	} else {
		CorAtual += 1;
	}

	TArray<AActor*> FoundMonsters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMonsters::StaticClass(), FoundMonsters);

	for (int i = 0; i < FoundMonsters.Num(); i++) {
		AMonsters* Monstro = Cast<AMonsters>(FoundMonsters[i]);
		if (Monstro->GetCorParaAparecer() == CorAtual && Monstro->IsVisible() == false) {
			Monstro->SetVisible(true);
		}
		else if (Monstro->GetCorParaAparecer() != CorAtual && Monstro->IsVisible() == true) {
			Monstro->SetVisible(false);
		}
	}

	TArray<AActor*> FoundParedes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AParede::StaticClass(), FoundParedes);

	for (int i = 0; i < FoundParedes.Num(); i++) {
		AParede* Parede = Cast<AParede>(FoundParedes[i]);
		if (Parede->GetID() == 1 && CorAtual == 2) {
			Parede->TrocarColisao(false);
		} else if (Parede->GetID() == 1 && CorAtual != 2) {
			Parede->TrocarColisao(true);
		}
	}
	
	switch (CorAtual) {
	case 1:
		LuzLanterna->SetLightColor(FLinearColor(0.25f, 0.25f, 0.25f, 0.25f));
		LuzLanterna->SetTemperature(6000.0f);
		break;
	case 2:
		LuzLanterna->SetLightColor(FLinearColor(0.0f, 0.6f, 0.0f, 0.6f));
		LuzLanterna->SetTemperature(1700.0f);
		break;
	case 3:
		LuzLanterna->SetLightColor(FLinearColor(0.0f, 0.0f, 0.6f, 0.6f));
		LuzLanterna->SetTemperature(6000.0f);
		break;
	case 4:
		LuzLanterna->SetLightColor(FLinearColor(0.7f, 0.7f, 0.0f, 0.7f));
		LuzLanterna->SetTemperature(6000.0f);
		break;
	case 5:
		LuzLanterna->SetLightColor(FLinearColor(0.6f, 0.0f, 0.7f, 0.7f));
		LuzLanterna->SetTemperature(6000.0f);
		break;
	case 6:
		LuzLanterna->SetLightColor(FLinearColor(0.6f, 0.0f, 0.0f, 0.6f));
		LuzLanterna->SetTemperature(1700.0f);
		break;
	}
}

// Called every frame
void ALanternaDoJogador::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

