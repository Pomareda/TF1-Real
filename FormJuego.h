#pragma once
#include "Controladora.h"
//#include "Mapas.h"

namespace TF1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MenuForm : public System::Windows::Forms::Form
	{
	public:
		MenuForm(void)
		{
			InitializeComponent();
			g = this->CreateGraphics();
			canvas = BufferedGraphicsManager::Current;
			buffer = canvas->Allocate(g, this->ClientRectangle);

			map1 = gcnew Bitmap("Imagenes/Mapa1.png");
			bmpPersonajeHumano = gcnew Bitmap("Imagenes/PersonajeHuman.png");
			bmpEnemigoIA = gcnew Bitmap("Imagenes/EnemigoIA.png");
			bmpRecurso = gcnew Bitmap("Imagenes/Recurso.png");
			bmpAliado = gcnew Bitmap("Imagenes/Aliado.png");

			bmpPersonajeHumano->MakeTransparent(bmpPersonajeHumano->GetPixel(0, 0));
			control = gcnew Controladora(bmpPersonajeHumano, this->ClientRectangle.Width, this->ClientRectangle.Height);
			Jugador^ jugadorPtr = control->getJugador();
			Enemigo^ enemigo1 = gcnew Enemigo(170, 170, 0, 0);
			Enemigo^ enemigo2 = gcnew Enemigo(10, 110, 0, 0);
			Enemigo^ enemigo3 = gcnew Enemigo(470, 540, 0, 0);
			Enemigo^ enemigo4 = gcnew Enemigo(655, 20, 0, 0);
			Enemigo^ enemigo5= gcnew Enemigo(940, 390, 0, 0);

			control->agregarEnemigo(enemigo1);
			control->agregarEnemigo(enemigo2);
			control->agregarEnemigo(enemigo3);
			control->agregarEnemigo(enemigo4);
			control->agregarEnemigo(enemigo5);

			cant_recursos = 0;
		}

	protected:
		~MenuForm()
		{
			if (components)
			{
				delete components;
			}
			delete control;
		}
	private: 
		System::ComponentModel::IContainer^ components;
		System::Windows::Forms::Timer^ timer1;
		Graphics^ g;
		BufferedGraphicsContext^ canvas;
		BufferedGraphics^ buffer;
		Bitmap^ bmpPersonajeHumano;
		Bitmap^ bmpEnemigoIA;
		Bitmap^ bmpRecurso;
		Bitmap^ map1;
		Bitmap^ bmpAliado;
		int cant_recursos;

	private: System::Windows::Forms::Panel^ verticalProgressBar;

		   Controladora^ control;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->verticalProgressBar = (gcnew System::Windows::Forms::Panel());
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MenuForm::timer1_Tick);
			// 
			// verticalProgressBar
			// 
			this->verticalProgressBar->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->verticalProgressBar->Location = System::Drawing::Point(1467, 39);
			this->verticalProgressBar->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->verticalProgressBar->Name = L"verticalProgressBar";
			this->verticalProgressBar->Size = System::Drawing::Size(55, 700);
			this->verticalProgressBar->TabIndex = 1;
			this->verticalProgressBar->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MenuForm::verticalProgressBar_Paint);
			// 
			// MenuForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1582, 753);
			this->Controls->Add(this->verticalProgressBar);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MenuForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MenuForm";
			this->Load += gcnew System::EventHandler(this, &MenuForm::MenuForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MenuForm::MenuForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MenuForm::MenuForm_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	
	private: 
	System::Void MenuForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		Jugador^ jugadorPtr = control->getJugador();
		switch (e->KeyCode)
		{
		case Keys::W:
			jugadorPtr->setDireccion(Arriba);
			break;
		case Keys::A:
			jugadorPtr->setDireccion(Izquierda);
			break;
		case Keys::S:
			jugadorPtr->setDireccion(Abajo);
			break;
		case Keys::D:
			jugadorPtr->setDireccion(Derecha);
			break;
		case Keys::E:		
			control->dialogoConIA();
			control->interactuarAliado();
			break;
		
		/*default:
			break;*/
		}
	}
	System::Void MenuForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		control->getJugador()->setDireccion(Ninguna);
	}

	System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		//logica del juego
		Graphics^ gBuffer = buffer->Graphics;

		gBuffer->Clear(Color::White);

		control->actualizarCamara();

		System::Drawing::Drawing2D::GraphicsState^ estadoOriginal = gBuffer->Save();

		control->getCamara()->aplicarTransformacion(gBuffer);
		int mapaAncho = 143 * 8;
		int mapaAlto = 84 * 8;

		gBuffer->DrawImage(map1, 0, 0, mapaAncho, mapaAlto);
		control->moverJugador(gBuffer, bmpPersonajeHumano, mapa1);
		if (cant_recursos < 4) {
			control->crearRecursos(bmpRecurso);
		}
		control->dibujarAliado(gBuffer, bmpAliado);
		control->moverEnemigos(gBuffer, bmpEnemigoIA);
		control->moverRecursos(gBuffer, bmpRecurso);
		control->dibujarEntidades(gBuffer, bmpPersonajeHumano, bmpEnemigoIA, bmpRecurso, mapa1);
		gBuffer->Restore(estadoOriginal);
		this->verticalProgressBar->Invalidate();
		buffer->Render(g);
		cant_recursos++;
	} 

	private: System::Void MenuForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void verticalProgressBar_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		int altura = verticalProgressBar->Height;
		int rellenar = control->getJugador()->getConfianza();

		e->Graphics->FillRectangle(Brushes::LightGreen, 0, altura - rellenar, verticalProgressBar->Width, rellenar);
}
};
}
