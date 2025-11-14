#pragma once
#include "Jugador.h"

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
			bmpPersonajeHumano = gcnew Bitmap("PersonajeHuman.png");
			jugadorHumano = new Jugador(100, 100, bmpPersonajeHumano->Width / 6, bmpPersonajeHumano->Height / 6);
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
		}
	private: 
		System::ComponentModel::IContainer^ components;
		Graphics^ g;
		BufferedGraphicsContext^ canvas;
		BufferedGraphics^ buffer;
		Bitmap^ bmpPersonajeHumano;
		Bitmap^ bmpEnemigoIA;
		Bitmap^ map1;
		Jugador* jugadorHumano;
		System::Windows::Forms::Timer^ timer1;

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
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
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

		switch (e->KeyCode)
		{
		case Keys::W:
			jugadorHumano->setDireccion(Arriba);
			break;
		case Keys::A:
			jugadorHumano->setDireccion(Izquierda);
			break;
		case Keys::S:
			jugadorHumano->setDireccion(Abajo);
			break;
		case Keys::D:
			jugadorHumano->setDireccion(Derecha);
			break;
		default:
			break;
		}

	}
	System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {

		buffer->Graphics->Clear(Color::White);
		jugadorHumano->mover(buffer->Graphics, bmpPersonajeHumano);
		buffer->Graphics->DrawImage(map1, 0, 0, map1->Width, map1->Height);
		jugadorHumano->dibujar(buffer->Graphics, bmpPersonajeHumano);

		buffer->Render(g);
	} 
	System::Void MenuForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		jugadorHumano->setDireccion(Ninguna);
	}
	System::Void MenuForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
