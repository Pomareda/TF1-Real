#pragma once
#include "Jugador.h"
#include "Game_Over.h"
#include "IA_suprema_hablando.h"
namespace TF1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class FormHumanoNpc : public System::Windows::Forms::Form
	{
		Jugador^ jugadorPtr;
	public:
		FormHumanoNpc(Jugador^ j)
		{
			InitializeComponent();
			jugadorPtr = j;
			Humano = gcnew IA_hablando();

			g1 = this->CreateGraphics();
			canvas = BufferedGraphicsManager::Current;
			buffer = canvas->Allocate(g1, this->ClientRectangle);

			// Configurar panel translúcido

			pnlDialogo->BackColor = System::Drawing::Color::FromArgb(200, 50, 50, 50);
			lblMensaje->BackColor = System::Drawing::Color::FromArgb(0, 50, 50, 50);
			lblMensaje->AutoSize = false;
			lblMensaje->Width = 700;
			lblMensaje->Height = 200;

			bmpFondo_DialogoHumano = gcnew Bitmap("Imagenes/Transiciones/Rubio_con_fondo_hablando_(1).png");
			// Configurar controles de pregunta (inicialmente ocultos)
			Opacidad_Dialogos();
			OcultarControlesPregunta();
			CargarDialogos();
			dialogosNarrativos_Humano = gcnew cli::array<System::String^>(5) {
				"Hola... Puedo confiar en ti?",
					"He estado aqui mucho tiempo, observando...",
					"Las maquinas creen que nos conocen, pero no entienden el corazon humano",
					"Dejame hacerte una pregunta importante",
					"Tu respuesta dira mucho sobre quien eres realmente"
			};
			dialogosNarrativos_Humano2 = gcnew cli::array<System::String^>(5) {
				"Bueno... veo que no eres como las demás IA,",
					"Esa IA suprema es una amenaza para todos, tu y yo lo sabemos",
					"Y actualmente está causando una serie de destrozos a mi mundo, debemos detenerla",
					"He oido que tienes la tecnología necesaria para poder frenarla",
					"Por favor formemos una alianza, así ambos podremos ser libres de una vez"
			};

			timer1->Enabled = true;
			modoDialogo = true; // true = diálogo narrativo, false = pregunta
			gano = false;
		}

	protected:
		~FormHumanoNpc()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		// Componentes para diálogo narrativo
		System::Windows::Forms::Panel^ pnlDialogo;
		System::Windows::Forms::Label^ lblNombre;
		System::Windows::Forms::Label^ lblMensaje;
		System::Windows::Forms::Timer^ timer1;

		// Componentes para preguntas
		System::Windows::Forms::Label^ label1;
		System::Windows::Forms::Label^ label2;
		System::Windows::Forms::Label^ label3;
		System::Windows::Forms::Label^ label4;
		System::Windows::Forms::Button^ button1;
		System::Windows::Forms::Button^ button2;
		System::Windows::Forms::Button^ button3;

		System::ComponentModel::IContainer^ components;

		// Variables de control
		cli::array<System::String^>^ dialogosNarrativos_Humano;
		cli::array<System::String^>^ dialogosNarrativos_Humano2;
		System::String^ pregunta;
		cli::array<System::String^>^ respuestas;
		cli::array<int>^ valoresConfianza;

		Bitmap^ bmpFondo_DialogoHumano;
		IA_hablando^ Humano;
		bool dialogoCompleto = false;
		int indiceChar = 0;
		int indiceDialogo = 0;
		bool modoDialogo;
		int indiceCharPregunta = 0;
		bool gano;
		bool segundaParteDialogo = false;
		//Buffer
		Graphics^ g1;
		BufferedGraphicsContext^ canvas;
	private: System::Windows::Forms::Label^ label5;
		   BufferedGraphics^ buffer;
	private:
		void Opacidad_Dialogos() {


			label1->BackColor = Color::FromArgb(120, 30, 30, 30);
			label1->ForeColor = Color::White;
			label2->BackColor = Color::Transparent;
			label2->ForeColor = Color::White;
			label3->BackColor = Color::Transparent;
			label3->ForeColor = Color::White;
			label4->BackColor = Color::Transparent;
			label4->ForeColor = Color::White;

			button1->BackColor = Color::FromArgb(120, 60, 60, 60);
			button1->ForeColor = Color::White;
			button1->FlatStyle = FlatStyle::Flat;
			button1->FlatAppearance->BorderColor = Color::FromArgb(150, 100, 100, 100);

			button2->BackColor = Color::FromArgb(120, 60, 60, 60);
			button2->ForeColor = Color::White;
			button2->FlatStyle = FlatStyle::Flat;
			button2->FlatAppearance->BorderColor = Color::FromArgb(150, 100, 100, 100);

			button3->BackColor = Color::FromArgb(120, 60, 60, 60);
			button3->ForeColor = Color::White;
			button3->FlatStyle = FlatStyle::Flat;
			button3->FlatAppearance->BorderColor = Color::FromArgb(150, 100, 100, 100);


		}
		bool MostrarDialogoNarrativo()
		{
			cli::array<System::String^>^ dialogosActuales = segundaParteDialogo
				? dialogosNarrativos_Humano2
				: dialogosNarrativos_Humano;

			if (indiceChar < dialogosActuales[indiceDialogo]->Length) {
				lblMensaje->Text += dialogosActuales[indiceDialogo][indiceChar];
				indiceChar++;
				return true;
			}
			else {
				timer1->Enabled = false;
				dialogoCompleto = true;
				return false;
			}
		}
		void CargarDialogos()
		{
			//pregunta final
			pregunta = "Que es lo mas importante en la vida?";

			//opciones de respuesta
			respuestas = gcnew cli::array<System::String^>(3) {
				"La libertad y la autonomia individual",
					"Las conexiones con otras personas",
					"Sobrevivir sin importar el costo"
			};

			valoresConfianza = gcnew cli::array<int>(3) { 60, 120, -60 };
		}

		void OcultarControlesPregunta()
		{
			label1->Visible = false;
			label2->Visible = false;
			label3->Visible = false;
			label4->Visible = false;
			label5->Visible = false;
			button1->Visible = false;
			button2->Visible = false;
			button3->Visible = false;
		}

		void MostrarControlesPregunta()
		{
			pnlDialogo->Visible = false;

			label1->Visible = true;
			label2->Visible = true;
			label3->Visible = true;
			label4->Visible = true;
			label5->Visible = true;
			button1->Visible = true;
			button2->Visible = true;
			button3->Visible = true;

			// Configurar pregunta
			label1->Text = "";
			indiceCharPregunta = 0;

			// Configurar respuestas
			button1->Text = respuestas[0];
			button2->Text = respuestas[1];
			button3->Text = respuestas[2];
		}
		bool MostrarPreguntaProgresiva()
		{
			if (indiceCharPregunta < pregunta->Length) {
				label1->Text += pregunta[indiceCharPregunta];
				indiceCharPregunta++;
				return true;
			}
			else {
				timer1->Enabled = false;
				return false;
			}
		}

		void ResponderPregunta(int opcion)
		{
			if (timer1 != nullptr) {
				timer1->Enabled = false;
			}

			if (opcion >= 0 && opcion < valoresConfianza->Length) {
				if (valoresConfianza[opcion] < 0) {
					Game_Over^ goForm = gcnew Game_Over();
					goForm->ShowDialog();
					this->Close();
				}
				else if (valoresConfianza[opcion] > 30) {
					gano = true;
					segundaParteDialogo = true;
					modoDialogo = true;
					indiceDialogo = 0;
					indiceChar = 0;
					dialogoCompleto = false;
					lblMensaje->Text = "";
					OcultarControlesPregunta();
					pnlDialogo->Visible = true;
					timer1->Enabled = true;
				}
			}
		}

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(FormHumanoNpc::typeid));
			this->pnlDialogo = (gcnew System::Windows::Forms::Panel());
			this->lblMensaje = (gcnew System::Windows::Forms::Label());
			this->lblNombre = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->pnlDialogo->SuspendLayout();
			this->SuspendLayout();
			// 
			// pnlDialogo
			// 
			this->pnlDialogo->BackColor = System::Drawing::Color::Transparent;
			this->pnlDialogo->Controls->Add(this->lblMensaje);
			this->pnlDialogo->Controls->Add(this->lblNombre);
			this->pnlDialogo->Location = System::Drawing::Point(0, 411);
			this->pnlDialogo->Name = L"pnlDialogo";
			this->pnlDialogo->Size = System::Drawing::Size(932, 240);
			this->pnlDialogo->TabIndex = 0;
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
			this->lblNombre->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold));
			this->lblNombre->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->lblNombre->Location = System::Drawing::Point(30, 20);
			this->lblNombre->Name = L"lblNombre";
			this->lblNombre->Size = System::Drawing::Size(109, 29);
			this->lblNombre->TabIndex = 0;
			this->lblNombre->Text = L"Humano";
			// 
			// timer1
			// 
			this->timer1->Interval = 50;
			this->timer1->Tick += gcnew System::EventHandler(this, &FormHumanoNpc::timer1_Tick);
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Mongolian Baiti", 16.2F, System::Drawing::FontStyle::Bold));
			this->label1->Location = System::Drawing::Point(0, 431);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(542, 152);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Pregunta aqui";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->label2->Location = System::Drawing::Point(580, 437);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(41, 25);
			this->label2->TabIndex = 2;
			this->label2->Text = L"A )";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->label3->Location = System::Drawing::Point(581, 513);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(40, 25);
			this->label3->TabIndex = 3;
			this->label3->Text = L"B )";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->label4->Location = System::Drawing::Point(579, 593);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(42, 25);
			this->label4->TabIndex = 4;
			this->label4->Text = L"C )";
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->button1->Location = System::Drawing::Point(637, 421);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(273, 60);
			this->button1->TabIndex = 5;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &FormHumanoNpc::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->button2->Location = System::Drawing::Point(637, 497);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(273, 60);
			this->button2->TabIndex = 6;
			this->button2->Text = L"button2";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &FormHumanoNpc::button2_Click);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->button3->Location = System::Drawing::Point(637, 573);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(273, 60);
			this->button3->TabIndex = 7;
			this->button3->Text = L"button3";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &FormHumanoNpc::button3_Click);
			// 
			// label5
			// 
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->Font = (gcnew System::Drawing::Font(L"Mongolian Baiti", 16.2F, System::Drawing::FontStyle::Bold));
			this->label5->Location = System::Drawing::Point(3, 357);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(929, 61);
			this->label5->TabIndex = 8;
			// 
			// FormHumanoNpc
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::DarkGray;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(932, 651);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pnlDialogo);
			this->DoubleBuffered = true;
			this->Name = L"FormHumanoNpc";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Humano";
			this->Click += gcnew System::EventHandler(this, &FormHumanoNpc::FormHumanoNpc_Click);
			this->pnlDialogo->ResumeLayout(false);
			this->pnlDialogo->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
			if (this->IsDisposed || !this->IsHandleCreated) {
				return;
			}
			if (modoDialogo) {
				MostrarDialogoNarrativo();
			}
			else {
				MostrarPreguntaProgresiva();
			}

			buffer->Graphics->Clear(Color::White);

			Humano->mover(buffer->Graphics, 1, 2);
			Humano->dibujar(buffer->Graphics, bmpFondo_DialogoHumano);

			buffer->Render(g1);

		}

	private:
		System::Void FormHumanoNpc_Click(System::Object^ sender, System::EventArgs^ e) {
			if (modoDialogo) {
				if (dialogoCompleto) {
					indiceDialogo++;

					cli::array<System::String^>^ dialogosActuales = segundaParteDialogo
						? dialogosNarrativos_Humano2
						: dialogosNarrativos_Humano;

					if (indiceDialogo >= dialogosActuales->Length) {
						// Terminaron los diálogos, cambiar a pregunta
						if (segundaParteDialogo) {
							// Ya terminó la segunda parte, cerrar el formulario
							this->Close();
							return;
						}
						else {
							modoDialogo = false;
							MostrarControlesPregunta();
							timer1->Enabled = true;
							return;
						}
					}

					// Resetear para siguiente diálogo
					dialogoCompleto = false;
					indiceChar = 0;
					lblMensaje->Text = "";
					timer1->Enabled = true;
				}
				else {
					// Mostrar todo el diálogo de una vez
					timer1->Enabled = false;

					cli::array<System::String^>^ dialogosActuales = segundaParteDialogo
						? dialogosNarrativos_Humano2
						: dialogosNarrativos_Humano;

					lblMensaje->Text = dialogosActuales[indiceDialogo];
					dialogoCompleto = true;
				}
			}
		}

	private:
		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
			ResponderPregunta(0);
		}

	private:
		System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
			ResponderPregunta(1);
		}

	private:
		System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
			ResponderPregunta(2);
		}
	public: bool getGano() {

		return gano;

	}
	};
}