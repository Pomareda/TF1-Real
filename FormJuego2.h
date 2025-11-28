#pragma once
#include "JugadorIA.h"
#include "Controladora.h"
#include "PlataformaM2.h"
#include "EnemigoM2.h"

namespace TF1 {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::IO;

   
    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            jugador = gcnew JugadorIA(gcnew Bitmap("Imagenes/personajeIA.png"));
			control = gcnew Controladora(gcnew Bitmap("Imagenes/posibleMapa2.jpg"), nullptr, this->ClientRectangle.Width, this->ClientRectangle.Height);

            EnemigoM2^ en1 = gcnew EnemigoM2(200, 2500, 0, 0);
            EnemigoM2^ en2 = gcnew EnemigoM2(100, 1800, 0, 0);
            EnemigoM2^ en3 = gcnew EnemigoM2(350, 2200, 0, 0);
            control->agregarEnemigoM2(en1);
            control->agregarEnemigoM2(en2);
            control->agregarEnemigoM2(en3);

            scrollY = 0;
            contadorPlataformas = 0;
            modoDebug = false;
            creandoPlataforma = false;

            plataformas = gcnew System::Collections::Generic::List<PlataformaM2^>();
            cargarPlataformas();
        }

    protected:
        ~MyForm()
        {
            if (components) delete components;
        }

    private:
        System::ComponentModel::IContainer^ components;
        System::Windows::Forms::Timer^ timer1;
        System::Windows::Forms::PictureBox^ pictureBox1;
        JugadorIA^ jugador;
		Controladora^ control;

        int scrollY;
        bool modoDebug = false;
        bool creandoPlataforma = false;
        Point puntoInicio;
        Point puntoActual;
        int contadorPlataformas = 0;

        System::Collections::Generic::List<PlataformaM2^>^ plataformas;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->components = (gcnew System::ComponentModel::Container());
            this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
            this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
            this->SuspendLayout();
            // 
            // timer1
            // 
            this->timer1->Enabled = true;
            this->timer1->Interval = 20;
            this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
            // 
            // pictureBox1
            // 
            this->pictureBox1->Location = System::Drawing::Point(0, -1);
            this->pictureBox1->Name = L"pictureBox1";
            this->pictureBox1->Size = System::Drawing::Size(501, 547);
            this->pictureBox1->TabIndex = 0;
            this->pictureBox1->TabStop = false;
            this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseDown);
            this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseMove);
            this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseUp);
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(498, 544);
            this->Controls->Add(this->pictureBox1);
            this->DoubleBuffered = true;
            this->MaximizeBox = false;
            this->Name = L"MyForm";
            this->Text = L"Prueba Salto";
            this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
            this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
            this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
            this->ResumeLayout(false);
        }
