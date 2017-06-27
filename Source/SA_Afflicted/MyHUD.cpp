#include "SA_Afflicted.h"
#include "MyHUD.h"
#include "Personagem.h"

AMyHUD::AMyHUD() {

	//Carrega uma fonte disponível na Engine
	ConstructorHelpers::FObjectFinder<UFont> LoadFont
	(TEXT("Font'/Engine/EngineFonts/Roboto.Roboto'"));
	//Verifica se conseguiu carregar a fonte
	if (LoadFont.Succeeded()) {
		//Atribui a fonte obtida para a variável BaseFont.
		BaseFont = LoadFont.Object;
	}

	//Carrega a textura (imagem) referente a vida
	ConstructorHelpers::FObjectFinder<UTexture2D> LoadTexture
	(TEXT("Texture2D'/Game/SA_things/Life.Life'"));
	//Verifica se conseguiu carregar a textura (imagem)
	if (LoadTexture.Succeeded()) {
		//Atribui a textura obtida para a variável LifeTexture.
		LifeTexture = LoadTexture.Object;
	}

	MostrarLife = true;
	CorFonte = FLinearColor(1.0f, 1.0f, 1.0f, 0.0f);

}

void AMyHUD::DrawHUD() {
	//Chama o método DrawHUD da superclasse.
	Super::DrawHUD();

	//Obter o tamanho da tela
	FVector2D ScreenDimensions = FVector2D(Canvas->SizeX,
		Canvas->SizeY);


	//Obter o Pawn que está sendo controlado pelo Player
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (Pawn) {
		//Realiza o cast de Pawn para Personagem
		APersonagem* Personagem = Cast<APersonagem>(Pawn);
		if (Personagem) {

			//Definir o que será escrito na tela
			//É necessário criar FStrings
			//https://wiki.unrealengine.com/Logs,_Printing_Messages_To_Yourself_During_Runtime

			//Desenha a string referente a vida do personagem, com cor
			//vermelha, nas posições X = 200 e Y = 50, utilizando a fonte
			//BaseFont com escala 2.0
			//DrawText(LifeString, FColor::Red, 200, 50, BaseFont, 2.0f);

			DesenharTexto();

			if (MostrarTexto) {
				switch (Texto) {
				case 0:
					DrawText(FString::Printf(TEXT("Basta usar o botão direito do mouse para interagir com sua lanterna."), 10), CorFonte, ScreenDimensions.X / 2 - 400, 100, BaseFont, 2.0f);
					break;
				case 1:
					DrawText(FString::Printf(TEXT("Agora você pode atirar corações com o botão esquerdo do mouse para derrotar seus inimigos."), 10), CorFonte, ScreenDimensions.X / 2 - 550, 200, BaseFont, 2.0f);
					break;
				case 2:
					DrawText(FString::Printf(TEXT("Parabens, você percebeu que pode fazer os inimigos aparecerem com diferentes cores de luz."), 10), CorFonte, ScreenDimensions.X / 2 - 550, 200, BaseFont, 2.0f);
					break;
				case 3:
					DrawText(FString::Printf(TEXT("Cuidado... O mal está à espreita, seja forte!"), 10), CorFonte, ScreenDimensions.X / 2 - 200, 200, BaseFont, 2.0f);
					break;
				case 4:
					DrawText(FString::Printf(TEXT("Muito bem! Você acaba de destruir o monstro do estresse, continue assim!"), 10), CorFonte, ScreenDimensions.X / 2 - 420, 200, BaseFont, 2.0f);
					break;
				case 5:
					DrawText(FString::Printf(TEXT("Você acaba de coletar uma nova lente, agora você tem mais uma cor de luz disponível."), 10), CorFonte, ScreenDimensions.X / 2 - 500, 200, BaseFont, 2.0f);
					break;
				case 6:
					DrawText(FString::Printf(TEXT("Prepare-se para enfrentar seu pior pesadelo! Seja forte, falta pouco para vencermos!"), 10), CorFonte, ScreenDimensions.X / 2 - 500, 200, BaseFont, 2.0f);
					break;
				case 7:
					DrawText(FString::Printf(TEXT("Parabéns, você conseguiu superar todos os males da depressão!"), 10), CorFonte, ScreenDimensions.X / 2 - 300, 200, BaseFont, 2.0f);
					break;
				case 8:
					DrawText(FString::Printf(TEXT("Agora você conhece um pouco melhor sobre essa terrível doença e sabe que pode ser superada."), 10), CorFonte, ScreenDimensions.X / 2 - 550, 200, BaseFont, 2.0f);
					break;
				case 9:
					DrawText(FString::Printf(TEXT("Vamos melhorar o mundo? Se cada um fizer sua parte, podemos sim construir um mundo melhor..."), 10), CorFonte, ScreenDimensions.X / 2 - 550, 200, BaseFont, 2.0f);
					break;
				case 10:
					DrawText(FString::Printf(TEXT("E mais feliz. =)"), 10), CorFonte, ScreenDimensions.X / 2 - 100, 200, BaseFont, 2.0f);
					break;
				}
			}
			

			if (MostrarLife) {
				float TamanhoBarra = Personagem->GetLife() * (20.0f*0.3f);
				float PositionX = ScreenDimensions.X/2.0f;
				for (int i = 0; i < Personagem->GetLife(); i++) {
					DrawTextureSimple(LifeTexture, PositionX - (TamanhoBarra/2.0f), 20, 0.3f);
					PositionX += 6.0f;
				}
			}
		}
	}
}

void AMyHUD::AtivarTexto(int8 Text)
{
	Texto = Text;
	MostrarTexto = true;
	UE_LOG(LogTemp, Warning, TEXT("Chamou Ativar Texto."));
}

void AMyHUD::DesenharTexto() {
	if (MostrarTexto) {
		if (Loop == 0) {
			Opacidade += 0.03f;
			if (Opacidade >= 1.0f) {
				Loop = 1;
			}
		} else if (Loop == 1) {
			Contador++;
			if (Contador == 200) {
				Loop = 2;
			}
		} else if (Loop == 2) {
			Opacidade -= 0.03f;
			if (Opacidade <= 0.0f) {
				Loop = 0;
				Contador = 0;
				if (Texto == 7 || Texto == 8 || Texto == 9) {
					Texto++;
				} else if (Texto == 10) {
					//VITORIA ---------- VITORIA ---------- VITORIA ---------- VITORIA  (TELA FINAL)
				} else {
					MostrarTexto = false;
				}
			}
		}
		CorFonte.A = Opacidade;
	}
}