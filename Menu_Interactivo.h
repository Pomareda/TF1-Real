#pragma once
#include "Menu_Creditos.h"
#include "FormJuego.h"
#include "Menu_Instrucciones.h"
namespace TF1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Menu_Interactivo
	/// </summary>
	public ref class Menu_Interactivo : public System::Windows::Forms::Form
	{
	public:
		Menu_Interactivo(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
			g = Panel_Inicio->CreateGraphics();
			space = BufferedGraphicsManager::Current;
			buffer = space->Allocate(g, Panel_Inicio->ClientRectangle);
			bmpFondo1 = gcnew Bitmap("Imagenes/Menu/1.png");
			bmpFondo2 = gcnew Bitmap("Imagenes/Menu/2.png");
			bmpFondo3 = gcnew Bitmap("Imagenes/Menu/3.png");
			boton_credits = gcnew Bitmap("Imagenes/Menu/Boton_credits_verdadero.png");
			boton_credits->MakeTransparent(boton_credits->GetPixel(0, 0));
			boton_jugar = gcnew Bitmap("Imagenes/Menu/Boton_sinfondo.png");
			boton_jugar->MakeTransparent(boton_jugar->GetPixel(0, 0));
			boton_rules = gcnew Bitmap("Imagenes/Menu/Boton_Rules_verdadero.png");
			boton_rules->MakeTransparent(boton_rules->GetPixel(0, 0));
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Menu_Interactivo()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ Panel_Inicio;
	private: System::ComponentModel::IContainer^ components;
	protected:

	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>

		Bitmap^ bmpFondo1;
		Bitmap^ bmpFondo2;
		Bitmap^ bmpFondo3;
		Graphics^ g;
		BufferedGraphicsContext^ space;
		Bitmap^ boton_credits;
		Bitmap^ boton_jugar;
		Bitmap^ boton_rules;
		int contador_imagen = 1;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Button^ btn2;
	private: System::Windows::Forms::Button^ btn3;


	private: System::Windows::Forms::Button^ btn1;






		   BufferedGraphics^ buffer;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Método necesario para admitir el Diseñador. No se puede modificar
		   /// el contenido de este método con el editor de código.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Menu_Interactivo::typeid));
			   this->Panel_Inicio = (gcnew System::Windows::Forms::Panel());
			   this->btn2 = (gcnew System::Windows::Forms::Button());
			   this->btn3 = (gcnew System::Windows::Forms::Button());
			   this->btn1 = (gcnew System::Windows::Forms::Button());
			   this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			   this->Panel_Inicio->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // Panel_Inicio
			   // 
			   this->Panel_Inicio->BackColor = System::Drawing::Color::Transparent;
			   this->Panel_Inicio->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Panel_Inicio.BackgroundImage")));
			   this->Panel_Inicio->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			   this->Panel_Inicio->Controls->Add(this->btn2);
			   this->Panel_Inicio->Controls->Add(this->btn3);
			   this->Panel_Inicio->Controls->Add(this->btn1);
			   this->Panel_Inicio->Cursor = System::Windows::Forms::Cursors::Default;
			   this->Panel_Inicio->Location = System::Drawing::Point(-16, -11);
			   this->Panel_Inicio->Name = L"Panel_Inicio";
			   this->Panel_Inicio->Size = System::Drawing::Size(647, 459);
			   this->Panel_Inicio->TabIndex = 1;
			   this->Panel_Inicio->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Menu_Interactivo::Panel_Inicio_Paint);
			   // 
			   // btn2
			   // 
			   this->btn2->BackColor = System::Drawing::Color::Transparent;
			   this->btn2->FlatAppearance->BorderSize = 0;
			   this->btn2->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			   this->btn2->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			   this->btn2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->btn2->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			   this->btn2->Location = System::Drawing::Point(125, 272);
			   this->btn2->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			   this->btn2->Name = L"btn2";
			   this->btn2->Size = System::Drawing::Size(184, 76);
			   this->btn2->TabIndex = 2;
			   this->btn2->UseVisualStyleBackColor = false;
			   this->btn2->Click += gcnew System::EventHandler(this, &Menu_Interactivo::button2_Click);
			   // 
			   // btn3
			   // 
			   this->btn3->BackColor = System::Drawing::Color::Transparent;
			   this->btn3->FlatAppearance->BorderSize = 0;
			   this->btn3->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			   this->btn3->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			   this->btn3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->btn3->Location = System::Drawing::Point(125, 353);
			   this->btn3->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			   this->btn3->Name = L"btn3";
			   this->btn3->Size = System::Drawing::Size(184, 76);
			   this->btn3->TabIndex = 1;
			   this->btn3->UseVisualStyleBackColor = false;
			   this->btn3->Click += gcnew System::EventHandler(this, &Menu_Interactivo::button3_Click);
			   // 
			   // btn1
			   // 
			   this->btn1->BackColor = System::Drawing::Color::Transparent;
			   this->btn1->FlatAppearance->BorderSize = 0;
			   this->btn1->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			   this->btn1->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			   this->btn1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->btn1->Location = System::Drawing::Point(125, 191);
			   this->btn1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			   this->btn1->Name = L"btn1";
			   this->btn1->Size = System::Drawing::Size(184, 76);
			   this->btn1->TabIndex = 0;
			   this->btn1->UseVisualStyleBackColor = false;
			   this->btn1->Click += gcnew System::EventHandler(this, &Menu_Interactivo::button1_Click);
			   // 
			   // timer1
			   // 
			   this->timer1->Enabled = true;
			   this->timer1->Interval = 600;
			   this->timer1->Tick += gcnew System::EventHandler(this, &Menu_Interactivo::timer1_Tick);
			   // 
			   // Menu_Interactivo
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::SystemColors::Control;
			   this->ClientSize = System::Drawing::Size(622, 439);
			   this->Controls->Add(this->Panel_Inicio);
			   this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			   this->Name = L"Menu_Interactivo";
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			   this->Text = L"Menu_Interactivo";
			   this->Panel_Inicio->ResumeLayout(false);
			   this->ResumeLayout(false);

		   }
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		buffer->Graphics->Clear(Color::WhiteSmoke);

		if (contador_imagen == 4) {
			contador_imagen = 1;
		}
		if (contador_imagen == 1) {
			buffer->Graphics->DrawImage(bmpFondo1, 0, 0, bmpFondo1->Width * 1, bmpFondo1->Height * 1);
			contador_imagen++;
		}
		else if (contador_imagen == 2) {
			buffer->Graphics->DrawImage(bmpFondo2, 0, 0, bmpFondo2->Width * 1, bmpFondo2->Height * 1);
			contador_imagen++;
		}
		else if (contador_imagen == 3) {
			buffer->Graphics->DrawImage(bmpFondo3, 0, 0, bmpFondo3->Width * 1, bmpFondo3->Height * 1);
			contador_imagen++;
		}
		if (boton_credits != nullptr) {
			this->btn3->BackgroundImage = boton_credits;
			this->btn3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
		}
		this->btn1->BackgroundImage = boton_jugar;
		this->btn1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
		this->btn2->BackgroundImage = boton_rules;
		this->btn2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
		buffer->Render(g);
		buffer->Graphics->Clear(Color::WhiteSmoke);
	}
	private: System::Void Panel_Inicio_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		MenuForm^ mundo1 = gcnew MenuForm();
		mundo1->Show();
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		Menu_Instrucciones^ Instrucciones = gcnew Menu_Instrucciones();
		Instrucciones->ShowDialog();
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		Menu_Creditos^ creditos = gcnew Menu_Creditos();
		creditos->ShowDialog();
	}
	};
}