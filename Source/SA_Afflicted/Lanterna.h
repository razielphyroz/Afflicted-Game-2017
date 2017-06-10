// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Lanterna.generated.h"

UCLASS()
class SA_AFFLICTED_API ALanterna : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALanterna();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Collision")
		UBoxComponent* CollisionComp;

	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMeshComponent* LanternMesh;
	
	UPROPERTY(EditAnywhere)
		FVector InitialLocation;

	UPROPERTY(EditAnywhere, Category = "Lanterna")
		int8 Direction;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Rodar();


};