#pragma endregion

    private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
        if (pictureBox1->BackgroundImage == nullptr) {
            return;
        }

        Graphics^ G = pictureBox1->CreateGraphics();
        BufferedGraphicsContext^ Espacio = BufferedGraphicsManager::Current;
        BufferedGraphics^ Canvas = Espacio->Allocate(G, pictureBox1->ClientRectangle);

        int scrollYAnterior = scrollY;
        int altoTotal = pictureBox1->BackgroundImage->Height;

        jugador->aplicarGravedad(altoTotal);
        jugador->aumentarCarga();
        jugador->mover();
        colisiones();
        moverPlataformasHorizontalmente();

        control->actualizarEnemigosM2(jugador->getX(), jugador->getY(),pictureBox1->BackgroundImage->Width, altoTotal);


        if (control->colisionProyectilesM2(jugador->getRect())) {
            //aca le baja vida??
        }

        int posicionJugador = jugador->getY();
        scrollY = posicionJugador - pictureBox1->Height / 2;

        int maxScroll = pictureBox1->BackgroundImage->Height - pictureBox1->Height;
        if (scrollY > maxScroll) scrollY = maxScroll;
        if (scrollY < 0) scrollY = 0;

        System::Drawing::Rectangle porcionImagen = System::Drawing::Rectangle(
            0, scrollY, pictureBox1->Width, pictureBox1->Height
        );

        System::Drawing::Rectangle destinoPantalla = System::Drawing::Rectangle(
            0, 0, pictureBox1->Width, pictureBox1->Height
        );

        // Dibujar fondo
        Canvas->Graphics->DrawImage(
            pictureBox1->BackgroundImage,
            destinoPantalla,
            porcionImagen,
            GraphicsUnit::Pixel
        );

        for each (PlataformaM2 ^ p in plataformas) {
            p->dibujar(Canvas->Graphics, scrollY);
        }

        control->dibujarEnemigosM2(Canvas->Graphics, scrollY);

        // Dibujar jugador
        jugador->dibujarConScroll(Canvas->Graphics, scrollY);

        if (modoDebug) {
            dibujarColisiones(Canvas->Graphics);
        }

        if (creandoPlataforma) {
            int x = Math::Min(puntoInicio.X, puntoActual.X);
            int y = Math::Min(puntoInicio.Y, puntoActual.Y);
            int ancho = Math::Abs(puntoActual.X - puntoInicio.X);
            int alto = Math::Abs(puntoActual.Y - puntoInicio.Y);

            Canvas->Graphics->DrawRectangle(Pens::White, x, y, ancho, alto);
            Canvas->Graphics->FillRectangle(
                gcnew SolidBrush(Color::FromArgb(50, 255, 255, 255)),
                x, y, ancho, alto
            );
        }

        Canvas->Render(G);
        delete Canvas;
        delete Espacio;
        delete G;
    }

    private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
        switch (e->KeyCode) {
        case Keys::W:
            jugador->empezarCarga();
            break;
        case Keys::A:
            jugador->setIzquierda(true);
            break;
        case Keys::D:
            jugador->setDerecha(true);
            break;
        case Keys::F1:
            modoDebug = !modoDebug;
            MessageBox::Show(modoDebug ? "Modo Debug Activado" : "Modo Debug Desactivado");
            break;
        case Keys::F2:
            guardarPlataformas();
            MessageBox::Show("Plataformas guardadas!");
            break;
        case Keys::F3:
            cargarPlataformas();
            MessageBox::Show("Plataformas recargadas!");
            break;
        case Keys::F6:
            eliminarUltimaPlataforma();
            MessageBox::Show("Plataforma eliminada!");
            break;
        }
    }

    private: System::Void MyForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
        switch (e->KeyCode)
        {
        case Keys::W:
            jugador->liberarSalto();
            break;
        case Keys::A:
            jugador->setIzquierda(false);
            break;
        case Keys::D:
            jugador->setDerecha(false);
            break;
        }
    }

    private: System::Void MyForm_MouseDown(System::Object^ sender, MouseEventArgs^ e) {
        if (e->Button == System::Windows::Forms::MouseButtons::Right) {
            creandoPlataforma = true;
            puntoInicio = e->Location;
            puntoActual = e->Location;
        }
    }

    private: System::Void MyForm_MouseMove(System::Object^ sender, MouseEventArgs^ e) {
        if (creandoPlataforma) {
            puntoActual = e->Location;
        }
    }

    private: Void crearPlataforma(int x, int y, int ancho, int alto) {
        PlataformaM2^ nueva = gcnew PlataformaM2(x, y, ancho, alto);
        plataformas->Add(nueva);
        contadorPlataformas++;
    }

    private: System::Void MyForm_MouseUp(System::Object^ sender, MouseEventArgs^ e) {
        if (creandoPlataforma && e->Button == System::Windows::Forms::MouseButtons::Right) {
            creandoPlataforma = false;

            int x = Math::Min(puntoInicio.X, puntoActual.X);
            int y = Math::Min(puntoInicio.Y, puntoActual.Y);
            int ancho = Math::Abs(puntoActual.X - puntoInicio.X);
            int alto = Math::Abs(puntoActual.Y - puntoInicio.Y);

            if (ancho > 5 && alto > 5) {
                crearPlataforma(x, y + scrollY, ancho, alto);
                guardarPlataformas();
            }
        }
    }

    private: Void colisiones() {
        if (pictureBox1->BackgroundImage == nullptr) {
            return;
        }

        PlataformaM2^ plataformaActual = nullptr;

        for each (PlataformaM2 ^ p in plataformas) {
            System::Drawing::Rectangle plataformaMundo = p->getRect();
            System::Drawing::Rectangle jugadorRect = jugador->getRect();

            if (plataformaMundo.IntersectsWith(jugadorRect)) {
                int distanciaArriba = Math::Abs(jugadorRect.Bottom - plataformaMundo.Top);
                int distanciaAbajo = Math::Abs(jugadorRect.Top - plataformaMundo.Bottom);
                int distanciaIzquierda = Math::Abs(jugadorRect.Right - plataformaMundo.Left);
                int distanciaDerecha = Math::Abs(jugadorRect.Left - plataformaMundo.Right);

                int minDistancia = Math::Min(Math::Min(distanciaArriba, distanciaAbajo),
                    Math::Min(distanciaIzquierda, distanciaDerecha));

                if (minDistancia == distanciaArriba && jugador->getVelY() >= 0) {
                    jugador->setY(plataformaMundo.Top - jugadorRect.Height + 10);
                    jugador->setVelY(0);
                    jugador->setEnSuelo(true);
                    plataformaActual = p;
                }
                else if (minDistancia == distanciaAbajo && jugador->getVelY() < 0) {
                    jugador->setY(plataformaMundo.Bottom);
                    jugador->setVelY(0);
                }
                else if (minDistancia == distanciaIzquierda) {
                    jugador->setX(plataformaMundo.Left - jugadorRect.Width);
                }
                else if (minDistancia == distanciaDerecha) {
                    jugador->setX(plataformaMundo.Right);
                }
            }
        }

        if (plataformaActual != nullptr) {
            jugador->setX(jugador->getX() + plataformaActual->velocidad);
        }

        int altoTotal = pictureBox1->BackgroundImage->Height;
        int limiteSuelo = altoTotal - (jugador->getRect().Height);

        if (jugador->getY() >= limiteSuelo) {
            jugador->setY(limiteSuelo);
            jugador->setVelY(0);
            jugador->setEnSuelo(true);
        }
    }

    private: Void dibujarColisiones(Graphics^ g) {
        System::Drawing::Rectangle jugadorRect = jugador->getRect();
        int jugadorPantallaY = jugadorRect.Y - scrollY;
        System::Drawing::Rectangle jugadorPantalla = System::Drawing::Rectangle(
            jugadorRect.X, jugadorPantallaY, jugadorRect.Width, jugadorRect.Height
        );
        g->DrawRectangle(Pens::Lime, jugadorPantalla);

        for each (PlataformaM2 ^ p in plataformas) {
            System::Drawing::Rectangle platRect = p->getRect();
            int platY = platRect.Y - scrollY;
            g->DrawRectangle(Pens::Red, platRect.X, platY, platRect.Width, platRect.Height);
            g->DrawLine(Pens::Yellow, platRect.X, platY, platRect.Right, platY);
        }
    }

    private: Void guardarPlataformas() {
        try {
            StreamWriter^ writer = gcnew StreamWriter("plataformas2.txt");
            for each (PlataformaM2 ^ p in plataformas) {
                String^ linea = String::Format("{0},{1},{2},{3}",
                    p->x, p->y, p->ancho, p->alto);
                writer->WriteLine(linea);
            }
            writer->Close();
        }
        catch (Exception^ ex) {
            MessageBox::Show("Error al guardar: " + ex->Message);
        }
    }

    private: Void cargarPlataformas() {
        try {
            plataformas->Clear();
            if (System::IO::File::Exists("plataformas2.txt")) {
                StreamReader^ reader = gcnew StreamReader("plataformas2.txt");
                String^ linea;
                while ((linea = reader->ReadLine()) != nullptr) {
                    cli::array<String^>^ datos = linea->Split(',');
                    if (datos->Length == 4) {
                        int x = Int32::Parse(datos[0]);
                        int y = Int32::Parse(datos[1]);
                        int ancho = Int32::Parse(datos[2]);
                        int alto = Int32::Parse(datos[3]);
                        PlataformaM2^ p = gcnew PlataformaM2(x, y, ancho, alto);
                        plataformas->Add(p);
                    }
                }
                reader->Close();
            }
        }
        catch (Exception^ ex) {
            MessageBox::Show("Error al cargar: " + ex->Message);
        }
    }

    private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
        try {
            this->pictureBox1->BackgroundImage = gcnew Bitmap("Imagenes/posibleMapa2.jpg");
        }
        catch (...) {
            try {
                this->pictureBox1->BackgroundImage = gcnew Bitmap("posibleMapa2.jpg");
            }
            catch (...) {
                MessageBox::Show("Error al cargar imagen");
            }
        }
    }

    private: void eliminarUltimaPlataforma() {
        if (plataformas != nullptr && plataformas->Count > 0) {
            plataformas->RemoveAt(plataformas->Count - 1);
            if (contadorPlataformas > 0) --contadorPlataformas;
            guardarPlataformas();
        }
        else {
            MessageBox::Show("No hay plataformas para eliminar");
        }
    }

    private: void moverPlataformasHorizontalmente() {
        for each (PlataformaM2 ^ p in plataformas) {
            p->mover(this->pictureBox1->Width);
        }
    }
    };
}