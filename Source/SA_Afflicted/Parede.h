// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Parede.generated.h"

UCLASS()
class SA_AFFLICTED_API AParede : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParede();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	int8 GetID();
	void TrocarColisao(bool Value);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Collision")
		UBoxComponent*CollisionComp;

	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, Category = "ParedeID")
		int8 Id;

	
};
