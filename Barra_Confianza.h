#pragma once
#include "Jugador.h"
#include "Minimapa.h"
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
		Barra_Confianza(Jugador^ juga, Minimapa^ mini, int anchoMapa, int altoMapa)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
			g = this->CreateGraphics();
			canvas = BufferedGraphicsManager::Current;
			buffer = canvas->Allocate(g, this->ClientRectangle);
			jug = juga;
			minimapa = mini;
			mapaAncho = anchoMapa;
			mapaAlto = altoMapa;
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
		   Minimapa^ minimapa;
		   int mapaAncho;
	private: System::Windows::Forms::Panel^ panelMinimapa;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
		   int mapaAlto;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Barra_Confianza::typeid));
			this->verticalProgressBar = (gcnew System::Windows::Forms::Panel());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->panelMinimapa = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
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
			// panelMinimapa
			// 
			this->panelMinimapa->BackColor = System::Drawing::Color::Transparent;
			this->panelMinimapa->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panelMinimapa.BackgroundImage")));
			this->panelMinimapa->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->panelMinimapa->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panelMinimapa->Location = System::Drawing::Point(127, 12);
			this->panelMinimapa->Name = L"panelMinimapa";
			this->panelMinimapa->Size = System::Drawing::Size(580, 404);
			this->panelMinimapa->TabIndex = 3;
			this->panelMinimapa->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Barra_Confianza::panelMinimapa_Paint);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(773, 54);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(106, 16);
			this->label1->TabIndex = 4;
			this->label1->Text = L"JUGADOR (TU):";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(773, 159);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(81, 16);
			this->label2->TabIndex = 5;
			this->label2->Text = L"ENEMIGOS:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(773, 272);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(55, 16);
			this->label3->TabIndex = 6;
			this->label3->Text = L"ALIADO";
			// 
			// Barra_Confianza
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1025, 452);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->panelMinimapa);
			this->Controls->Add(this->verticalProgressBar);
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"Barra_Confianza";
			this->Text = L"Barra_Confianza";
			this->Load += gcnew System::EventHandler(this, &Barra_Confianza::Barra_Confianza_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Barra_Confianza::Barra_Confianza_KeyDown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (this->IsDisposed || !this->IsHandleCreated || this->timer1 == nullptr || !this->timer1->Enabled)
			return;

		Graphics^ gBuffer = buffer->Graphics;
		gBuffer->Clear(Color::White);

		// Dibujar en el buffer, no en 'g'
		gBuffer->DrawRectangle(Pens::Black, 600, 155, 20, 20);
		gBuffer->FillRectangle(Brushes::Blue, 600, 155, 20, 20);

		gBuffer->DrawEllipse(Pens::Black, 600, 70, 20, 20);
		gBuffer->FillEllipse(Brushes::Red, 600, 70, 20, 20);

		cli::array<Point>^ puntosTriangulo = gcnew cli::array<Point>(3) {
			Point(610, 240),
				Point(630, 260),
				Point(590, 260)
		};
		gBuffer->DrawPolygon(Pens::Black, puntosTriangulo);
		SolidBrush^ brush = gcnew SolidBrush(Color::Green);

		gBuffer->FillPolygon(brush, puntosTriangulo);
		minimapa->actualizar(jug->getX() + 20, jug->getY() + 5, mapaAncho, mapaAlto, panelMinimapa->Width, panelMinimapa->Height);
		this->verticalProgressBar->Invalidate();
		this->panelMinimapa->Invalidate();

		buffer->Render(g); // renderiza el contenido del buffer al formulario
	}
	private: System::Void Barra_Confianza_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void verticalProgressBar_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		int altura = verticalProgressBar->Height;
		int rellenar = jug->getConfianza() * 0.5;
		e->Graphics->FillRectangle(Brushes::LightGreen, 0, altura - rellenar, verticalProgressBar->Width, rellenar);
	}
	private: System::Void panelMinimapa_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {

		e->Graphics->DrawRectangle(Pens::Black, 0, 0, panelMinimapa->Width - 1, panelMinimapa->Height - 1);

		e->Graphics->DrawRectangle(Pens::Black, 280, 21, 10, 10);
		e->Graphics->FillRectangle(Brushes::Blue, 280, 21, 10, 10);

		e->Graphics->DrawRectangle(Pens::Black, 400, 227, 10, 10);
		e->Graphics->FillRectangle(Brushes::Blue, 400, 227, 10, 10);

		e->Graphics->DrawRectangle(Pens::Black, 84, 102, 10, 10);
		e->Graphics->FillRectangle(Brushes::Blue, 84, 102, 10, 10);

		e->Graphics->DrawRectangle(Pens::Black, 80, 253, 10, 10);
		e->Graphics->FillRectangle(Brushes::Blue, 80, 253, 10, 10);

		e->Graphics->DrawRectangle(Pens::Black, 205, 288, 10, 10);
		e->Graphics->FillRectangle(Brushes::Blue, 205, 288, 10, 10);


		cli::array<Point>^ puntosTriangulo = gcnew cli::array<Point>(3) {
			Point(120, 300),
				Point(125, 309),
				Point(115, 309)
		};
		e->Graphics->DrawPolygon(Pens::Black, puntosTriangulo);
		SolidBrush^ brush = gcnew SolidBrush(Color::Green);

		e->Graphics->FillPolygon(brush, puntosTriangulo);

		minimapa->dibujar(e->Graphics);
	}
	private: System::Void Barra_Confianza_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::Tab) {
			this->Close();
		}
	}
	};
}
