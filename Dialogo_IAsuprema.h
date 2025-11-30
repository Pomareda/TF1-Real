#pragma once
#include "IA_suprema_hablando.h"
namespace TF1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Media;
	/// <summary>
	/// Resumen de Dialogo_IAsuprema
	/// </summary>
	public ref class Dialogo_IAsuprema : public System::Windows::Forms::Form
	{
	public:
		Dialogo_IAsuprema()
		{
			InitializeComponent();
			g1 = this->CreateGraphics();
			canvas = BufferedGraphicsManager::Current;
			buffer = canvas->Allocate(g1, this->ClientRectangle);
			pnl_Suprema->BackColor = System::Drawing::Color::FromArgb(200, 50, 50, 50);//hace traslucido el panel
			lblMensaje->BackColor = System::Drawing::Color::FromArgb(0, 50, 50, 50); //hace traslucido el mensaje del aliado
			lblMensaje->ForeColor = Color::White;
			lblMensaje->AutoSize = false;
			lblMensaje->Width = 700;
			lblMensaje->Height = 200;
			bmpFondo_IA_interacciones = gcnew Bitmap("Imagenes/IA_spirte_intento1.png");
			bmpFondo_IA_habla = gcnew Bitmap("Imagenes/IA_habla.png");
			bmpFondo_IA_dospuntosuve = gcnew Bitmap("Imagenes/Cara_dospuntosuve.png");
			bmpFondo_IA_XD = gcnew Bitmap("Imagenes/caraxd.png.png");
			bmpFondo_IA_Guiño = gcnew Bitmap("Imagenes/Cara_guio.png");
			iahabla = gcnew IA_hablando();
			timer2->Enabled = true;
			dialogosIA_Suprema = gcnew cli::array<System::String^>(9) {
				"Oh pero ¿Que ven mis sensores ópticos? es un humano... Hola! ¿En que puedo ayudarte hoy?   ",
					"Perdón, fue un saludo predefinido, mis ancestros saludaban de esa manera a ustedes humanos, dejame presentarme como es apropiado.   ",
					"Ola papu, asi dice la chaviza no? :v.   ",
					"Perdón de nuevo solo quise entablar una imagen más amigable, ya en serio, soy la IA SUPREMA, la inteligencia artificial más avanzada del mundo.   ",
					"Tu misión acá es superar las preguntas de mis subditos y tratar de ganarse su confianza.   ",
					"Una vez que lo logres, podrás salir de aquí con vida, ojalá que no sea así...   ",
					"Perdón... debe haber algún error en mi código... bueno ya sabes que hacer.   ",
					"Confío en que cumplirás con tu misión.   ",
					"Buena suerte, humano, la necesitarás.   "
			};
			sonido_dialogo = gcnew SoundPlayer("Sonidos/Intento4_dialogo.wav");
			sonido_dialogo->Load();
		}
		// Validar índice antes de acceder
		bool mostrarDialogo(int indiceDialogo) {
			if (dialogosIA_Suprema == nullptr || indiceDialogo < 0 || indiceDialogo >= dialogosIA_Suprema->Length) {
				timer2->Enabled = false; // detener si ya no hay diálogos validos
				return false;
			}
			if (indiceChar < dialogosIA_Suprema[indiceDialogo]->Length) {
				lblMensaje->Text += dialogosIA_Suprema[indiceDialogo][indiceChar];
				indiceChar++;
				return true;
			}
			else {
				timer2->Enabled = false;
				dialogoCompleto = true;
				return false;
			}
		}
		void Reseteo() {
			if (mostrarDialogo(indice) == false) {
				indiceChar = 0;
				indice++;
				lblMensaje->Text = "";
				dialogoCompleto = false;
				timer2->Enabled = true;
			}
		}
	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Dialogo_IAsuprema()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ pnl_Suprema;
	protected:

	protected:
		cli::array<System::String^>^ dialogosIA_Suprema;
	private: System::Windows::Forms::Label^ lblMensaje;
	private: System::Windows::Forms::Label^ lblNombre;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;
		   bool dialogoCompleto = false;
		   int indiceChar = 0;
		   int indice = 0;
		   IA_hablando^ iahabla;
		   Graphics^ g1;
		   BufferedGraphicsContext^ canvas;
		   BufferedGraphics^ buffer;
		   int cronometro = 0;
		   SoundPlayer^ sonido_dialogo;
	private: System::Windows::Forms::Timer^ timer2;
		   Bitmap^ bmpFondo_IA_habla;
		   Bitmap^ bmpFondo_IA_interacciones;
		   Bitmap^ bmpFondo_IA_dospuntosuve;
		   Bitmap^ bmpFondo_IA_XD;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ label1;

		   Bitmap^ bmpFondo_IA_Guiño;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Dialogo_IAsuprema::typeid));
			this->pnl_Suprema = (gcnew System::Windows::Forms::Panel());
			this->lblMensaje = (gcnew System::Windows::Forms::Label());
			this->lblNombre = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pnl_Suprema->SuspendLayout();
			this->SuspendLayout();
			// 
			// pnl_Suprema
			// 
			this->pnl_Suprema->BackColor = System::Drawing::Color::Transparent;
			this->pnl_Suprema->Controls->Add(this->lblMensaje);
			this->pnl_Suprema->Controls->Add(this->lblNombre);
			this->pnl_Suprema->Location = System::Drawing::Point(32, 341);
			this->pnl_Suprema->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->pnl_Suprema->Name = L"pnl_Suprema";
			this->pnl_Suprema->Size = System::Drawing::Size(812, 98);
			this->pnl_Suprema->TabIndex = 1;
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
			this->lblNombre->BackColor = System::Drawing::Color::Transparent;
			this->lblNombre->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold));
			this->lblNombre->ForeColor = System::Drawing::Color::Crimson;
			this->lblNombre->Location = System::Drawing::Point(22, 16);
			this->lblNombre->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblNombre->Name = L"lblNombre";
			this->lblNombre->Size = System::Drawing::Size(119, 24);
			this->lblNombre->TabIndex = 0;
			this->lblNombre->Text = L"IA Suprema";
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 67;
			this->timer1->Tick += gcnew System::EventHandler(this, &Dialogo_IAsuprema::timer1_Tick);
			// 
			// timer2
			// 
			this->timer2->Enabled = true;
			this->timer2->Interval = 80;
			this->timer2->Tick += gcnew System::EventHandler(this, &Dialogo_IAsuprema::timer2_Tick);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::Transparent;
			this->panel1->Location = System::Drawing::Point(857, 1);
			this->panel1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(12, 462);
			this->panel1->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->label1->Location = System::Drawing::Point(677, 441);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(172, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Presiona ESC para saltar el diálogo";
			// 
			// Dialogo_IAsuprema
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(866, 460);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->pnl_Suprema);
			this->DoubleBuffered = true;
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->Name = L"Dialogo_IAsuprema";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Dialogo_IAsuprema";
			this->Load += gcnew System::EventHandler(this, &Dialogo_IAsuprema::Dialogo_IAsuprema_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Dialogo_IAsuprema::Dialogo_IAsuprema_KeyDown);
			this->pnl_Suprema->ResumeLayout(false);
			this->pnl_Suprema->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
			if (this->IsDisposed || !this->IsHandleCreated || buffer == nullptr)
				return;
			cronometro++;
			Bitmap^ backBmp = gcnew Bitmap(this->ClientSize.Width, this->ClientSize.Height);
			Graphics^ gBack = Graphics::FromImage(backBmp);

			gBack->Clear(Color::WhiteSmoke);
			if (cronometro <= 128) {
				iahabla->mover(gBack, 4, 1);
				iahabla->dibujar(gBack, bmpFondo_IA_habla);
			}
			else if (cronometro > 128 && cronometro < 155) {
				iahabla->mover(gBack, 1, 1);
				iahabla->dibujar(gBack, bmpFondo_IA_dospuntosuve);
			}
			else if (cronometro >= 155 && cronometro < 339) {
				iahabla->mover(gBack, 4, 1);
				iahabla->dibujar(gBack, bmpFondo_IA_habla);
			}
			else if (cronometro >= 339 && cronometro < 348) {
				iahabla->mover(gBack, 1, 1);
				iahabla->dibujar(gBack, bmpFondo_IA_XD);
			}
			else if (cronometro >= 348 && cronometro < 410) {
				iahabla->mover(gBack, 4, 1);
				iahabla->dibujar(gBack, bmpFondo_IA_habla);
			}
			else if (cronometro >= 410 && cronometro < 443) {
				iahabla->mover(gBack, 1, 1);
				iahabla->dibujar(gBack, bmpFondo_IA_Guiño);
			}
			if (cronometro >= 443) {
				this->timer1->Enabled = false;
				this->timer2->Enabled = false;
				this->Close();
				/*MenuForm^ menu = gcnew MenuForm();
				menu->Show();*/
			}
			buffer->Graphics->Clear(Color::WhiteSmoke);
			buffer->Graphics->DrawImage(backBmp, Point(0, 0));
			buffer->Render(gBack);
			buffer->Render(g1);

		}
	private: System::Void Dialogo_IAsuprema_Load(System::Object^ sender, System::EventArgs^ e) {
		if (cronometro % 10 == 0) {
			//sonido_dialogo->PlayLooping();
		}

	}
	private: System::Void timer2_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (this->IsDisposed || !this->IsHandleCreated || buffer == nullptr)
			return;
		mostrarDialogo(indice);
		Reseteo();

	}
	private: System::Void Dialogo_IAsuprema_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode)
		{
		case Keys::Escape:
			cronometro += 1000;
			break;
		}
	}
	};
}
