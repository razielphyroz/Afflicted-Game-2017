// Fill out your copyright notice in the Description page of Project Settings.

#include "SA_Afflicted.h"
#include "Personagem.h"



// Sets default values
APersonagem::APersonagem()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(CameraBoom);

	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (SkeletalMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}

	GetMesh()->SetWorldLocation(FVector(0.0f, 0.0f, -80.0f));
	GetMesh()->SetWorldScale3D(FVector(0.9f, 0.9f, 0.9f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimObj(TEXT("AnimBlueprint'/Game/Animations/WalkAnimation.WalkAnimation'"));
	if (AnimObj.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimObj.Object->GetAnimBlueprintGeneratedClass());
	}

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	LentesDisponiveis = 1;

}

// Called when the game starts or when spawned
void APersonagem::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APersonagem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APersonagem::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move", this, &APersonagem::Move);
	PlayerInputComponent->BindAxis("Sides", this, &APersonagem::MoveSides);
	PlayerInputComponent->BindAxis("Turn", this, &APersonagem::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &APersonagem::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

}

int16 APersonagem::GetLentesDisponiveis(){
	return LentesDisponiveis;
}

void APersonagem::SetLentesDisponiveis(int16 NewValue){
	LentesDisponiveis = NewValue;
}

void APersonagem::Move(float Value) {
	//FVector Forward(1.0f, 0.0f, 0.0f);
	//if (Value > 1.0f) {
		//Value = 1.0f;
	//}
	if (Controller != NULL && Value != 0.0f) {
		FRotator Rotation = Controller->GetControlRotation();
		if (GetCharacterMovement()->IsMovingOnGround() ||
			GetCharacterMovement()->IsFalling()) {
			Rotation.Pitch = 0.0f;
		}
		const FVector Direction = FRotationMatrix(Rotation).
			GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);

	}
}

void APersonagem::MoveSides(float Value) {
	//FVector Side(0.0f, 1.0f, 0.0f);
	//if (Value > 1.0f) {
	//	Value = 1.0f;
//	}
	//AddMovementInput(Side, Value);
	if (Controller != NULL && Value != 0.0f) {
		FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}

	
}

bool APersonagem::IsTemArma() {
	return TemArma;
}

void APersonagem::SetTemArma(bool NewValue) {
	TemArma = NewValue;
}

bool APersonagem::IsTemLanterna() {
	return TemLanterna;
}

void APersonagem::SetTemLanterna(bool NewValue) {
	TemLanterna = NewValue;
}
