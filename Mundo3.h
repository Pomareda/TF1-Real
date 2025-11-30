#pragma once
#include <Windows.h>      
#include <mmsystem.h>     
#pragma comment(lib, "winmm.lib")

#include "Boss.h"
#include "Cables.h"
#include "Bala.h" //bala ya incluye a jugador, no lo llamo 2veces
#include "USB.h"
#include "File.h"
#include "FormScores.h"
#include "Game_Over3.h"
#include "Victoria.h"

namespace Mundo3 {

	using namespace System::Drawing;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;


	public ref class Mundo3 : public System::Windows::Forms::Form
	{
	public:
		Mundo3(int idJugador) {
			InitializeComponent();
			idJugadorActual = idJugador;
			timer1->Enabled = true;
			timer2->Enabled = true;
			rand = gcnew Random(Guid::NewGuid().GetHashCode()); //indefendible, esto debe ser puesto como sacado de ia

			g = this->CreateGraphics();
			canvas = BufferedGraphicsManager::Current;
			buffer = canvas->Allocate(g, this->ClientRectangle);

			boss = gcnew Boss(0, 0, 770, 380, 600);
			bmpBoss = gcnew Bitmap("Imagenes/mundo3/Boss.png");
			bmpBoss->MakeTransparent(bmpBoss->GetPixel(0, 0));

			plataformas = gcnew System::Collections::Generic::List<Plataforma^>();
			bmpPlataforma = gcnew Bitmap("Imagenes/mundo3/Plataforma.png");
			bmpPlataforma->MakeTransparent(bmpPlataforma->GetPixel(0, 0));
			plataformas->Add(gcnew Plataforma(40, 270, 200, 55, 0, true));
			plataformas->Add(gcnew Plataforma(290, 320, 200, 60, 0, true));
			plataformas->Add(gcnew Plataforma(550, 300, 200, 65, 1, false));

			balas = gcnew System::Collections::Generic::List<Bala^>();
			bmpBala = gcnew Bitmap("Imagenes/mundo3/Bala.png");
			bmpBala->MakeTransparent(bmpBala->GetPixel(0, 0));

			bmpJugador = gcnew Bitmap("Imagenes/mundo3/Jugador.png");
			jugador = gcnew JugadorM3(bmpJugador);

			bmpCable = gcnew Bitmap("Imagenes/mundo3/Cables.png");
			bmpCable->MakeTransparent(bmpCable->GetPixel(0, 0));
			cable = gcnew Cables(bmpCable->Width / 5, bmpCable->Height);

			bmpAdvertencia = gcnew Bitmap("Imagenes/mundo3/Advertencia.png");

			bmpFondo = gcnew Bitmap("Imagenes/mundo3/Fondo.png"); //para el primer dibujo en el tick1

			USBs = gcnew System::Collections::Generic::List<USB^>();
			bmpUSB = gcnew Bitmap("Imagenes/mundo3/USB.png");
			bmpUSBinvertido = gcnew Bitmap("Imagenes/mundo3/USB.png");
			bmpUSBinvertido->RotateFlip(RotateFlipType::Rotate180FlipY);
			bmpUSB->MakeTransparent(bmpUSB->GetPixel(0, 0));

			//IA:
			//---------------------------------------------------------------------------------------------------------------------
			mciSendStringA("close all", NULL, 0, NULL);

			// "Imagenes\\mundo3\\..." = Entrar a la carpeta de recursos
			String^ rutaRelativa = System::Windows::Forms::Application::StartupPath + "\\..\\..\\Imagenes\\mundo3\\Soundtrack.wav";

			// GetFullPath limpia los ".." y crea una ruta perfecta tipo C:\Users\...\

            String^ rutaAbsoluta = System::IO::Path::GetFullPath(rutaRelativa);

			// 2. Comando Open (igual que antes)
			String^ comandoOpen = "open \"" + rutaAbsoluta + "\" alias MiMusica";

			// Conversión y ejecución (igual que antes)
			char* comandoChars = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(comandoOpen);
			int errorOpen = mciSendStringA(comandoChars, NULL, 0, NULL);
			System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr(comandoChars));

			if (errorOpen != 0) {
				// Mensaje de error para saber dónde buscó si falla
				char errorText[128];
				mciGetErrorStringA(errorOpen, errorText, 128);
				MessageBox::Show("No encuentro el audio en:\n" + rutaAbsoluta + "\n\nError: " + gcnew String(errorText));
			}
			else {
				int errorPlay = mciSendStringA("play MiMusica repeat", NULL, 0, NULL);
				if (errorPlay != 0) {
					mciSendStringA("play MiMusica", NULL, 0, NULL);
				}
			}

			// --- ACTUALIZACIÓN TAMBIÉN PARA EL DISPARO ---
			// Hacemos lo mismo para el disparo para que no falle
			String^ rutaDisparo = System::Windows::Forms::Application::StartupPath + "\\..\\..\\Imagenes\\mundo3\\Disparo.wav";
			sonidoDisparo = gcnew System::Media::SoundPlayer(System::IO::Path::GetFullPath(rutaDisparo));
			sonidoDisparo->LoadAsync();
			//---------------------------------------------------------------------------------------------------------------------	
			
			try {
				FileParametersMundo3* fileParams = new FileParametersMundo3();

				int platX[5] = { 40, 290, 550 };
				int platY[5] = { 270, 320, 300 };

				fileParams->GuardarConfiguracion(600, 3, platX, platY);
				delete fileParams;
			}
			catch (...) {}



		}

