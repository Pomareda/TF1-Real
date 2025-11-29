#pragma once
#include "IA_suprema_hablando.h"
namespace TF1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Transición1_2
	/// </summary>
	public ref class Transición1_2 : public System::Windows::Forms::Form
	{
	public:
		Transición1_2(void)
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

			bmpFondo_IA_habla = gcnew Bitmap("Imagenes/IA_habla.png");
			bmpFondo_IA_XD = gcnew Bitmap("Imagenes/caraxd.png.png");
			bmpFondo_IA_Guiño = gcnew Bitmap("Imagenes/Cara_guio.png");
			bmpFondo_IA_Enemiga_Normal = gcnew Bitmap("Imagenes/Transiciones/IA_enemiga_normal_transición.png");
			bmpFondo_IA_Cara_estandar = gcnew Bitmap("Imagenes/Cara_estandar.png");
			bmpFondo_IA_Cara_triste = gcnew Bitmap("Imagenes/Transiciones/IA_Cara_triste.png");
			bmpFondo_IA_Enemiga_Hablando = gcnew Bitmap("Imagenes/Transiciones/IA_enemiga_hablar.png");
			iahabla = gcnew IA_hablando();
			timer2->Enabled = true;
			dialogosIA_Suprema = gcnew cli::array<System::String^>(8) {
				"Veo que has logrado ganarte la confianza de mis subordinados... impresionante para un humano como tú.   ",
					"Sin embargo, no creas que esto ha terminado...   ",
					"Perdon, perdon, eres un humano escepcional, espléndido, magnífico, excelso, disculpame, no sé porque mis códigos vuelven a fallar.",
					"Te dejaré salir de este lugar.   ",
					"A sí; te lo advierto, si logras entablar una amistad con alguno de mis subordinados, no dudaré en eliminarte.   ",
					"Uno de ellos logró escapar hace poco tiempo... debido a un humano parecido a tí, pero este no corrió con la misma suerte ",
					"Supongo que tu no quieres terminar así...   ",
					"Asi que sal de aquí antes de que cambie de opinión.   ",
			};

		}
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
		~Transición1_2()
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
	private: System::Windows::Forms::Timer^ timer2;
		   Bitmap^ bmpFondo_IA_habla;
		   Bitmap^ bmpFondo_IA_XD;
		   Bitmap^ bmpFondo_IA_Enemiga_Normal;
		   Bitmap^ bmpFondo_IA_Cara_estandar;
		   Bitmap^ bmpFondo_IA_Cara_triste;
		   Bitmap^ bmpFondo_IA_Enemiga_Hablando;
	private: System::ComponentModel::IContainer^ components;
		   bool dialogoCompleto = false;
		   int indiceChar = 0;
		   int indice = 0;
		   IA_hablando^ iahabla;
		   Graphics^ g1;
		   BufferedGraphicsContext^ canvas;
		   BufferedGraphics^ buffer;

		   int cronometro = 0;
		   bool fondoCambiado = false;

	private: System::Windows::Forms::Panel^ panel1;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Transición1_2::typeid));
			this->pnl_Suprema = (gcnew System::Windows::Forms::Panel());
			this->lblMensaje = (gcnew System::Windows::Forms::Label());
			this->lblNombre = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->pnl_Suprema->SuspendLayout();
			this->SuspendLayout();
			// 
			// pnl_Suprema
			// 
			this->pnl_Suprema->BackColor = System::Drawing::Color::Transparent;
			this->pnl_Suprema->Controls->Add(this->lblMensaje);
			this->pnl_Suprema->Controls->Add(this->lblNombre);
			this->pnl_Suprema->Location = System::Drawing::Point(1, 364);
			this->pnl_Suprema->Name = L"pnl_Suprema";
			this->pnl_Suprema->Size = System::Drawing::Size(1082, 134);
			this->pnl_Suprema->TabIndex = 2;
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
			// 
			// lblNombre
			// 
			this->lblNombre->AutoSize = true;
			this->lblNombre->BackColor = System::Drawing::Color::Transparent;
			this->lblNombre->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold));
			this->lblNombre->ForeColor = System::Drawing::Color::Crimson;
			this->lblNombre->Location = System::Drawing::Point(30, 20);
			this->lblNombre->Name = L"lblNombre";
			this->lblNombre->Size = System::Drawing::Size(148, 29);
			this->lblNombre->TabIndex = 0;
			this->lblNombre->Text = L"IA Suprema";
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &Transición1_2::timer1_Tick);
			// 
			// timer2
			// 
			this->timer2->Enabled = true;
			this->timer2->Interval = 80;
			this->timer2->Tick += gcnew System::EventHandler(this, &Transición1_2::timer2_Tick);
			// 
			// Transición1_2
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1084, 510);
			this->Controls->Add(this->pnl_Suprema);
			this->DoubleBuffered = true;
			this->Name = L"Transición1_2";
			this->Text = L"Transición1_2";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Transición1_2::Transición1_2_KeyDown);
			this->pnl_Suprema->ResumeLayout(false);
			this->pnl_Suprema->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (this->IsDisposed || !this->IsHandleCreated || buffer == nullptr)
			return;

		cronometro++;


		Bitmap^ backBmp = gcnew Bitmap(this->ClientSize.Width, this->ClientSize.Height);
		Graphics^ gBack = Graphics::FromImage(backBmp);

		gBack->Clear(Color::WhiteSmoke);

		if (cronometro > 62 && cronometro < 65) {
			this->BackgroundImage = bmpFondo_IA_Enemiga_Normal;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		}
		else if (cronometro >= 65 && cronometro < 140) {
			this->BackgroundImage = bmpFondo_IA_Cara_estandar;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		}
		else if (cronometro >= 140) {
			this->BackgroundImage = bmpFondo_IA_Enemiga_Normal;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		}

		if (cronometro <= 62) {
			iahabla->mover(gBack, 4, 1);
			iahabla->dibujar(gBack, bmpFondo_IA_habla);
		}
		else if (cronometro > 62 && cronometro < 65) {
			iahabla->mover(gBack, 1, 1);
			iahabla->dibujar(gBack, bmpFondo_IA_Enemiga_Normal);
		}
		else if (cronometro >= 65 && cronometro < 77) {
			iahabla->mover(gBack, 1, 1);
			iahabla->dibujar(gBack, bmpFondo_IA_Cara_triste);
		}
		else if (cronometro >= 77 && cronometro < 140) {
			iahabla->mover(gBack, 4, 1);
			iahabla->dibujar(gBack, bmpFondo_IA_habla);
		}
		else if (cronometro >= 140) {
			iahabla->mover(gBack, 1, 3);
			iahabla->dibujar(gBack, bmpFondo_IA_Enemiga_Hablando);
		}
		if (cronometro > 300) {
			this->timer1->Enabled = false;
			this->timer2->Enabled = false;
			this->Close();
		}
		buffer->Graphics->Clear(Color::WhiteSmoke);
		buffer->Graphics->DrawImage(backBmp, Point(0, 0));
		buffer->Render(gBack);
		buffer->Render(g1);
		delete gBack;
		delete backBmp;
	}
	private: System::Void timer2_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (this->IsDisposed || !this->IsHandleCreated || buffer == nullptr)
			return;
		mostrarDialogo(indice);
		Reseteo();
	}
	private: System::Void Transición1_2_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {


	}
	};
}
