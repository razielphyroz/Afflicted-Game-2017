// Fill out your copyright notice in the Description page of Project Settings.

#include "SA_Afflicted.h"
#include "Personagem.h"
#include "LanternaDoJogador.h"



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

	GetCharacterMovement()->MaxWalkSpeed = 800.0f;

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

	bUseControllerRotationPitch = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	Life = 100;

	//LanternaEmUso = ConstructObject<ALanternaDoJogador>(ALanternaDoJogador::StaticClass());

}

// Called when the game starts or when spawned
void APersonagem::BeginPlay()
{
	Super::BeginPlay();
	LentesDisponiveis = 2;

	UWorld* World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParameters;
		LanternaEmUso = World->SpawnActor<ALanternaDoJogador>(GetActorLocation(), GetActorRotation(), SpawnParameters);
	}
}

// Called every frame
void APersonagem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LanternaEmUso->SetActorLocation(FVector(GetActorLocation().X,GetActorLocation().Y,GetActorLocation().Z));
	LanternaEmUso->SetActorRotation(GetActorRotation());
}

// Called to bind functionality to input
void APersonagem::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move", this, &APersonagem::Move);
	PlayerInputComponent->BindAxis("Sides", this, &APersonagem::MoveSides);
	PlayerInputComponent->BindAxis("Turn", this, &APersonagem::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &APersonagem::AddControllerPitchInput);

	PlayerInputComponent->BindAction("CorLant", IE_Pressed, this, &APersonagem::MudarCor);
}

int16 APersonagem::GetLentesDisponiveis()
{
	return LentesDisponiveis;
}

void APersonagem::SetLentesDisponiveis(int16 NewValue)
{
	LentesDisponiveis = NewValue;
}

void APersonagem::Move(float Value)
{
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

void APersonagem::MoveSides(float Value)
{
	if (Controller != NULL && Value != 0.0f) {
		FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void APersonagem::MudarCor()
{
	if (LanternaEmUso != nullptr) {
		LanternaEmUso->MudarCorDaLuz();
	}
}

bool APersonagem::IsTemArma()
{
	return TemArma;
}

void APersonagem::SetTemArma(bool NewValue)
{
	TemArma = NewValue;
}

bool APersonagem::IsTemLanterna()
{
	return TemLanterna;
}

void APersonagem::SetTemLanterna(bool NewValue)
{
	TemLanterna = NewValue;
}

int8 APersonagem::GetLife()
{
	return Life;
}

void APersonagem::SetLife(int8 Value)
{
	Life = Value;
}

void APersonagem::AdicionarCorDisponivel()
{
	if (LanternaEmUso != nullptr) {
		LanternaEmUso->AdicionarCorDisponivel();
	}
}
