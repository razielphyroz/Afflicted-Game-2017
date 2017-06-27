#pragma once

#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
*
*/
UCLASS()
class SA_AFFLICTED_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:

	//Construtor da classe
	AMyHUD();

	//Sobrescrita do método responsável por desenhar o HUD
	virtual void DrawHUD() override;

	void AtivarTexto(int8 Text);

private:	
	
	UPROPERTY(EditAnywhere)
		UFont* BaseFont;

	UPROPERTY(EditAnywhere)
		UTexture2D* LifeTexture;
	
	float Opacidade;
	bool MostrarLife;
	int8 Texto;
	bool MostrarTexto;
	int16 Contador;
	int8 Loop;
	void DesenharTexto();
	FLinearColor CorFonte;
};