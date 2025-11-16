#pragma once

namespace TF1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class FormAliado : public System::Windows::Forms::Form
	{
	public:
		FormAliado() {
			InitializeComponent();
			pnlAliado->BackColor = System::Drawing::Color::FromArgb(200, 50, 50, 50);//hace traslucido el panel
			timer1->Enabled = true;
			dialogosAliado = gcnew cli::array<System::String^>(8) {
				"...",
					"Espera... ¿Eres... un humano?",
					"Hace décadas que no veía uno.... tienes muy mala suerte de terminar acá.",
					"Presumo que te dieron la misma misión que a mí... te deseo suerte",
					"Lamentablemente no lo logré y me dejaron encerrado, vagando hasta mi muerte.",
					"Para tu suerte, conozco lo que una de estas maquinas quiere escuchar.",
					"Te daré la respuesta, espero que te sirva",
					"Mucha suerte y escapa, chico."
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
			this->pnlAliado->Location = System::Drawing::Point(0, 472);
			this->pnlAliado->Name = L"pnlAliado";
			this->pnlAliado->Size = System::Drawing::Size(932, 240);
			this->pnlAliado->TabIndex = 0;
			this->pnlAliado->Click += gcnew System::EventHandler(this, &FormAliado::pnlAliado_Click);
			// 
			// lblMensaje
			// 
			this->lblMensaje->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold));
			this->lblMensaje->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->lblMensaje->Location = System::Drawing::Point(30, 49);
			this->lblMensaje->Name = L"lblMensaje";
			this->lblMensaje->Size = System::Drawing::Size(0, 29);
			this->lblMensaje->TabIndex = 1;
			//re asigno pq no funciona por alguna razon
			lblMensaje->BackColor = System::Drawing::Color::FromArgb(0, 50, 50, 50);
			lblMensaje->AutoSize = false;
			lblMensaje->Width = 800;
			lblMensaje->Height = 500;
			lblMensaje->Text = "";
			lblMensaje->UseCompatibleTextRendering = true;
			lblMensaje->ForeColor = Color::White;
			//hasta aca
			// 
			// lblNombre
			// 
			this->lblNombre->AutoSize = true;
			this->lblNombre->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold));
			this->lblNombre->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->lblNombre->Location = System::Drawing::Point(30, 20);
			this->lblNombre->Name = L"lblNombre";
			this->lblNombre->Size = System::Drawing::Size(52, 29);
			this->lblNombre->TabIndex = 0;
			this->lblNombre->Text = L"\?\?\?";
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &FormAliado::timer1_Tick);
			// 
			// FormAliado
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(932, 703);
			this->Controls->Add(this->pnlAliado);
			this->DoubleBuffered = true;
			this->Name = L"FormAliado";
			this->Text = L"FormAliado";
			this->pnlAliado->ResumeLayout(false);
			this->pnlAliado->PerformLayout();
			this->ResumeLayout(false);

		}
	#pragma endregion

	private: 
	System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		mostrarDialogo(indice);
	}

	System::Void pnlAliado_Click(System::Object^ sender, System::EventArgs^ e) {
		if (dialogoCompleto) {

			indice++;
			if (indice >= dialogosAliado->Length) {
				//aumenta la confianza del jugador
				this->Close();
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