		Mundo3(){}

	protected:

		~Mundo3()
		{
			mciSendStringA("close MiMusica", NULL, 0, NULL);
			if (components)
			{
				delete components;
			}
		}
	private:
		bool teclaDisparo = false;
		bool acabar = false;
		int cooldown = 0; //ms entre disparos
		int cooldownCables = 5; //ms entre aparicion de cables
		int cooldownSpawnUSB = 5; // ms entre aparicion de USB

		System::ComponentModel::IContainer^ components;
		System::Windows::Forms::Timer^ timer1;
		System::Windows::Forms::Timer^ timer2;

		Boss^ boss;
		JugadorM3^ jugador;
		Cables^ cable;

		System::Collections::Generic::List<Plataforma^>^ plataformas;
		System::Collections::Generic::List<Bala^>^ balas;
		System::Collections::Generic::List<USB^>^ USBs;
		System::Media::SoundPlayer^ sonidoDisparo;


		Random^ rand;
		Graphics^ g;
		BufferedGraphicsContext^ canvas;
		BufferedGraphics^ buffer;

		Bitmap^ bmpBoss;
		Bitmap^ bmpPlataforma;
		Bitmap^ bmpJugador;
		Bitmap^ bmpBala;
		Bitmap^ bmpCable;
		Bitmap^ bmpAdvertencia;
		Bitmap^ bmpUSB;
		Bitmap^ bmpUSBinvertido;
		Bitmap^ bmpFondo;
		Game_Over3^ gameOver;

		int tiempoTranscurrido = 0;
		int ticksTimer = 0;
		int danoTotalAlBoss = 0;
		int idJugadorActual;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Interval = 40;
			this->timer1->Tick += gcnew System::EventHandler(this, &Mundo3::timer1_Tick);
			// 
			// timer2
			// 
			this->timer2->Interval = 200;
			this->timer2->Tick += gcnew System::EventHandler(this, &Mundo3::timer2_Tick);
			// 
			// Mundo3
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::Color::DimGray;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(782, 503);
			this->Name = L"Mundo3";
			this->RightToLeftLayout = true;
			this->Text = L"Mundo3";
			this->Load += gcnew System::EventHandler(this, &Mundo3::Mundo3_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Mundo3::Mundo3_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Mundo3::Mundo3_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion

	private:
		System::Void Mundo3_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			switch (e->KeyCode) {
			case Keys::W:
				jugador->liberarSalto();
				break;
			case Keys::A:
				jugador->setIzquierda(true);
				break;
			case Keys::D:
				jugador->setDerecha(true);
				break;
			case Keys::E:
				teclaDisparo = true;
				jugador->setDisparando(true);
				break;
			}
		}

