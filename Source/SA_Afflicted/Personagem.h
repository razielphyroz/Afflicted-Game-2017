// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Personagem.generated.h"

UCLASS()
class SA_AFFLICTED_API APersonagem : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APersonagem();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	int16 GetLentesDisponiveis();
	void SetLentesDisponiveis(int16 NewValue);

	bool IsTemArma();
	void SetTemArma(bool NewValue);

	bool IsTemLanterna();
	void SetTemLanterna(bool NewValue);

	int8 GetLife();
	void SetLife(int8 Value);

	void AdicionarCorDisponivel();

	void Atirar();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* CameraBoom;


	TSubclassOf<class UUserWidget> UserWidgetPause;

	class ALanternaDoJogador* LanternaEmUso;


	void Move(float Value);

	void MoveSides(float Value);

	void MudarCor();

	int16 LentesDisponiveis;
	void Pause();	

	int8 Life;

	bool TemArma;
	bool TemLanterna;
};
