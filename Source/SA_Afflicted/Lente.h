// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Lente.generated.h"

UCLASS()
class SA_AFFLICTED_API ALente : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALente();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	int32 LenteVermelha, LenteVerde, LenteAzul;
	int32 GetLenteVermelha();
	void SetLenteVermelha(int32 NewLente);

private:

	UPROPERTY(EditAnywhere, Category = "Collision")
		UBoxComponent*CollisionComp;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMeshComponent* MeshComp;
	
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
	
};
