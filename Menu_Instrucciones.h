#pragma once
#include "Animacion_instrucciones.h"
namespace TF1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Menu_Instrucciones
	/// </summary>
	public ref class Menu_Instrucciones : public System::Windows::Forms::Form
	{
	public:
		Menu_Instrucciones(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
			bmpFondo_instrucciones = gcnew Bitmap("Imagenes/Instrucciones/sprite_fondo.png");
			instrucciones = gcnew Fondo_Instrucciones();
			g1 = this->CreateGraphics();
			canvas = BufferedGraphicsManager::Current;
			buffer = canvas->Allocate(g1, this->ClientRectangle);
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Menu_Instrucciones()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^ components;
		   Fondo_Instrucciones^ instrucciones;
		   Graphics^ g1;
		   BufferedGraphicsContext^ canvas;
		   BufferedGraphics^ buffer;
	protected:
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Panel^ panel1;







	protected:

	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>

		Bitmap^ bmpFondo_instrucciones;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Menu_Instrucciones::typeid));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &Menu_Instrucciones::timer1_Tick);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->label3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->label3->Location = System::Drawing::Point(4, 245);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(296, 100);
			this->label3->TabIndex = 2;
			this->label3->Text = L"<<C O N T R O L E S>> \r\n Interactuar: [E]\r\n                                      "
				L"  W\r\nMovimiento/ seleccion: A S D";
			this->label3->Click += gcnew System::EventHandler(this, &Menu_Instrucciones::label3_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->label1->Location = System::Drawing::Point(4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(248, 25);
			this->label1->TabIndex = 0;
			this->label1->Text = L"<<INSTRUCCIONES>> ";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->label2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->label2->Location = System::Drawing::Point(4, 25);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(579, 200);
			this->label2->TabIndex = 1;
			this->label2->Text = resources->GetString(L"label2.Text");
			this->label2->Click += gcnew System::EventHandler(this, &Menu_Instrucciones::label2_Click);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::LightCyan;
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Location = System::Drawing::Point(472, 39);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(657, 380);
			this->panel1->TabIndex = 3;
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Menu_Instrucciones::panel1_Paint);
			// 
			// Menu_Instrucciones
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1141, 548);
			this->Controls->Add(this->panel1);
			this->DoubleBuffered = true;
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"Menu_Instrucciones";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Menu_Instrucciones";
			this->Load += gcnew System::EventHandler(this, &Menu_Instrucciones::Menu_Instrucciones_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Menu_Instrucciones::Menu_Instrucciones_Paint);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion



	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Menu_Instrucciones_Load(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void Menu_Instrucciones_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (this->IsDisposed || !this->IsHandleCreated || this->timer1 == nullptr || !this->timer1->Enabled)
			return;

		// Crear bitmap temporal del tamaño del formulario
		Bitmap^ backBmp = gcnew Bitmap(this->ClientSize.Width, this->ClientSize.Height);
		Graphics^ gBack = Graphics::FromImage(backBmp);
		gBack->Clear(Color::WhiteSmoke);
		instrucciones->mover(gBack);
		instrucciones->dibujar(gBack, bmpFondo_instrucciones);

		buffer->Graphics->Clear(Color::WhiteSmoke);
		buffer->Graphics->DrawImage(backBmp, Point(0, 0));

		System::Drawing::Rectangle labelRect1 = System::Drawing::Rectangle(this->label1->Location, this->label1->Size);
		System::Drawing::Rectangle clientRect = System::Drawing::Rectangle(Point(0, 0), this->ClientSize);
		labelRect1.Intersect(clientRect);

		System::Drawing::Rectangle labelRect2 = System::Drawing::Rectangle(this->label2->Location, this->label2->Size);
		labelRect2.Intersect(clientRect);

		System::Drawing::Rectangle labelRect3 = System::Drawing::Rectangle(this->label3->Location, this->label3->Size);
		labelRect3.Intersect(clientRect);

		

		buffer->Render(gBack);
		buffer->Render(g1);

		// Limpiar recursos temporales
		delete gBack;
		delete backBmp;
	}

	private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}