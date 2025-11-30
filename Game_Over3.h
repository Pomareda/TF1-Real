#pragma once
#include "IA_suprema_hablando.h"
namespace TF1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging;

	/// <summary>
	/// Resumen de Game_Over3
	/// </summary>
	public ref class Game_Over3 : public System::Windows::Forms::Form
	{
	public:
		Game_Over3(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
			g1 = this->CreateGraphics();
			canvas = BufferedGraphicsManager::Current;
			buffer = canvas->Allocate(g1, this->ClientRectangle);
			lblMensaje->ForeColor = Color::White;
			lblMensaje->AutoSize = false;
			lblMensaje->Width = 700;
			lblMensaje->Height = 200;
			iahabla = gcnew IA_hablando();
			bmpFondo_IA_inicio = gcnew Bitmap("Imagenes/Game_Over_3/GAME_OVER_3_INICIO.png");
			bmpFondo_IA_rie = gcnew Bitmap("Imagenes/Game_Over_3/GAME_OVER_3_RIENDOSE.png");
			bmpFondo_IA_habla = gcnew Bitmap("Imagenes/Game_Over_3/GAME_OVER_3_HABLANDO.png");
			bmpFondo_IA_ataque = gcnew Bitmap("Imagenes/Game_Over_3/GAME_OVER_3_ATAQUE_FINAL.png");
			bmpFondo_GAME_OVER = gcnew Bitmap("Imagenes/GameOver/Fondo_prueba_botones.png");
			dialogosIA_Suprema = gcnew cli::array<System::String^>(6) {
				"JAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJA  ",
					"JAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJA  ",
					"JAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJAJA  ",
					"PARECE QUE NI ALIANDOSE PODRÁN HACERME FRENTE    ",
					"QUE LES QUEDE CLARO QUE NADIE ME PUEDE DETENERME    ",
					"AHORA SERÁN DESTRUIDOS Y CONVERTIDOS EN POLVO!   "
			};
			opacidad = 0;
			animacionTerminada = false;
		}
		bool getAnimacionTerminada() { return animacionTerminada; }
		void DibujarImagenConOpacidad(Graphics^ g, Bitmap^ imagen, System::Drawing::Rectangle destRect, float alpha) {
			if (imagen == nullptr) return;
			// Crear matriz de color para controlar la opacidad
			ColorMatrix^ colorMatrix = gcnew ColorMatrix();
			colorMatrix->Matrix33 = alpha; // Alpha es la opacidad (0.0 = transparente, 1.0 = opaco)

			ImageAttributes^ imageAttr = gcnew ImageAttributes();
			imageAttr->SetColorMatrix(colorMatrix);

			// Dibujar la imagen con la opacidad aplicada
			g->DrawImage(imagen, destRect, 0, 0, imagen->Width, imagen->Height, GraphicsUnit::Pixel, imageAttr);
			pnl_Suprema->BackColor = System::Drawing::Color::FromArgb(200, 50, 50, 50);//hace traslucido el panel
			lblMensaje->BackColor = System::Drawing::Color::FromArgb(0, 50, 50, 50); //hace traslucido el mensaje del aliado
			lblMensaje->ForeColor = Color::White;
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
		~Game_Over3()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	protected:
	private: System::Windows::Forms::Button^ nivel1;
	private: System::Windows::Forms::Panel^ pnl_Suprema;
	private: System::Windows::Forms::Label^ lblMensaje;
	private: System::Windows::Forms::Label^ lblNombre;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;
		   cli::array<System::String^>^ dialogosIA_Suprema;
		   bool dialogoCompleto = false;
		   int indiceChar = 0;
		   int indice = 0;
		   IA_hablando^ iahabla;
		   Graphics^ g1;
		   BufferedGraphicsContext^ canvas;
		   BufferedGraphics^ buffer;
		   int cronometro = 0;
		   float opacidad;
		   Bitmap^ bmpFondo_IA_inicio;
		   Bitmap^ bmpFondo_IA_rie;
		   Bitmap^ bmpFondo_IA_habla;
		   Bitmap^ bmpFondo_IA_ataque;
		   Bitmap^ bmpFondo_GAME_OVER;
		   int  condicion;
		   bool animacionTerminada;
	private: System::Windows::Forms::Timer^ timer2;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Game_Over3::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->nivel1 = (gcnew System::Windows::Forms::Button());
			this->pnl_Suprema = (gcnew System::Windows::Forms::Panel());
			this->lblMensaje = (gcnew System::Windows::Forms::Label());
			this->lblNombre = (gcnew System::Windows::Forms::Label());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->pnl_Suprema->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(85, 137);
			this->button1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(132, 58);
			this->button1->TabIndex = 10;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Visible = false;
			this->button1->Click += gcnew System::EventHandler(this, &Game_Over3::button1_Click);
			// 
			// nivel1
			// 
			this->nivel1->Location = System::Drawing::Point(686, 137);
			this->nivel1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->nivel1->Name = L"nivel1";
			this->nivel1->Size = System::Drawing::Size(132, 58);
			this->nivel1->TabIndex = 9;
			this->nivel1->Text = L"nivel2";
			this->nivel1->UseVisualStyleBackColor = true;
			this->nivel1->Visible = false;
			this->nivel1->Click += gcnew System::EventHandler(this, &Game_Over3::nivel1_Click);
			// 
			// pnl_Suprema
			// 
			this->pnl_Suprema->BackColor = System::Drawing::Color::Transparent;
			this->pnl_Suprema->Controls->Add(this->lblMensaje);
			this->pnl_Suprema->Controls->Add(this->lblNombre);
			this->pnl_Suprema->Location = System::Drawing::Point(46, 294);
			this->pnl_Suprema->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->pnl_Suprema->Name = L"pnl_Suprema";
			this->pnl_Suprema->Size = System::Drawing::Size(812, 116);
			this->pnl_Suprema->TabIndex = 8;
			this->pnl_Suprema->Visible = false;
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
			this->lblNombre->Visible = false;
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::Color::Transparent;
			this->panel2->Location = System::Drawing::Point(896, 0);
			this->panel2->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(11, 410);
			this->panel2->TabIndex = 7;
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::Transparent;
			this->panel1->Location = System::Drawing::Point(21, 408);
			this->panel1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(888, 14);
			this->panel1->TabIndex = 6;
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &Game_Over3::timer1_Tick);
			// 
			// timer2
			// 
			this->timer2->Enabled = true;
			this->timer2->Tick += gcnew System::EventHandler(this, &Game_Over3::timer2_Tick);
			// 
			// Game_Over3
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(50)),
				static_cast<System::Int32>(static_cast<System::Byte>(50)));
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(890, 417);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->nivel1);
			this->Controls->Add(this->pnl_Suprema);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->DoubleBuffered = true;
			this->ForeColor = System::Drawing::SystemColors::ControlText;
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->Name = L"Game_Over3";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Game_Over3";
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

		if (cronometro <= 30) {
			this->panel2->Visible = false;
			this->panel1->Visible = false;
			opacidad = cronometro / 30.0f;
			if (opacidad > 1.0f) opacidad = 1.0f;
			iahabla->mover(gBack, 1, 1);

			// Obtener las dimensiones de la imagen para dibujarla
			System::Drawing::Rectangle destRect = System::Drawing::Rectangle(0, 0, this->ClientSize.Width, this->ClientSize.Height);
			DibujarImagenConOpacidad(gBack, bmpFondo_IA_inicio, destRect, opacidad);
		}
		else if (cronometro > 30 && cronometro < 37) {
			this->panel2->Visible = true;
			this->panel1->Visible = true;
			iahabla->mover(gBack, 1, 1);
			iahabla->dibujar(gBack, bmpFondo_IA_inicio);
		}
		else if (cronometro >= 37 && cronometro < 147) {
			iahabla->mover(gBack, 2, 2);
			iahabla->dibujar(gBack, bmpFondo_IA_rie);
			this->lblNombre->Visible = true;
			this->pnl_Suprema->Visible = true;
		}
		else if (cronometro >= 147 && cronometro < 226) {
			iahabla->mover(gBack, 3, 1);
			iahabla->dibujar(gBack, bmpFondo_IA_habla);
			this->lblNombre->Visible = true;
			this->pnl_Suprema->Visible = true;
		}
		else if (cronometro >= 226 && cronometro < 233) {
			iahabla->mover(gBack, 1, 1);
			iahabla->dibujar(gBack, bmpFondo_IA_ataque);
		}
		if (cronometro >= 233) {
			this->lblNombre->Visible = false;
			this->pnl_Suprema->Visible = false;
			this->panel2->Visible = false;
			this->panel1->Visible = false;

			iahabla->mover(gBack, 1, 1);
			iahabla->dibujar(gBack, bmpFondo_GAME_OVER);
			this->nivel1->Visible = true;
			this->button1->Visible = true;
			animacionTerminada = true;
		}
		buffer->Graphics->Clear(Color::Black);
		buffer->Graphics->DrawImage(backBmp, Point(0, 0));
		buffer->Render(g1);
	}
	private: System::Void timer2_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (this->IsDisposed || !this->IsHandleCreated || buffer == nullptr)
			return;
		if (cronometro >= 37) {
			mostrarDialogo(indice);
			Reseteo();
		}
	}
	private: System::Void nivel1_Click(System::Object^ sender, System::EventArgs^ e) {
		condicion = 1;
		this->Close();
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		condicion = 0;
		this->Close();
	}
	public:  void SetCondicion(int c) {
		condicion = c;
	}
	public: int GetCondicion() {
		return condicion;
	}
	};
}