		System::Void Mundo3_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			switch (e->KeyCode)
			{
			case Keys::A:
				jugador->setIzquierda(false);
				break;
			case Keys::D:
				jugador->setDerecha(false);
				break;
			case Keys::E:
				teclaDisparo = false;
				jugador->setDisparando(false);
				break;
			}
		}

		//--------------------------------------------------------------

		System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {

			ticksTimer++;
			if (ticksTimer >= 25) { // 25 ticks = 1 segundo (40ms * 25 = 1000ms)
				tiempoTranscurrido++;
				ticksTimer = 0;
			}

			//100 ms
			Graphics^ gBuffer = buffer->Graphics;
			//imagen de fondo
			gBuffer->DrawImage(bmpFondo, 0, 0, 800, 550);

			//BOSS:
			gBuffer->DrawImage(bmpBoss, boss->getX(), boss->getY(), boss->getAncho(), boss->getAlto());

			//PLATAFORMAS:
			for (int i = 0; i < plataformas->Count; i++)
			{
				gBuffer->DrawImage(bmpPlataforma,
					plataformas[i]->getX(),
					plataformas[i]->getY(),
					plataformas[i]->getAncho(),
					plataformas[i]->getAlto());

				//gBuffer->DrawRectangle(Pens::Red, plataformas[i]->getRect()); //rectangulo de las plataformas para pruebas
			}

			//JUGADOR:
			jugador->aplicarGravedad();
			jugador->mover();
			jugador->reiniciarPosicion();// si se cae, reinicia posición

			System::Drawing::Rectangle porcionAUsar = System::Drawing::Rectangle(
				jugador->getIDX() * jugador->getAncho(),
				jugador->getIDY() * jugador->getAlto(),
				jugador->getAncho(),
				jugador->getAlto()
			);
			System::Drawing::Rectangle destino = System::Drawing::Rectangle(
				jugador->getX(),
				jugador->getY(),
				jugador->getAncho(),
				jugador->getAlto()
			);
			gBuffer->DrawImage(bmpJugador, destino, porcionAUsar, GraphicsUnit::Pixel);
			//dibujar vida del jugaador:
			gBuffer->FillRectangle(Brushes::Green, System::Drawing::Rectangle(jugador->getX(), jugador->getY() - 15, 3 * jugador->getVida() / 4, 10));

			//dibujar rectagulo de jugador para pruebas
			//gBuffer->DrawRectangle(Pens::Blue, jugador->getRect());

			bool inter = false;
			for (int i = 0; i < plataformas->Count; i++) {
				if (jugador->getRect().IntersectsWith(plataformas[i]->getRect())) {

					//intersección por arriba:
					if (jugador->getY() + jugador->getAlto() <= plataformas[i]->getY() + 22 && jugador->getVelY() > 0) {

						jugador->setVelY(0);
						jugador->setY(plataformas[i]->getY() - jugador->getAlto() + 7); // Posicionar justo encima
						jugador->setEnSuelo(true);
					}
					inter = true;
				}
			}
			if (!inter) {
				jugador->setEnSuelo(false); inter = false;
			}

			//USBs
			for (int i = 0; i < USBs->Count; i++) {
				USBs[i]->mover();

				//cambiar direccion del dibujo dependiendo de donde viene
				if (USBs[i]->getdX() < 0)
					gBuffer->DrawImage(bmpUSBinvertido, USBs[i]->getRect());
				else gBuffer->DrawImage(bmpUSB, USBs[i]->getRect());


				// colisión jugador
				if (USBs[i]->esActivo() && jugador->getRect().IntersectsWith(USBs[i]->getRect())) {
					jugador->setVida(jugador->getVida() - 5);
					USBs[i]->setActivo(false);
				}
				//colision balas
				if (balas->Count > 0) {
					for (int j = 0; j < balas->Count; j++) {
						if (USBs[i]->esActivo() && balas[j]->getRect().IntersectsWith(USBs[i]->getRect())) {
							balas->RemoveAt(j);
							USBs[i]->setActivo(false);
							j--;
						}
					}
				}

				// Eliminar inactivos 
				if (!USBs[i]->esActivo()) {
					USBs->RemoveAt(i);
					i--;
				}
			}

			//CABLES:
			if (cable->esActivo()) {
				cable->mover();
				if (cable->esAdvertencia()) {
					gBuffer->DrawImage(bmpAdvertencia, cable->getXPlataforma(), cable->getYFinal(), 100, 100);
				}
				else {
					System::Drawing::Rectangle origen = System::Drawing::Rectangle(
						cable->getIDX() * cable->getAncho(),
						0,
						cable->getAncho(),
						cable->getAlto()
					);

					System::Drawing::Rectangle destino = System::Drawing::Rectangle(
						cable->getX(),
						cable->getY(),
						200,
						1120
					);

					gBuffer->DrawImage(bmpCable, destino, origen, GraphicsUnit::Pixel);
					gBuffer->DrawRectangle(Pens::Black, destino);

					// Lógica de colisión usando el rectángulo visual 'destino'
					if (jugador->getRect().IntersectsWith(destino)) {
						jugador->setVida(jugador->getVida() - 0.5);
					}

					// Colisión con balas
					if (balas->Count > 0) {
						for (int i = 0; i < balas->Count; i++) {
							if (balas[i]->getRect().IntersectsWith(destino)) {
								balas->RemoveAt(i);
								boss->setVida(boss->getVida() - 5);
								danoTotalAlBoss += 5;
								i--;
							}
						}
					}
				}
			}

			//BALAS:
			if (cooldown > 0) {
				cooldown--;
			} //temporizador basicamente

			if (teclaDisparo && cooldown == 0) {
				balas->Add(gcnew Bala(bmpBala, jugador));
				sonidoDisparo->Play();
				cooldown = 5;
			}

			for (int i = 0; i < balas->Count; i++) {
				balas[i]->mover();
				gBuffer->DrawImage(bmpBala, balas[i]->getX(), balas[i]->getY());

				if (!balas[i]->getActiva()) {
					balas->RemoveAt(i);
					i--; // ajustar índice después de eliminar la bala
				}
			}

			//dibujar barra de vida del boss:
			gBuffer->FillRectangle(Brushes::Red, System::Drawing::Rectangle(150, 450, boss->getVida() / 2, 30));

			buffer->Render(g);
		}

		//---------------------------------------------------------------------------------------------------------------------------
		
		System::Void timer2_Tick(System::Object^ sender, System::EventArgs^ e) {
			// 200 ms
			if (jugador->getVida() <= 0) {
				jugador->setIDY(9); //cambio sprite a muerto
				acabar = true;

			}
			else if (boss->getVida() <= 0) {
				acabar = true;
			}

			if (acabar) {
				timer1->Enabled = false;
				timer2->Enabled = false;
				mciSendStringA("stop MiMusica", NULL, 0, NULL);

				try {
					FileScores* fileScores = new FileScores();
					fileScores->GuardarScoreMundo3(
						danoTotalAlBoss,
						jugador->getVida(),
						tiempoTranscurrido,
						idJugadorActual // PASAR EL ID
					);
					delete fileScores;
				}
				catch (...) {}

				if (jugador->getVida() <= 0) {
					gameOver = gcnew Game_Over3();
					gameOver->ShowDialog();
					if (gameOver->GetCondicion() == 1)
					{
						this->Close();
						Mundo3^ mundo3 = gcnew Mundo3(idJugadorActual);
						mundo3->Show();
					}
					else {
						this->Close();
					}
				}
				else {
					Victoria^ vic = gcnew Victoria();
					this->Close();
					vic->ShowDialog();
				}
				FormScores^ formScores = gcnew FormScores();
				formScores->ShowDialog();

				this->Close();
				return;
			}

			//PLATAFORMAS:
			for (int i = 0; i < plataformas->Count; i++)
			{
				plataformas[i]->mover();
			}

			//BOSS:
			boss->mover();

			//Ataque de cables:
			cable->aumentarIdx();
			if (cooldownCables > 0) {
				cooldownCables--;
			}
			else {
				if (!cable->esActivo()) {
					int indicePlataformas = rand->Next(0, plataformas->Count);
					cable->activar(plataformas[indicePlataformas]);

					cooldownCables = 10;
				}
			}

			//Ataques USB:
			if (cooldownSpawnUSB > 0) {
				cooldownSpawnUSB--;
			}
			else {
				int lado = rand->Next(0, 2); //0 izquierda, 1 derecha
				int altura = rand->Next(0, 3); //0 baja, 1 media, 2 alta
				int posY;

				switch (altura) {
				case 0:
					posY = 160;
					break;
				case 1:
					posY = 220;
					break;
				case 2:
					posY = 280;
					break;
				}

				if (lado == 0) {
					USBs->Add(gcnew USB(-50, posY, 15));
				}
				else {
					USBs->Add(gcnew USB(1100, posY, -15));
				}

				cooldownSpawnUSB = 5;
				
			}
		}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Mundo3_Load(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
