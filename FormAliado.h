#pragma once
#include "Jugador.h"

namespace TF1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class FormAliado : public System::Windows::Forms::Form
	{
		Jugador^ jugadorPtr;
	public:
		FormAliado(Jugador^ j) {
			InitializeComponent();
			pnlAliado->BackColor = System::Drawing::Color::FromArgb(200, 50, 50, 50);//hace traslucido el panel
			lblMensaje->BackColor = System::Drawing::Color::FromArgb(0, 50, 50, 50); //hace traslucido el mensaje del aliado
			
			lblMensaje->AutoSize = false;
			lblMensaje->Width = 700;
			lblMensaje->Height = 200;

			this->jugadorPtr = j;

			timer1->Enabled = true;
			dialogosAliado = gcnew cli::array<System::String^>(8) {
				"...",
					"Espera... ¿Eres... un humano?",
					"Hace décadas que no veía uno.... tienes muy mala suerte de terminar aquí muchacho",
					"Presumo que te dieron la misma misión que a mí... te deseo suerte",
					"Lamentablemente no lo logré y me dejaron encerrado aqui, vagando hasta mi muerte",
					"Para tu suerte, conozco lo que una de estas maquinas quiere escuchar",
					"Te daré la respuesta, espero que te sirva",
					"Mucha suerte y escapa, chico"
			};
		}

		bool mostrarDialogo(int indiceDialogo) {
			if (indiceChar < dialogosAliado[indiceDialogo]->Length) {
				lblMensaje->Text += dialogosAliado[indiceDialogo][indiceChar];
				indiceChar++;
				/*
				if(indiceChar == 15) {
					lblMensaje->Text += "\n"; // salto de línea si llega al indice 35
				}
				*/
				return true; 
			}
			else {
				timer1->Enabled = false;
				dialogoCompleto = true;
				return false; 
			}
		}

	protected:
		~FormAliado()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		cli::array<System::String^>^ dialogosAliado;
		System::Windows::Forms::Panel^ pnlAliado;
		System::Windows::Forms::Label^ lblNombre;
		System::Windows::Forms::Label^ lblMensaje;
		System::Windows::Forms::Timer^ timer1;
		System::ComponentModel::IContainer^ components;
		bool dialogoCompleto = false;
		int indiceChar = 0;
		int indice = 0;

	#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(FormAliado::typeid));
			this->pnlAliado = (gcnew System::Windows::Forms::Panel());
			this->lblMensaje = (gcnew System::Windows::Forms::Label());
			this->lblNombre = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->pnlAliado->SuspendLayout();
			this->SuspendLayout();
			// 
			// pnlAliado
			// 
			this->pnlAliado->Controls->Add(this->lblMensaje);
			this->pnlAliado->Controls->Add(this->lblNombre);
			this->pnlAliado->Location = System::Drawing::Point(0, 384);
			this->pnlAliado->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->pnlAliado->Name = L"pnlAliado";
			this->pnlAliado->Size = System::Drawing::Size(699, 195);
			this->pnlAliado->TabIndex = 0;
			// 
			// lblMensaje
			// 
			this->lblMensaje->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold));
			this->lblMensaje->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->lblMensaje->Location = System::Drawing::Point(22, 40);
			this->lblMensaje->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblMensaje->Name = L"lblMensaje";
			this->lblMensaje->Size = System::Drawing::Size(0, 24);
			this->lblMensaje->TabIndex = 1;
			// 
			// lblNombre
			// 
			this->lblNombre->AutoSize = true;
			this->lblNombre->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold));
			this->lblNombre->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->lblNombre->Location = System::Drawing::Point(22, 16);
			this->lblNombre->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblNombre->Name = L"lblNombre";
			this->lblNombre->Size = System::Drawing::Size(43, 24);
			this->lblNombre->TabIndex = 0;
			this->lblNombre->Text = L"\?\?\?";
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &FormAliado::timer1_Tick);
			// 
			// FormAliado
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(699, 571);
			this->Controls->Add(this->pnlAliado);
			this->DoubleBuffered = true;
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->Name = L"FormAliado";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"FormAliado";
			this->Click += gcnew System::EventHandler(this, &FormAliado::FormAliado_Click);
			this->pnlAliado->ResumeLayout(false);
			this->pnlAliado->PerformLayout();
			this->ResumeLayout(false);

		}
	#pragma endregion

	private: 
	System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		mostrarDialogo(indice);
	}
	
private: System::Void FormAliado_Click(System::Object^ sender, System::EventArgs^ e) {
	if (dialogoCompleto) {

		indice++;
		if (indice >= dialogosAliado->Length) {
			this->Close();
			if (dialogoCompleto == true) {
				jugadorPtr->setConfianza(jugadorPtr->getConfianza() + 120);
			}

			return;
		}
		//resetear
		dialogoCompleto = false;
		indiceChar = 0;
		lblMensaje->Text = "";
		timer1->Enabled = true;
	}
	else {
		timer1->Enabled = false;
		//mostrar todo el dialogo de una vez
		lblMensaje->Text = dialogosAliado[indice];
		dialogoCompleto = true;
	}
}
};
}
