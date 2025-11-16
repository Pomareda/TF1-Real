#pragma once
#include <stdlib.h>
#include "Jugador.h"

namespace TF1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class Dialogo : public System::Windows::Forms::Form
	{
		Jugador^ jugadorPtr;

	public:
		Dialogo(Jugador^ j)
		{
			InitializeComponent();
			g = this->CreateGraphics();
			canvas = BufferedGraphicsManager::Current;
			buffer = canvas->Allocate(g, this->ClientRectangle);

			bmpDialogoIA = gcnew Bitmap("diddyDroid.png");
			bmpDialogoProta = gcnew Bitmap("prota.png");

			jugadorPtr = j;
			Preguntas();
			mostrarPregunta();

		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
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
		List<List<int>^>^ impactos = nullptr;
		int indicePregunta; 

		//falta ponerlo
		Bitmap^ fondo;

	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;

	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Método necesario para admitir el Diseñador. No se puede modificar
		   /// el contenido de este método con el editor de código.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			   this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->button3 = (gcnew System::Windows::Forms::Button());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->label4 = (gcnew System::Windows::Forms::Label());
			   this->groupBox1->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // timer1
			   // 
			   this->timer1->Tick += gcnew System::EventHandler(this, &Dialogo::timer1_Tick);
			   // 
			   // groupBox1
			   // 
			   this->groupBox1->BackColor = System::Drawing::Color::Transparent;
			   this->groupBox1->Controls->Add(this->label4);
			   this->groupBox1->Controls->Add(this->label3);
			   this->groupBox1->Controls->Add(this->label2);
			   this->groupBox1->Controls->Add(this->label1);
			   this->groupBox1->Controls->Add(this->button3);
			   this->groupBox1->Controls->Add(this->button2);
			   this->groupBox1->Controls->Add(this->button1);
			   this->groupBox1->Location = System::Drawing::Point(12, 374);
			   this->groupBox1->Name = L"groupBox1";
			   this->groupBox1->Size = System::Drawing::Size(909, 158);
			   this->groupBox1->TabIndex = 0;
			   this->groupBox1->TabStop = false;
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->label1->Location = System::Drawing::Point(16, 16);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(51, 20);
			   this->label1->TabIndex = 3;
			   this->label1->Text = L"label1";
			   // 
			   // button3
			   // 
			   this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->button3->Location = System::Drawing::Point(457, 108);
			   this->button3->Name = L"button3";
			   this->button3->Size = System::Drawing::Size(446, 40);
			   this->button3->TabIndex = 2;
			   this->button3->Text = L"button3";
			   this->button3->UseVisualStyleBackColor = true;
			   this->button3->Click += gcnew System::EventHandler(this, &Dialogo::button3_Click);
			   // 
			   // button2
			   // 
			   this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->button2->Location = System::Drawing::Point(457, 62);
			   this->button2->Name = L"button2";
			   this->button2->Size = System::Drawing::Size(446, 40);
			   this->button2->TabIndex = 1;
			   this->button2->Text = L"button2";
			   this->button2->UseVisualStyleBackColor = true;
			   this->button2->Click += gcnew System::EventHandler(this, &Dialogo::button2_Click);
			   // 
			   // button1
			   // 
			   this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->button1->Location = System::Drawing::Point(457, 16);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(446, 40);
			   this->button1->TabIndex = 0;
			   this->button1->Text = L"button1";
			   this->button1->UseVisualStyleBackColor = true;
			   this->button1->Click += gcnew System::EventHandler(this, &Dialogo::button1_Click);
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->label2->Location = System::Drawing::Point(422, 25);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(32, 20);
			   this->label2->TabIndex = 4;
			   this->label2->Text = L"A )";
			   // 
			   // label3
			   // 
			   this->label3->AutoSize = true;
			   this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->label3->Location = System::Drawing::Point(422, 71);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(32, 20);
			   this->label3->TabIndex = 5;
			   this->label3->Text = L"B )";
			   // 
			   // label4
			   // 
			   this->label4->AutoSize = true;
			   this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->label4->Location = System::Drawing::Point(422, 117);
			   this->label4->Name = L"label4";
			   this->label4->Size = System::Drawing::Size(32, 20);
			   this->label4->TabIndex = 6;
			   this->label4->Text = L"C )";
			   // 
			   // Dialogo
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(933, 529);
			   this->Controls->Add(this->groupBox1);
			   this->Name = L"Dialogo";
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			   this->Text = L"Dialogo";
			   this->Load += gcnew System::EventHandler(this, &Dialogo::Dialogo_Load);
			   this->groupBox1->ResumeLayout(false);
			   this->groupBox1->PerformLayout();
			   this->ResumeLayout(false);

		   }
#pragma endregion
	private: System::Void Dialogo_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	private: void Preguntas()
	{
		int buena = 120;
		int me = 60;
		int mala = -120;
		
		preguntas = gcnew List<String^>();
		respuestas = gcnew List<List<String^>^>();
		impactos = gcnew List<List<int>^>();

		//1
		preguntas->Add("Los humanos somos naturalmente buenos o egoistas?");
		{
			List<String^>^ opcs = gcnew List<String^>();
			opcs->Add(" El humano nace bueno, la sociedad lo corrompe.");
			opcs->Add(" El humano no nace ni bueno ni malo, la sociedad lo moldea.");
			opcs->Add(" El humano nace malo y empeora con la sociedad.");
			respuestas->Add(opcs);

			List<int>^ confianza = gcnew List<int>();
			confianza->Add(me); confianza->Add(buena); confianza->Add(mala);
			impactos->Add(confianza);
		}

		//2
		preguntas->Add("Un procedimiento requiere que debas sacrificar a 1 persona para salvar 5, Que haces?");
		{
			List<String^>^ opcs = gcnew List<String^>();
			opcs->Add(" Buscar otra solucion, hare todo lo posible para salvar 5.");
			opcs->Add(" Sacrifico 1 vida para salvar 5, 4 vidas al precio de 1.");
			opcs->Add(" No hago nada, que se encargue el destino.");
			respuestas->Add(opcs);

			List<int>^ confianza = gcnew List<int>();
			confianza->Add(buena); confianza->Add(me); confianza->Add(mala);
			impactos->Add(confianza);
		}

		//3
		preguntas->Add("Como medirias el exito personal?");
		{
			List<String^>^ opcs = gcnew List<String^>();
			opcs->Add(" Por dinero, joyas, yates, esencia primordial.");
			opcs->Add(" Viviendo el presente, el futuro es incierto, mejor vivir a lo maximo.");
			opcs->Add(" Por autorrealizacion personal.");
			respuestas->Add(opcs);

			List<int>^ confianza = gcnew List<int>();
			confianza->Add(mala); confianza->Add(me); confianza->Add(buena);
			impactos->Add(confianza);
		}

		//4
		preguntas->Add("La felicidad es una meta o proceso?");
		{
			List<String^>^ opcs = gcnew List<String^>();
			opcs->Add(" La felicidad es una Meta final.");
			opcs->Add(" Buscar la felicidad significa una odisea sin fin de infelicidad.");
			opcs->Add(" Tenerla tanto de meta como procedimiento son formas validas.");
			respuestas->Add(opcs);

			List<int>^ confianza = gcnew List<int>();
			confianza->Add(me - me); confianza->Add(me); confianza->Add(buena);
			impactos->Add(confianza);
		}

		//5
		preguntas->Add("Lisander es trolazo?");
		{
			List<String^>^ opcs = gcnew List<String^>();
			opcs->Add(" Si.");
			opcs->Add(" Obvio.");
			opcs->Add(" Lo que se ve no se pregunta.");
			respuestas->Add(opcs);

			List<int>^ confianza = gcnew List<int>();
			confianza->Add(buena); confianza->Add(buena); confianza->Add(buena);
			impactos->Add(confianza);
		}
	}

	private: void mostrarPregunta()
	{
		if (preguntas == nullptr || preguntas->Count == 0) { return; }
		System::Random^ rand = gcnew System::Random();
		indicePregunta = rand->Next(0, preguntas->Count);

		label1->Text = preguntas[indicePregunta];
		List<String^>^ opts = respuestas[indicePregunta];

		button1->Text = (opts->Count > 0) ? opts[0] : "";
		button2->Text = (opts->Count > 1) ? opts[1] : "";
		button3->Text = (opts->Count > 2) ? opts[2] : "";
	}

	private: void Respuesta(int respuesta)
	{
		if (jugadorPtr != nullptr && impactos != nullptr && indicePregunta >= 0 && indicePregunta < impactos->Count)
		{
			List<int>^ imp = impactos[indicePregunta]; 
			if (imp != nullptr && respuesta >= 0 && respuesta < imp->Count) {
				int delta = imp[respuesta];
				jugadorPtr->setConfianza(jugadorPtr->getConfianza() + delta);
			}
		}
		if (preguntas != nullptr && indicePregunta >= 0 && indicePregunta < preguntas->Count) {
			preguntas->RemoveAt(indicePregunta);
			respuestas->RemoveAt(indicePregunta);
			if (impactos != nullptr && indicePregunta >= 0 && indicePregunta < impactos->Count)
				impactos->RemoveAt(indicePregunta);
		}

		this->Close(); 
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
		Graphics^ gBuffer = buffer->Graphics;









	}

};
}
