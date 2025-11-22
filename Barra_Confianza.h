#pragma once
#include "Jugador.h"
namespace TF1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Barra_Confianza
	/// </summary>
	public ref class Barra_Confianza : public System::Windows::Forms::Form
	{
	public:
		Barra_Confianza(Jugador ^ juga)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
			g = this->CreateGraphics();
			canvas = BufferedGraphicsManager::Current;
			buffer = canvas->Allocate(g, this->ClientRectangle);
			jug = juga;
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Barra_Confianza()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ verticalProgressBar;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;
		   Graphics^ g;
		   BufferedGraphicsContext^ canvas;
		   BufferedGraphics^ buffer;
		   Jugador^ jug;
	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->verticalProgressBar = (gcnew System::Windows::Forms::Panel());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// verticalProgressBar
			// 
			this->verticalProgressBar->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->verticalProgressBar->Location = System::Drawing::Point(44, 11);
			this->verticalProgressBar->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->verticalProgressBar->Name = L"verticalProgressBar";
			this->verticalProgressBar->Size = System::Drawing::Size(55, 430);
			this->verticalProgressBar->TabIndex = 2;
			this->verticalProgressBar->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Barra_Confianza::verticalProgressBar_Paint);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &Barra_Confianza::timer1_Tick);
			// 
			// Barra_Confianza
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(498, 452);
			this->Controls->Add(this->verticalProgressBar);
			this->Name = L"Barra_Confianza";
			this->Text = L"Barra_Confianza";
			this->Load += gcnew System::EventHandler(this, &Barra_Confianza::Barra_Confianza_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (this->IsDisposed || !this->IsHandleCreated || this->timer1 == nullptr || !this->timer1->Enabled)
			return;
		Graphics^ gBuffer = buffer->Graphics;
		gBuffer->Clear(Color::White);
		this->verticalProgressBar->Invalidate();
		buffer->Render(g);

	}
	private: System::Void Barra_Confianza_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void verticalProgressBar_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		int altura = verticalProgressBar->Height;
		int rellenar = jug->getConfianza()*0.5;
		e->Graphics->FillRectangle(Brushes::LightGreen, 0, altura - rellenar, verticalProgressBar->Width, rellenar);
	}
	};
}
