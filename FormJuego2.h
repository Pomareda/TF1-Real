#pragma once
#include "JugadorIA.h"

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
            scrollY = 0;
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


        int scrollY;
        bool modoDebug = false;
        bool creandoPlataforma = false;
        Point puntoInicio;
        Point puntoActual;
        int contadorPlataformas = 0;

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
            this->pictureBox1->Size = System::Drawing::Size(1084, 662);
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
            this->ClientSize = System::Drawing::Size(1084, 661);
            this->Controls->Add(this->pictureBox1);
            this->DoubleBuffered = true;
            this->MaximizeBox = false;
            this->Name = L"MyForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Mundo 2";
            this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
            this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
            this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
            this->ResumeLayout(false);

        }
#pragma endregion

    private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {

        // VALIDACIÓN CRÍTICA
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

        int posicionJugador = jugador->getY();
        scrollY = posicionJugador - pictureBox1->Height / 2;

        int maxScroll = pictureBox1->BackgroundImage->Height - pictureBox1->Height;
        if (scrollY > maxScroll) scrollY = maxScroll;
        if (scrollY < 0) scrollY = 0;

        int deltaScroll = scrollY - scrollYAnterior;
        if (deltaScroll != 0) {
            moverElementos(deltaScroll);
        }

        System::Drawing::Rectangle porcionImagen = System::Drawing::Rectangle(
            0, scrollY, pictureBox1->Width, pictureBox1->Height
        );

        System::Drawing::Rectangle destinoPantalla = System::Drawing::Rectangle(
            0, 0, pictureBox1->Width, pictureBox1->Height
        );

        Canvas->Graphics->DrawImage(
            pictureBox1->BackgroundImage,
            destinoPantalla,
            porcionImagen,
            GraphicsUnit::Pixel
        );

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
        case Keys::Space:
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
            toggleVisibilidadPlataformas(modoDebug);
            break;
        case Keys::F5:
            guardarPlataformas();
            MessageBox::Show("Plataformas guardadas!");
            break;
        case Keys::F9:
            limpiarPlataformas();
            cargarPlataformas();
            MessageBox::Show("Plataformas cargadas!");
            break;
        }
    }

    private: System::Void MyForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
        switch (e->KeyCode)
        {
        case Keys::Space:
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
        PictureBox^ nuevaPlataforma = gcnew PictureBox();
        nuevaPlataforma->Location = Point(x, y);
        nuevaPlataforma->Size = System::Drawing::Size(ancho, alto);
        nuevaPlataforma->BackColor = Color::Transparent;
        nuevaPlataforma->Tag = "plataforma";
        nuevaPlataforma->Name = "plataforma" + contadorPlataformas++;
        this->Controls->Add(nuevaPlataforma);
        nuevaPlataforma->BringToFront();
    }

    private: System::Void MyForm_MouseUp(System::Object^ sender, MouseEventArgs^ e) {
        if (creandoPlataforma && e->Button == System::Windows::Forms::MouseButtons::Right) {
            creandoPlataforma = false;

            int x = Math::Min(puntoInicio.X, puntoActual.X);
            int y = Math::Min(puntoInicio.Y, puntoActual.Y);
            int ancho = Math::Abs(puntoActual.X - puntoInicio.X);
            int alto = Math::Abs(puntoActual.Y - puntoInicio.Y);

            if (ancho > 5 && alto > 5) {
                crearPlataforma(x, y, ancho, alto);
                guardarPlataformas();
            }
        }
    }

    private: Void colisiones() {
        if (pictureBox1->BackgroundImage == nullptr) {
            return;
        }

        jugador->setEnSuelo(false);

        for each (Control ^ x in this->Controls) {
            if (x->Tag != nullptr && x->Tag->ToString() == "plataforma") {
                int plataformaYMundo = x->Top + scrollY;

                System::Drawing::Rectangle plataformaMundo = System::Drawing::Rectangle(
                    x->Left, plataformaYMundo, x->Width, x->Height
                );

                System::Drawing::Rectangle jugadorRect = jugador->getRect();

                if (plataformaMundo.IntersectsWith(jugadorRect)) {
                    int distanciaArriba = Math::Abs(jugadorRect.Bottom - plataformaMundo.Top);
                    int distanciaAbajo = Math::Abs(jugadorRect.Top - plataformaMundo.Bottom);
                    int distanciaIzquierda = Math::Abs(jugadorRect.Right - plataformaMundo.Left);
                    int distanciaDerecha = Math::Abs(jugadorRect.Left - plataformaMundo.Right);

                    int minDistancia = Math::Min(Math::Min(distanciaArriba, distanciaAbajo),
                        Math::Min(distanciaIzquierda, distanciaDerecha));

                    if (minDistancia == distanciaArriba && jugador->getVelY() >= 0) {
                        jugador->setY(plataformaMundo.Top - jugadorRect.Height);
                        jugador->setVelY(0);
                        jugador->setEnSuelo(true);
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
        }

        int altoTotal = pictureBox1->BackgroundImage->Height;
        int limiteSuelo = altoTotal - (jugador->getRect().Height);

        if (jugador->getY() >= limiteSuelo) {
            jugador->setY(limiteSuelo);
            jugador->setVelY(0);
            jugador->setEnSuelo(true);
        }
    }

    private: Void moverElementos(int deltaScroll) {
        for each (Control ^ x in this->Controls) {
            if (x->Tag != nullptr && x->Tag->ToString() == "plataforma") {
                x->Top -= deltaScroll;
            }
        }
    }

    private: Void dibujarColisiones(Graphics^ g) {
        System::Drawing::Rectangle jugadorRect = jugador->getRect();
        int jugadorPantallaY = jugadorRect.Y - scrollY;
        System::Drawing::Rectangle jugadorPantalla = System::Drawing::Rectangle(
            jugadorRect.X, jugadorPantallaY, jugadorRect.Width, jugadorRect.Height
        );
        g->DrawRectangle(Pens::Lime, jugadorPantalla);

        for each (Control ^ x in this->Controls) {
            if (x->Tag != nullptr && x->Tag->ToString() == "plataforma") {
                g->DrawRectangle(Pens::Red, x->Bounds);
                g->DrawLine(Pens::Yellow, x->Left, x->Top, x->Right, x->Top);
            }
        }
    }

    private: Void guardarPlataformas() {
        try {
            StreamWriter^ writer = gcnew StreamWriter("plataformas2.txt");

            for each (Control ^ x in this->Controls) {
                if (x->Tag != nullptr && x->Tag->ToString() == "plataforma") {
                    int yMundo = x->Top + scrollY;
                    String^ linea = String::Format("{0},{1},{2},{3}",
                        x->Left, yMundo, x->Width, x->Height);
                    writer->WriteLine(linea);
                }
            }

            writer->Close();
        }
        catch (Exception^ ex) {
            MessageBox::Show("Error al guardar: " + ex->Message);
        }
    }

    private: Void cargarPlataformas() {
        try {
            if (System::IO::File::Exists("plataformas2.txt")) {
                StreamReader^ reader = gcnew StreamReader("plataformas2.txt");
                String^ linea;

                while ((linea = reader->ReadLine()) != nullptr) {
                    cli::array<String^>^ datos = linea->Split(',');

                    if (datos->Length == 4) {
                        int x = Int32::Parse(datos[0]);
                        int yMundo = Int32::Parse(datos[1]);
                        int ancho = Int32::Parse(datos[2]);
                        int alto = Int32::Parse(datos[3]);

                        int yPantalla = yMundo - scrollY;

                        crearPlataforma(x, yPantalla, ancho, alto);
                    }
                }

                reader->Close();
            }
        }
        catch (Exception^ ex) {
            MessageBox::Show("Error al cargar: " + ex->Message);
        }
    }

    private: Void limpiarPlataformas() {
        System::Collections::Generic::List<Control^>^ aEliminar =
            gcnew System::Collections::Generic::List<Control^>();

        for each (Control ^ x in this->Controls) {
            if (x->Tag != nullptr && x->Tag->ToString() == "plataforma") {
                aEliminar->Add(x);
            }
        }

        for each (Control ^ x in aEliminar) {
            this->Controls->Remove(x);
            delete x;
        }
    }

    private: Void toggleVisibilidadPlataformas(bool visible) {
        for each (Control ^ x in this->Controls) {
            if (x->Tag != nullptr && x->Tag->ToString() == "plataforma") {
                x->Visible = visible;
            }
        }
    }
    private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
        try {
            this->pictureBox1->BackgroundImage = gcnew Bitmap("Imagenes/jumpkingmap.jpg");
        }
        catch (...) {
            // Si falla, intenta con otra ruta
            try {
                this->pictureBox1->BackgroundImage = gcnew Bitmap("jumpkingmap.jpg");
            }
            catch (...) {
                MessageBox::Show("Error al cargar imagen: ");
            }
        }
    }
};
}