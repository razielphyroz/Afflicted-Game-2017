// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Monsters.generated.h"

UCLASS()
class SA_AFFLICTED_API AMonsters : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsters();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetVisible(bool Value);

	bool IsVisible();

	int8 GetCorParaAparecer();

	float GetLife();

	void SetLife(float Value);

	void Destruir();

	void RodarBarraLife(FRotator Vector);

	void AtualizarBarraLife();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Collision")
		UCapsuleComponent* CollisionComp;

	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "LifeMesh")
		UStaticMeshComponent* GreenLife;

	UPROPERTY(EditAnywhere, Category = "MonsterProprieties")
		int8 CorParaAparecer;

	UPROPERTY(EditAnywhere, Category = "MonsterProprieties")
		float Damage;

	UPROPERTY(EditAnywhere, Category = "MonsterProprieties")
		float Life;

	UPROPERTY(EditAnywhere, Category = "MonsterProprieties")
		float LifeInicial;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FVector InitialPos;

	int8 Direction;

	void Update();
};
