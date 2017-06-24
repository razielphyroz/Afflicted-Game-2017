// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LuzesDropadas.generated.h"

UCLASS()
class SA_AFFLICTED_API ALuzesDropadas : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALuzesDropadas();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Levitar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Iluminacao")
	UPointLightComponent* Light;

	FVector InitialPos;

	int8 MoveDistance;
};
