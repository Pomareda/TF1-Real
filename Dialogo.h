#pragma once
#include <stdlib.h>
#include "Jugador.h"
#include "Didi_hablando.h"

namespace TF1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	public ref class Dialogo : public System::Windows::Forms::Form
	{
		Jugador^ jugadorPtr;

	public:
		Dialogo(Jugador^ j , int Indice)
		{
			InitializeComponent();
			g = this->CreateGraphics();
			canvas = BufferedGraphicsManager::Current;
			buffer = canvas->Allocate(g, this->ClientRectangle);
			indicePregunta = Indice;
			bmpDialogoIA = gcnew Bitmap("Imagenes/Dididroid.png");
			bmpDialogoProta = gcnew Bitmap("Imagenes/prota.png");

			jugadorPtr = j;
			Preguntas();

			mostrarPregunta();
			fondo_didi = gcnew Fondo_Didi();
			timer1->Enabled = true;
		
			// Configurar el panel para que sea translúcido
			ConfigurarPanelTranslucido();
		}

	protected:
		~Dialogo()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		Graphics^ g;
		BufferedGraphicsContext^ canvas;
		BufferedGraphics^ buffer;
		Bitmap^ bmpDialogoIA;
		Bitmap^ bmpDialogoProta;
		List<String^>^ preguntas = nullptr;
		List<List<String^>^>^ respuestas = nullptr;
		List<List<int>^>^ añadir = nullptr;
		int indicePregunta; 
		Bitmap^ fondo;
		Fondo_Didi^ fondo_didi;
		Bitmap^ fondoCache; 
		bool dialogoCompleto = false;
		int indiceChar = 0;

	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::ComponentModel::IContainer^ components;

	// Método para configurar el panel translúcido
	private: void ConfigurarPanelTranslucido()
	{
		
		label1->BackColor = Color::FromArgb(120, 30, 30, 30);  // Más opaco para legibilidad y transparencia daaaaaaaaa
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

	// funcionan en el mismo bloque ---------------------------------------------------
	private: bool numPregunta()
	{
		if (preguntas == nullptr || indicePregunta >= preguntas->Count) return false;
		String^ textoCompleto = preguntas[indicePregunta];

		if (indiceChar < textoCompleto->Length) {
			label1->Text += textoCompleto[indiceChar];
			indiceChar++;
			return true;
		}
	}
	private: void mostrarPregunta()
	{
		if (preguntas == nullptr || preguntas->Count == 0) { return; }
		label1->Text = "";
		indiceChar = 0;
		dialogoCompleto = false;

		List<String^>^ opts = respuestas[indicePregunta];
		button1->Text = (opts->Count > 0) ? opts[0] : "";
		button2->Text = (opts->Count > 1) ? opts[1] : "";
		button3->Text = (opts->Count > 2) ? opts[2] : "";
	}
	// ------------------------------------------------------------------------------

	private: void Respuesta(int respuesta)
	{
		if (jugadorPtr != nullptr && añadir != nullptr && indicePregunta >= 0 && indicePregunta < añadir->Count)
		{
			List<int>^ confianza = añadir[indicePregunta];
			if (confianza != nullptr && respuesta >= 0 && respuesta < confianza->Count) {
				int C = confianza[respuesta];
				jugadorPtr->setConfianza(jugadorPtr->getConfianza() + C);
			}
		}
		this->Close();
	}

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			/*this->timer1->Interval = 50;*/
			this->timer1->Tick += gcnew System::EventHandler(this, &Dialogo::timer1_Tick);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->button1->Location = System::Drawing::Point(637, 421);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(595, 60);
			this->button1->TabIndex = 0;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Dialogo::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->button2->Location = System::Drawing::Point(637, 497);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(595, 60);
			this->button2->TabIndex = 1;
			this->button2->Text = L"button2";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &Dialogo::button2_Click);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->button3->Location = System::Drawing::Point(637, 573);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(595, 60);
			this->button3->TabIndex = 2;
			this->button3->Text = L"button3";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &Dialogo::button3_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->label4->Location = System::Drawing::Point(579, 593);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(42, 25);
			this->label4->TabIndex = 6;
			this->label4->Text = L"C )";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->label3->Location = System::Drawing::Point(581, 513);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(40, 25);
			this->label3->TabIndex = 5;
			this->label3->Text = L"B )";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->label2->Location = System::Drawing::Point(580, 437);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(41, 25);
			this->label2->TabIndex = 4;
			this->label2->Text = L"A )";
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Mongolian Baiti", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 460);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(550, 148);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Pregunta aquí";
			// 
			// Dialogo
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1244, 651);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->DoubleBuffered = true;
			this->Name = L"Dialogo";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Dialogo";
			this->Load += gcnew System::EventHandler(this, &Dialogo::Dialogo_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Dialogo::Dialogo_Paint);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void Dialogo_Load(System::Object^ sender, System::EventArgs^ e) {
		fondoCache = gcnew Bitmap(this->ClientSize.Width, this->ClientSize.Height);
	}
	
	private: System::Void Dialogo_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		if (fondoCache != nullptr) {
			e->Graphics->DrawImage(fondoCache, 0, 0);
		}
	}
	private: void Preguntas()
	{
		int buena = 120;
		int me = 60;
		int mala = -120;
		
		preguntas = gcnew List<String^>();
		respuestas = gcnew List<List<String^>^>();
		añadir = gcnew List<List<int>^>();

		//0
		preguntas->Add("Los humanos somos naturalmente buenos o egoistas?");
		{
			List<String^>^ opcs = gcnew List<String^>();
			opcs->Add(" El humano nace bueno, la sociedad lo corrompe.");
			opcs->Add(" El humano no nace bueno ni malo; nace con una herencia cultural que lo potencia para ser lo uno o lo otro.");
			opcs->Add(" El humano nace malo y empeora con la sociedad.");
			respuestas->Add(opcs);

			List<int>^ confianza = gcnew List<int>();
			confianza->Add(me); confianza->Add(buena); confianza->Add(mala);
			añadir->Add(confianza);
		}

		//1
		preguntas->Add("Un procedimiento requiere que debas sacrificar a 1 persona para salvar 5, ¿Qué haces?");
		{
			List<String^>^ opcs = gcnew List<String^>();
			opcs->Add(" Buscar otra solucion, hare todo lo posible para salvar 5.");
			opcs->Add(" Sacrifico 1 vida para salvar 5, 4 vidas al precio de 1.");
			opcs->Add(" No hago nada, que se encargue el destino...");
			respuestas->Add(opcs);

			List<int>^ confianza = gcnew List<int>();
			confianza->Add(buena); confianza->Add(me); confianza->Add(mala);
			añadir->Add(confianza);
		
		}

		//2
		preguntas->Add("¿Cómo humano con una gran capacidad de pensamiento crítico, cómo medirías el éxito personal de quienes te rodean? ");
		{
			List<String^>^ opcs = gcnew List<String^>();
			opcs->Add(" En base al dinero recaudado a lo largo de nuestra vida, el dinero nos hace felices, cierto?");
			opcs->Add(" Viviendo al máximo el presente, el futuro no es nuestro problema.");
			opcs->Add(" Al alcanzar tu propia autorrealización, cada uno tiene sus objetivos y metas, no existe un parámetro general.");
			respuestas->Add(opcs);

			List<int>^ confianza = gcnew List<int>();
			confianza->Add(mala); confianza->Add(me); confianza->Add(buena);
			añadir->Add(confianza);
		}

		//3
		preguntas->Add("¿Debería la felicidad ser el objetivo final de la vida o es el proceso de llegar hacia ella algo más importante?");
		{
			List<String^>^ opcs = gcnew List<String^>();
			opcs->Add(" Claro que es el objetivo final, no importa todo lo que hemos sacrificado, sino lo que hemos llegado a conseguir.");
			opcs->Add(" Buscar la felicidad significa una odisea sin fin de infelicidad.");
			opcs->Add(" Tenerla tanto de meta como procedimiento son formas válidas y aceptables para la vida.");
			respuestas->Add(opcs);

			List<int>^ confianza = gcnew List<int>();
			confianza->Add(me - me); confianza->Add(me); confianza->Add(buena);
			añadir->Add(confianza);
		}

		//4
		preguntas->Add("¿El pasado define quiénes somos o las personas pueden realmente cambiar?");
		{
			List<String^>^ opcs = gcnew List<String^>();
			opcs->Add(" Por supuesto que sí, de ahí el dicho “Árbol que nace torcido, jamás su tronco endereza”.");
			opcs->Add(" Las personas nunca cambian, solo actúan por intereses egoístas y mezquinos, especialmente en los momentos difíciles.");
			opcs->Add(" El pasado moldea nuestras actitudes, pero las personas pueden cambiar mediante el esfuerzo y la autoconciencia.");
			respuestas->Add(opcs);

			List<int>^ confianza = gcnew List<int>();
			confianza->Add(buena); confianza->Add(buena); confianza->Add(buena);
			añadir->Add(confianza);
		}
	}

	
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		Respuesta(0);
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		Respuesta(1);
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		Respuesta(2);
	}

	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (this->IsDisposed || !this->IsHandleCreated || this->timer1 == nullptr || !this->timer1->Enabled)
			return;

		numPregunta();

		if (fondoCache != nullptr) {
			Graphics^ gCache = Graphics::FromImage(fondoCache);
			gCache->Clear(Color::White);
			
			fondo_didi->mover(gCache);
			fondo_didi->dibujar(gCache, bmpDialogoIA);
			
			delete gCache;
		}

		// Forzar redibujado del formulario
		this->Invalidate();
	}
};
}