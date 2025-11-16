#pragma once

namespace TF1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class Dialogo : public System::Windows::Forms::Form
	{
	public:
		Dialogo(void)
		{
			InitializeComponent();
			g = this->CreateGraphics();
			canvas = BufferedGraphicsManager::Current;
			buffer = canvas->Allocate(g, this->ClientRectangle);

			// no lee las imagenes ns porque 
		/*	bmpDialogoIA = gcnew Bitmap("diddyDroid.png");
			bmpDialogoProta = gcnew Bitmap("prota.png");*/
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

		//falta ponerlo
		Bitmap^ fondo;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button4;


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
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->button3 = (gcnew System::Windows::Forms::Button());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->button4 = (gcnew System::Windows::Forms::Button());
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
			   this->groupBox1->Controls->Add(this->button4);
			   this->groupBox1->Controls->Add(this->label1);
			   this->groupBox1->Controls->Add(this->button3);
			   this->groupBox1->Controls->Add(this->button2);
			   this->groupBox1->Controls->Add(this->button1);
			   this->groupBox1->Location = System::Drawing::Point(12, 526);
			   this->groupBox1->Name = L"groupBox1";
			   this->groupBox1->Size = System::Drawing::Size(909, 201);
			   this->groupBox1->TabIndex = 0;
			   this->groupBox1->TabStop = false;
			   // 
			   // button1
			   // 
			   this->button1->Location = System::Drawing::Point(457, 16);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(433, 40);
			   this->button1->TabIndex = 0;
			   this->button1->Text = L"button1";
			   this->button1->UseVisualStyleBackColor = true;
			   this->button1->Click += gcnew System::EventHandler(this, &Dialogo::button1_Click);
			   // 
			   // button2
			   // 
			   this->button2->Location = System::Drawing::Point(457, 62);
			   this->button2->Name = L"button2";
			   this->button2->Size = System::Drawing::Size(433, 40);
			   this->button2->TabIndex = 1;
			   this->button2->Text = L"button2";
			   this->button2->UseVisualStyleBackColor = true;
			   this->button2->Click += gcnew System::EventHandler(this, &Dialogo::button2_Click);
			   // 
			   // button3
			   // 
			   this->button3->Location = System::Drawing::Point(457, 108);
			   this->button3->Name = L"button3";
			   this->button3->Size = System::Drawing::Size(433, 40);
			   this->button3->TabIndex = 2;
			   this->button3->Text = L"button3";
			   this->button3->UseVisualStyleBackColor = true;
			   this->button3->Click += gcnew System::EventHandler(this, &Dialogo::button3_Click);
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Location = System::Drawing::Point(16, 16);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(35, 13);
			   this->label1->TabIndex = 3;
			   this->label1->Text = L"label1";
			   // 
			   // button4
			   // 
			   this->button4->Location = System::Drawing::Point(457, 154);
			   this->button4->Name = L"button4";
			   this->button4->Size = System::Drawing::Size(433, 40);
			   this->button4->TabIndex = 4;
			   this->button4->Text = L"button4";
			   this->button4->UseVisualStyleBackColor = true;
			   this->button4->Click += gcnew System::EventHandler(this, &Dialogo::button4_Click);
			   // 
			   // Dialogo
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(933, 729);
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
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {

		Graphics^ gBuffer = buffer->Graphics;



	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
