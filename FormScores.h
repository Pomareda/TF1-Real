#pragma once
#include "File.h"

namespace TF1 {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class FormScores : public System::Windows::Forms::Form {
    public:
        FormScores() {
            InitializeComponent();
        }

    private:
        System::Windows::Forms::TabControl^ tabControl1;
        System::Windows::Forms::TabPage^ tabMundo1;
        System::Windows::Forms::TabPage^ tabMundo2;
        System::Windows::Forms::TabPage^ tabMundo3;
        System::Windows::Forms::Label^ lblTitulo;
        System::Windows::Forms::Button^ btnCerrar;
        System::ComponentModel::Container^ components;

        void InitializeComponent() {
            this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
            this->tabMundo1 = (gcnew System::Windows::Forms::TabPage());
            this->tabMundo2 = (gcnew System::Windows::Forms::TabPage());
            this->tabMundo3 = (gcnew System::Windows::Forms::TabPage());
            this->lblTitulo = (gcnew System::Windows::Forms::Label());
            this->btnCerrar = (gcnew System::Windows::Forms::Button());
            this->tabControl1->SuspendLayout();
            this->SuspendLayout();

            // 
            // lblTitulo
            // 
            this->lblTitulo->Font = (gcnew System::Drawing::Font(L"Arial", 20, System::Drawing::FontStyle::Bold));
            this->lblTitulo->Location = System::Drawing::Point(12, 9);
            this->lblTitulo->Name = L"lblTitulo";
            this->lblTitulo->Size = System::Drawing::Size(860, 50);
            this->lblTitulo->TabIndex = 0;
            this->lblTitulo->Text = L"TABLA DE PUNTUACIONES";
            this->lblTitulo->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

            // 
            // tabControl1
            // 
            this->tabControl1->Controls->Add(this->tabMundo1);
            this->tabControl1->Controls->Add(this->tabMundo2);
            this->tabControl1->Controls->Add(this->tabMundo3);
            this->tabControl1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
            this->tabControl1->Location = System::Drawing::Point(12, 70);
            this->tabControl1->Name = L"tabControl1";
            this->tabControl1->SelectedIndex = 0;
            this->tabControl1->Size = System::Drawing::Size(860, 490);
            this->tabControl1->TabIndex = 1;

            // 
            // tabMundo1
            // 
            this->tabMundo1->BackColor = System::Drawing::Color::White;
            this->tabMundo1->Location = System::Drawing::Point(4, 25);
            this->tabMundo1->Name = L"tabMundo1";
            this->tabMundo1->Padding = System::Windows::Forms::Padding(10);
            this->tabMundo1->Size = System::Drawing::Size(852, 461);
            this->tabMundo1->TabIndex = 0;
            this->tabMundo1->Text = L"Mundo 1";

            // 
            // tabMundo2
            // 
            this->tabMundo2->BackColor = System::Drawing::Color::White;
            this->tabMundo2->Location = System::Drawing::Point(4, 25);
            this->tabMundo2->Name = L"tabMundo2";
            this->tabMundo2->Padding = System::Windows::Forms::Padding(10);
            this->tabMundo2->Size = System::Drawing::Size(852, 461);
            this->tabMundo2->TabIndex = 1;
            this->tabMundo2->Text = L"Mundo 2";

            // 
            // tabMundo3
            // 
            this->tabMundo3->BackColor = System::Drawing::Color::White;
            this->tabMundo3->Location = System::Drawing::Point(4, 25);
            this->tabMundo3->Name = L"tabMundo3";
            this->tabMundo3->Padding = System::Windows::Forms::Padding(10);
            this->tabMundo3->Size = System::Drawing::Size(852, 461);
            this->tabMundo3->TabIndex = 2;
            this->tabMundo3->Text = L"Mundo 3";

            // 
            // btnCerrar
            // 
            this->btnCerrar->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
            this->btnCerrar->Location = System::Drawing::Point(362, 575);
            this->btnCerrar->Name = L"btnCerrar";
            this->btnCerrar->Size = System::Drawing::Size(160, 45);
            this->btnCerrar->TabIndex = 2;
            this->btnCerrar->Text = L"Cerrar";
            this->btnCerrar->UseVisualStyleBackColor = true;
            this->btnCerrar->Click += gcnew System::EventHandler(this, &FormScores::btnCerrar_Click);

            // 
            // FormScores
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::WhiteSmoke;
            this->ClientSize = System::Drawing::Size(884, 631);
            this->Controls->Add(this->btnCerrar);
            this->Controls->Add(this->tabControl1);
            this->Controls->Add(this->lblTitulo);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->Name = L"FormScores";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Puntuaciones - Todos los Mundos";
            this->Load += gcnew System::EventHandler(this, &FormScores::FormScores_Load);
            this->tabControl1->ResumeLayout(false);
            this->ResumeLayout(false);
        }

        void FormScores_Load(Object^ sender, EventArgs^ e) {
            CargarScoresEnTab(tabMundo1, 1);
            CargarScoresEnTab(tabMundo2, 2);
            CargarScoresEnTab(tabMundo3, 3);
        }

