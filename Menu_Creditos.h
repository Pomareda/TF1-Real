#pragma once

namespace TF1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Menu_Creditos
	/// </summary>
	public ref class Menu_Creditos : public System::Windows::Forms::Form
	{
	public:
		Menu_Creditos(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
			//

			bmpFondo_creditos = gcnew Bitmap("Imagenes/Creditos/Fondo_creditos_generico.jpg");
			this->Panel_Inicio->BackgroundImage = bmpFondo_creditos;
			this->Panel_Inicio->BackgroundImageLayout = ImageLayout::Stretch;
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Menu_Creditos()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ Panel_Inicio;
	protected:
	private: System::Windows::Forms::PictureBox^ pictureBox1;

	private: System::Windows::Forms::PictureBox^ pictureBox4;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ lbl1;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label4;





	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container^ components;
		Bitmap^ bmpFondo_creditos;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Menu_Creditos::typeid));
			this->Panel_Inicio = (gcnew System::Windows::Forms::Panel());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->lbl1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->Panel_Inicio->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// Panel_Inicio
			// 
			this->Panel_Inicio->BackColor = System::Drawing::Color::Transparent;
			this->Panel_Inicio->Controls->Add(this->label5);
			this->Panel_Inicio->Controls->Add(this->label2);
			this->Panel_Inicio->Controls->Add(this->label1);
			this->Panel_Inicio->Controls->Add(this->label4);
			this->Panel_Inicio->Controls->Add(this->textBox4);
			this->Panel_Inicio->Controls->Add(this->textBox3);
			this->Panel_Inicio->Controls->Add(this->textBox2);
			this->Panel_Inicio->Controls->Add(this->label3);
			this->Panel_Inicio->Controls->Add(this->textBox1);
			this->Panel_Inicio->Controls->Add(this->lbl1);
			this->Panel_Inicio->Controls->Add(this->pictureBox4);
			this->Panel_Inicio->Controls->Add(this->pictureBox3);
			this->Panel_Inicio->Controls->Add(this->pictureBox2);
			this->Panel_Inicio->Controls->Add(this->pictureBox1);
			this->Panel_Inicio->Location = System::Drawing::Point(-9, -23);
			this->Panel_Inicio->Margin = System::Windows::Forms::Padding(4);
			this->Panel_Inicio->Name = L"Panel_Inicio";
			this->Panel_Inicio->Size = System::Drawing::Size(855, 543);
			this->Panel_Inicio->TabIndex = 2;
			this->Panel_Inicio->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Menu_Creditos::Panel_Inicio_Paint);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"MS Gothic", 36, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::Color::Transparent;
			this->label5->Location = System::Drawing::Point(122, 379);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(614, 60);
			this->label5->TabIndex = 16;
			this->label5->Text = L"¡GRACIAS POR JUGAR!";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label2->Font = (gcnew System::Drawing::Font(L"MingLiU_MSCS-ExtB", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::Transparent;
			this->label2->Location = System::Drawing::Point(668, 323);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(166, 25);
			this->label2->TabIndex = 10;
			this->label2->Text = L"Robert Poma";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label1->Font = (gcnew System::Drawing::Font(L"MingLiU_MSCS-ExtB", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::Transparent;
			this->label1->Location = System::Drawing::Point(457, 323);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(180, 25);
			this->label1->TabIndex = 9;
			this->label1->Text = L"Joaquin Luna";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"MS Gothic", 36, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::Transparent;
			this->label4->Location = System::Drawing::Point(299, 48);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(273, 60);
			this->label4->TabIndex = 15;
			this->label4->Text = L"CREDITOS";
			// 
			// textBox4
			// 
			this->textBox4->BackColor = System::Drawing::Color::DarkGoldenrod;
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Modern No. 20", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox4->Location = System::Drawing::Point(487, 133);
			this->textBox4->Multiline = true;
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(100, 23);
			this->textBox4->TabIndex = 14;
			this->textBox4->Text = L"      Tvpu";
			// 
			// textBox3
			// 
			this->textBox3->BackColor = System::Drawing::Color::Orange;
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Modern No. 20", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox3->Location = System::Drawing::Point(707, 133);
			this->textBox3->Multiline = true;
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 23);
			this->textBox3->TabIndex = 13;
			this->textBox3->Text = L"   Pomareda";
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::Color::Cyan;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Modern No. 20", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox2->Location = System::Drawing::Point(269, 133);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 23);
			this->textBox2->TabIndex = 12;
			this->textBox2->TabStop = false;
			this->textBox2->Text = L"  ElLisan23";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label3->Font = (gcnew System::Drawing::Font(L"MingLiU_MSCS-ExtB", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::Transparent;
			this->label3->Location = System::Drawing::Point(210, 323);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(222, 25);
			this->label3->TabIndex = 11;
			this->label3->Text = L"Lisander Concha";
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::DarkGoldenrod;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Modern No. 20", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(51, 133);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 23);
			this->textBox1->TabIndex = 8;
			this->textBox1->Text = L"    Elotezzz";
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Menu_Creditos::textBox1_TextChanged);
			// 
			// lbl1
			// 
			this->lbl1->AutoSize = true;
			this->lbl1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->lbl1->Font = (gcnew System::Drawing::Font(L"MingLiU_MSCS-ExtB", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbl1->ForeColor = System::Drawing::Color::Transparent;
			this->lbl1->Location = System::Drawing::Point(8, 323);
			this->lbl1->Name = L"lbl1";
			this->lbl1->Size = System::Drawing::Size(208, 25);
			this->lbl1->TabIndex = 7;
			this->lbl1->Text = L"Khaled Loarte ";
			this->lbl1->Click += gcnew System::EventHandler(this, &Menu_Creditos::label1_Click);
			// 
			// pictureBox4
			// 
			this->pictureBox4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.Image")));
			this->pictureBox4->Location = System::Drawing::Point(241, 152);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(152, 168);
			this->pictureBox4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox4->TabIndex = 6;
			this->pictureBox4->TabStop = false;
			this->pictureBox4->Click += gcnew System::EventHandler(this, &Menu_Creditos::pictureBox4_Click);
			// 
			// pictureBox3
			// 
			this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.Image")));
			this->pictureBox3->Location = System::Drawing::Point(464, 152);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(152, 168);
			this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox3->TabIndex = 5;
			this->pictureBox3->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(686, 152);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(136, 168);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 4;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(33, 152);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(136, 168);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 3;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &Menu_Creditos::pictureBox1_Click);
			// 
			// Menu_Creditos
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->ClientSize = System::Drawing::Size(837, 496);
			this->Controls->Add(this->Panel_Inicio);
			this->Name = L"Menu_Creditos";
			this->Text = L"Menu_Creditos";
			this->Panel_Inicio->ResumeLayout(false);
			this->Panel_Inicio->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Panel_Inicio_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pictureBox4_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
