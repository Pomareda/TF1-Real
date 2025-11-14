#pragma once
#include "Controladora.h"

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
			control = new Controladora();

			bmpPersonajeHumano = gcnew Bitmap("PersonajeHuman.png");
			bmpEnemigoIA = gcnew Bitmap("EnemigoIA.png");
			
			Jugador* jugadorPtr = control->getJugador();

			Enemigo* enemigo1 = new Enemigo(80, 180, 0, 0);
			control->agregarEnemigo(enemigo1);

			map1 = gcnew Bitmap("Mapa1.png");
			bmpPersonajeHumano->MakeTransparent(bmpPersonajeHumano->GetPixel(0, 0));

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
		Bitmap^ map1;
		Controladora* control;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MenuForm::timer1_Tick);
			// 
			// MenuForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1600, 779);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MenuForm";
			this->Text = L"MenuForm";
			this->Load += gcnew System::EventHandler(this, &MenuForm::MenuForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MenuForm::MenuForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MenuForm::MenuForm_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	
	private: 
	System::Void MenuForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		Jugador* jugadorPtr = control->getJugador();
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
		default:
			break;
		}
	}

	System::Void MenuForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		control->getJugador()->setDireccion(Ninguna);
	}

	System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {

		Graphics^ gBuffer = buffer->Graphics;

		gBuffer->Clear(Color::White);
		gBuffer->DrawImage(map1, 0, 0, this->ClientRectangle.Width, this->ClientRectangle.Height);

		control->moverJugador(gBuffer, bmpPersonajeHumano);
		control->moverEnemigos(gBuffer, bmpEnemigoIA);


		control->dibujarEntidades(gBuffer, bmpPersonajeHumano, bmpEnemigoIA);

		buffer->Render(g);
	} 

	private: System::Void MenuForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