        void CargarScoresEnTab(TabPage^ tab, int mundo) {
            try {
                FileScores* fileScores = new FileScores();
                vector<Score> scores = fileScores->LeerScoresPorMundo(mundo);

                for (size_t i = 0; i < scores.size(); i++) {
                    for (size_t j = i + 1; j < scores.size(); j++) {
                        if (scores[j].puntaje > scores[i].puntaje) {
                            Score temp = scores[i];
                            scores[i] = scores[j];
                            scores[j] = temp;
                        }
                    }
                }

                DataGridView^ dgv = gcnew DataGridView();
                dgv->Location = System::Drawing::Point(10, 10);
                dgv->Size = System::Drawing::Size(830, 440);
                dgv->ReadOnly = true;
                dgv->AllowUserToAddRows = false;
                dgv->AllowUserToResizeRows = false; 
                dgv->AllowUserToResizeColumns = true;  
                dgv->RowHeadersVisible = false;  
                dgv->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
                dgv->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
                dgv->ColumnHeadersHeight = 35;
                dgv->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
                dgv->MultiSelect = false;
                dgv->RowTemplate->Height = 30;  

                dgv->BackgroundColor = System::Drawing::Color::White;
                dgv->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
                dgv->GridColor = System::Drawing::Color::LightGray;

                dgv->ColumnHeadersDefaultCellStyle->BackColor = System::Drawing::Color::FromArgb(70, 130, 180);
                dgv->ColumnHeadersDefaultCellStyle->ForeColor = System::Drawing::Color::White;
                dgv->ColumnHeadersDefaultCellStyle->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
                dgv->ColumnHeadersDefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleCenter;
                dgv->EnableHeadersVisualStyles = false;

                dgv->DefaultCellStyle->Font = (gcnew System::Drawing::Font(L"Arial", 9));
                dgv->DefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightSkyBlue;
                dgv->DefaultCellStyle->SelectionForeColor = System::Drawing::Color::Black;
                dgv->AlternatingRowsDefaultCellStyle->BackColor = System::Drawing::Color::FromArgb(240, 240, 240);

                dgv->Columns->Add("Jugador", "Jugador");
                dgv->Columns->Add("Puntaje", "Puntaje");

                if (mundo == 1) {
                    dgv->Columns->Add("Confianza", "Confianza");
                    dgv->Columns->Add("Enemigos", "Enemigos");
                    dgv->Columns->Add("Recursos", "Recursos");
                }
                else if (mundo == 2) {
                    dgv->Columns->Add("Vidas", "Vidas");
                    dgv->Columns->Add("Tiempo", "Tiempo (s)");
                }
                else if (mundo == 3) {
                    dgv->Columns->Add("Dano", "Daño");
                    dgv->Columns->Add("Vidas", "Vidas");
                    dgv->Columns->Add("Tiempo", "Tiempo (s)");
                }

                dgv->Columns->Add("Fecha", "Fecha");

                // Centrar todas las columnas excepto "Jugador"
                for (int i = 1; i < dgv->Columns->Count; i++) {
                    dgv->Columns[i]->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleCenter;
                }

                if (scores.size() == 0) {
                    // Si no hay scores, mostrar mensaje
                    Label^ lblNoData = gcnew Label();
                    lblNoData->Text = "No hay puntuaciones registradas para este mundo";
                    lblNoData->Font = (gcnew System::Drawing::Font(L"Arial", 14, System::Drawing::FontStyle::Italic));
                    lblNoData->ForeColor = System::Drawing::Color::Gray;
                    lblNoData->Location = System::Drawing::Point(200, 200);
                    lblNoData->Size = System::Drawing::Size(450, 50);
                    lblNoData->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
                    tab->Controls->Add(lblNoData);
                }
                else {
                    for (size_t i = 0; i < scores.size(); i++) {
                        String^ nombre = gcnew String(scores[i].nombreJugador);
                        String^ puntaje = scores[i].puntaje.ToString();
                        String^ fecha = gcnew String(scores[i].fecha);

                        if (mundo == 1) {
                            dgv->Rows->Add(
                                nombre,
                                puntaje,
                                scores[i].confianza.ToString(),
                                scores[i].enemigosVencidos.ToString(),
                                scores[i].recursosRecogidos.ToString(),
                                fecha
                            );
                        }
                        else if (mundo == 2) {
                            dgv->Rows->Add(
                                nombre,
                                puntaje,
                                scores[i].vidas.ToString(),
                                scores[i].tiempo.ToString(),
                                fecha
                            );
                        }
                        else if (mundo == 3) {
                            dgv->Rows->Add(
                                nombre,
                                puntaje,
                                scores[i].dano.ToString(),
                                scores[i].vidas.ToString(),
                                scores[i].tiempo.ToString(),
                                fecha
                            );
                        }
                    }

                    if (dgv->Rows->Count > 0) {
                        dgv->Rows[0]->DefaultCellStyle->BackColor = System::Drawing::Color::Gold;
                        dgv->Rows[0]->DefaultCellStyle->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
                    }

                    tab->Controls->Add(dgv);
                }

                delete fileScores;
            }
            catch (...) {
                Label^ lblError = gcnew Label();
                lblError->Text = "Error al cargar puntuaciones del Mundo " + mundo.ToString();
                lblError->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold));
                lblError->ForeColor = System::Drawing::Color::Red;
                lblError->Location = System::Drawing::Point(200, 200);
                lblError->Size = System::Drawing::Size(450, 50);
                lblError->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
                tab->Controls->Add(lblError);
            }
        }

        void btnCerrar_Click(Object^ sender, EventArgs^ e) {
            this->Close();
        }
    };
}