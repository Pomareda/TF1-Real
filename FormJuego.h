#pragma once
#include "Controladora.h"
#include "Mapas.h"

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
			map1 = gcnew Bitmap("Mapa1.png");
			bmpPersonajeHumano = gcnew Bitmap("PersonajeHuman.png");
			bmpEnemigoIA = gcnew Bitmap("EnemigoIA.png");

			bmpRecurso = gcnew Bitmap("Recurso.png");

			bmpPersonajeHumano->MakeTransparent(bmpPersonajeHumano->GetPixel(0, 0));
			control = gcnew Controladora(bmpPersonajeHumano);
			Jugador^ jugadorPtr = control->getJugador();
			Enemigo^ enemigo1 = gcnew Enemigo(80, 180, 0, 0);
			control->agregarEnemigo(enemigo1);
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
			this->verticalProgressBar->Location = System::Drawing::Point(1100, 32);
			this->verticalProgressBar->Margin = System::Windows::Forms::Padding(2);
			this->verticalProgressBar->Name = L"verticalProgressBar";
			this->verticalProgressBar->Size = System::Drawing::Size(42, 569);
			this->verticalProgressBar->TabIndex = 1;
			this->verticalProgressBar->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MenuForm::verticalProgressBar_Paint);
			// 
			// MenuForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1200, 633);
			this->Controls->Add(this->verticalProgressBar);
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
		gBuffer->DrawImage(map1, 0, 0, this->ClientRectangle.Width, this->ClientRectangle.Height);
		control->moverJugador(gBuffer, bmpPersonajeHumano, mapa1);
		if (cant_recursos < 4) {
			control->crearRecursos(bmpRecurso);
		}

		control->moverEnemigos(gBuffer, bmpEnemigoIA);
		control->moverRecursos(gBuffer, bmpRecurso);
		control->dibujarEntidades(gBuffer, bmpPersonajeHumano, bmpEnemigoIA, bmpRecurso, mapa1);
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
