// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LanternaDoJogador.generated.h"

UCLASS()
class SA_AFFLICTED_API ALanternaDoJogador : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALanternaDoJogador();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void MudarCorDaLuz();
	void AdicionarCorDisponivel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Collision")
		UBoxComponent* CollisionComp;

	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "CorDaLente")
		int8 CorDaLente;

	//UFUNCTION()
	//	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	//		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//UFUNCTION()
	//	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	//		int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, Category = "LuzDaLanterna")
		USpotLightComponent* LuzLanterna;

	int8 CorAtual;
	int8 CoresDisponiveis;

};
