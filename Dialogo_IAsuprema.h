#pragma once

namespace TF1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Dialogo_IAsuprema
	/// </summary>
	public ref class Dialogo_IAsuprema : public System::Windows::Forms::Form
	{
	public:
		Dialogo_IAsuprema(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
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
	private: System::Windows::Forms::Panel^ pnlAliado;
	protected:
	private: System::Windows::Forms::Label^ lblMensaje;
	private: System::Windows::Forms::Label^ lblNombre;

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pnlAliado = (gcnew System::Windows::Forms::Panel());
			this->lblMensaje = (gcnew System::Windows::Forms::Label());
			this->lblNombre = (gcnew System::Windows::Forms::Label());
			this->pnlAliado->SuspendLayout();
			this->SuspendLayout();
			// 
			// pnlAliado
			// 
			this->pnlAliado->Controls->Add(this->lblMensaje);
			this->pnlAliado->Controls->Add(this->lblNombre);
			this->pnlAliado->Location = System::Drawing::Point(5, 251);
			this->pnlAliado->Name = L"pnlAliado";
			this->pnlAliado->Size = System::Drawing::Size(964, 240);
			this->pnlAliado->TabIndex = 1;
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
			this->lblNombre->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->lblNombre->Location = System::Drawing::Point(30, 20);
			this->lblNombre->Name = L"lblNombre";
			this->lblNombre->Size = System::Drawing::Size(52, 29);
			this->lblNombre->TabIndex = 0;
			this->lblNombre->Text = L"\?\?\?";
			// 
			// Dialogo_IAsuprema
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(969, 492);
			this->Controls->Add(this->pnlAliado);
			this->Name = L"Dialogo_IAsuprema";
			this->Text = L"Dialogo_IAsuprema";
			this->pnlAliado->ResumeLayout(false);
			this->pnlAliado->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
