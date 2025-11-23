#pragma once
#include "Controladora.h"
#include "Dialogo_IAsuprema.h"

namespace TF1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	
	public ref class MenuForm : public System::Windows::Forms::Form
	{
	public:
		MenuForm(void)
		{
			InitializeComponent();
			g = this->CreateGraphics();
			canvas = BufferedGraphicsManager::Current;
			buffer = canvas->Allocate(g, this->ClientRectangle);
			bmpMapa = gcnew Bitmap("Imagenes/Mapa1.png");
			bmpPersonajeHumano = gcnew Bitmap("Imagenes/PersonajeHuman.png");
			bmpEnemigoIA = gcnew Bitmap("Imagenes/EnemigoIA.png");
			bmpRecurso = gcnew Bitmap("Imagenes/Recurso.png");
			bmpAliado = gcnew Bitmap("Imagenes/Aliado.png");

			bmpPersonajeHumano->MakeTransparent(bmpPersonajeHumano->GetPixel(0, 0));
			control = gcnew Controladora(bmpPersonajeHumano, this->ClientRectangle.Width, this->ClientRectangle.Height);
			Jugador^ jugadorPtr = control->getJugador();


			Enemigo^ enemigo1 = gcnew Enemigo(170, 170, 0, 0);
			Enemigo^ enemigo2 = gcnew Enemigo(10, 110, 0, 0);
			Enemigo^ enemigo3 = gcnew Enemigo(470, 540, 0, 0);
			Enemigo^ enemigo4 = gcnew Enemigo(655, 20, 0, 0);
			Enemigo^ enemigo5= gcnew Enemigo(940, 390, 0, 0);


			control->agregarEnemigo(enemigo1);
			control->agregarEnemigo(enemigo2);
			control->agregarEnemigo(enemigo3);
			control->agregarEnemigo(enemigo4);
			control->agregarEnemigo(enemigo5);

			cant_recursos = 0;

			modoDebug = false;
			creandoPlataforma = false;
			plataformas = gcnew System::Collections::Generic::List<System::Drawing::Rectangle>();
			cargarPlataformas();
		}

	protected:
		~MenuForm()
		{
			if (components)
			{
				delete components;
			}
			delete control;
		}
	private: 
		System::ComponentModel::IContainer^ components;
		System::Windows::Forms::Timer^ timer1;
		Graphics^ g;
		BufferedGraphicsContext^ canvas;
		BufferedGraphics^ buffer;
		Bitmap^ bmpPersonajeHumano;
		Bitmap^ bmpEnemigoIA;
		Bitmap^ bmpRecurso;
		Bitmap^ bmpMapa; 
		Bitmap^ bmpAliado;
		int cant_recursos;

		bool modoDebug;
		bool creandoPlataforma;
		Point puntoInicio;
		Point puntoActual;
		int contadorPlataformas;
		System::Collections::Generic::List<System::Drawing::Rectangle>^ plataformas;



		Controladora^ control;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MenuForm::timer1_Tick);
			// 
			// MenuForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1084, 661);
			this->Name = L"MenuForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MenuForm";
			this->Load += gcnew System::EventHandler(this, &MenuForm::MenuForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MenuForm::MenuForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MenuForm::MenuForm_KeyUp);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MenuForm::MenuForm_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MenuForm::MenuForm_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MenuForm::MenuForm_MouseUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	
	private: 
	System::Void MenuForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		Jugador^ jugadorPtr = control->getJugador();
		switch (e->KeyCode)
		{
		case Keys::W:
			jugadorPtr->setDireccion(Arriba);
			break;
		case Keys::A:
			jugadorPtr->setDireccion(Izquierda);
			break;
		case Keys::S:
			jugadorPtr->setDireccion(Abajo);
			break;
		case Keys::D:
			jugadorPtr->setDireccion(Derecha);
			break;
		case Keys::E:
			control->dialogoConIA();
			control->interactuarAliado();
			break;
		case Keys::C:
			control->barra_confianza();
			break;
		case Keys::F1:  // Activar/desactivar modo debug
			modoDebug = !modoDebug;
			MessageBox::Show(modoDebug ? "Modo Dios Activado" : "Modo Dios Desactivado");
			break;
		case Keys::F2:  // Guardar plataformas
			guardarPlataformas();
			MessageBox::Show("Plataformas guardadas!");
			break;
		case Keys::F3:  // Recargar plataformas
			cargarPlataformas();
			MessageBox::Show("Plataformas recargadas!");
			break;
		case Keys::F4: // Limpiar plataformas
			limpiarPlataformas();
			guardarPlataformas();
			MessageBox::Show("Plataformas eliminadas!");
			break;
		}
	}
	System::Void MenuForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		control->getJugador()->setDireccion(Ninguna);
	}

	System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		// lógica del juego
		Graphics^ gBuffer = buffer->Graphics;
		gBuffer->Clear(Color::White);

		Jugador^ jugador = control->getJugador();
		int tamañoAncho = this->ClientSize.Width;
		int tamañoAlto = this->ClientSize.Height;


		int mapaAncho = 143 * 20; 
		int mapaAlto = 84 * 20; 

		int CentrarJX = jugador->getX() + jugador->getAncho() / 2;
		int CentrarJY = jugador->getY() + jugador->getAlto() / 2;
		int camX = tamañoAncho / 2 - CentrarJX;
		int camY = tamañoAlto / 2 - CentrarJY;

		//CAMARA
		if (mapaAncho <= tamañoAncho) {
			camX = (tamañoAncho - mapaAncho) / 2;
		}
		else {
			int minCamX = tamañoAncho - mapaAncho;
			if (camX > 0) camX = 0;
			if (camX < minCamX) camX = minCamX;
		}

		if (mapaAlto <= tamañoAlto) {
			camY = (tamañoAlto - mapaAlto) / 2;
		}
		else {
			int minCamY = tamañoAlto - mapaAlto;
			if (camY > 0) camY = 0;
			if (camY < minCamY) camY = minCamY;
		}

		System::Drawing::Drawing2D::GraphicsState^ estadoOriginal = gBuffer->Save();
		

		gBuffer->TranslateTransform((float)camX, (float)camY);

		gBuffer->DrawImage(bmpMapa, 0, 0, mapaAncho, mapaAlto);


		verificarColisionesPlataformas();
		control->moverJugador(gBuffer, bmpPersonajeHumano);

		if (cant_recursos < 4) {
			control->crearRecursos(bmpRecurso);
		}
		control->dibujarAliado(gBuffer, bmpAliado);
		control->moverEnemigos(gBuffer, bmpEnemigoIA);
		control->moverRecursos(gBuffer, bmpRecurso);
		control->dibujarEntidades(gBuffer, bmpPersonajeHumano, bmpEnemigoIA, bmpRecurso);

		dibujarPlataformas(gBuffer);

		if (modoDebug) {
			dibujarDebug(gBuffer);
		}

		if (creandoPlataforma) {
			int x = Math::Min(puntoInicio.X, puntoActual.X);
			int y = Math::Min(puntoInicio.Y, puntoActual.Y);
			int ancho = Math::Abs(puntoActual.X - puntoInicio.X);
			int alto = Math::Abs(puntoActual.Y - puntoInicio.Y);

			gBuffer->FillRectangle(
				gcnew SolidBrush(Color::FromArgb(50, 255, 255, 255)),
				x, y, ancho, alto
			);
			gBuffer->DrawRectangle(Pens::White, x, y, ancho, alto);
			
		}



		gBuffer->Restore(estadoOriginal);
		buffer->Render(g);
		cant_recursos++;
	}

	private: System::Void MenuForm_Load(System::Object^ sender, System::EventArgs^ e) {
		this->timer1->Enabled = false;
		Dialogo_IAsuprema^ dialogoIA = gcnew Dialogo_IAsuprema();
		dialogoIA->ShowDialog();
		this->timer1->Enabled = true;
	}

	
	private: System::Void MenuForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Right) {
			creandoPlataforma = true;
			Jugador^ jugador = control->getJugador();
			int tamañoAncho = this->ClientSize.Width;
			int tamañoAlto = this->ClientSize.Height;
			int mapaAncho = 143 * 20;
			int mapaAlto = 84 * 20;

			int CentrarJX = jugador->getX() + jugador->getAncho() / 2;
			int CentrarJY = jugador->getY() + jugador->getAlto() / 2;
			int camX = tamañoAncho / 2 - CentrarJX;
			int camY = tamañoAlto / 2 - CentrarJY;

			// Aplicar límites de cámara
			if (mapaAncho <= tamañoAncho) {
				camX = (tamañoAncho - mapaAncho) / 2;
			}
			else {
				int minCamX = tamañoAncho - mapaAncho;
				if (camX > 0) camX = 0;
				if (camX < minCamX) camX = minCamX;
			}

			if (mapaAlto <= tamañoAlto) {
				camY = (tamañoAlto - mapaAlto) / 2;
			}
			else {
				int minCamY = tamañoAlto - mapaAlto;
				if (camY > 0) camY = 0;
				if (camY < minCamY) camY = minCamY;
			}

			// Convertir coordenadas de pantalla a coordenadas del mundo
			puntoInicio = Point(e->Location.X - camX, e->Location.Y - camY);
			puntoActual = puntoInicio;
		}
	}

	private: System::Void MenuForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (creandoPlataforma) {

			Jugador^ jugador = control->getJugador();
			int tamañoAncho = this->ClientSize.Width;
			int tamañoAlto = this->ClientSize.Height;
			int mapaAncho = 143 * 20;
			int mapaAlto = 84 * 20;

			int CentrarJX = jugador->getX() + jugador->getAncho() / 2;
			int CentrarJY = jugador->getY() + jugador->getAlto() / 2;
			int camX = tamañoAncho / 2 - CentrarJX;
			int camY = tamañoAlto / 2 - CentrarJY;

			if (mapaAncho <= tamañoAncho) {
				camX = (tamañoAncho - mapaAncho) / 2;
			}
			else {
				int minCamX = tamañoAncho - mapaAncho;
				if (camX > 0) camX = 0;
				if (camX < minCamX) camX = minCamX;
			}

			if (mapaAlto <= tamañoAlto) {
				camY = (tamañoAlto - mapaAlto) / 2;
			}
			else {
				int minCamY = tamañoAlto - mapaAlto;
				if (camY > 0) camY = 0;
				if (camY < minCamY) camY = minCamY;
			}

			// Convertir coordenadas de pantalla a coordenadas del mundo
			puntoActual = Point(e->Location.X - camX, e->Location.Y - camY);
		}
	}
	private: System::Void MenuForm_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (creandoPlataforma && e->Button == System::Windows::Forms::MouseButtons::Right) {
			creandoPlataforma = false;

			int x = Math::Min(puntoInicio.X, puntoActual.X);
			int y = Math::Min(puntoInicio.Y, puntoActual.Y);
			int ancho = Math::Abs(puntoActual.X - puntoInicio.X);
			int alto = Math::Abs(puntoActual.Y - puntoInicio.Y);

			if (ancho > 5 && alto > 5) {
				System::Drawing::Rectangle nuevaPlataforma = System::Drawing::Rectangle(x, y, ancho, alto);
				plataformas->Add(nuevaPlataforma);
				guardarPlataformas();
			}
		}

	}


	private: void verificarColisionesPlataformas() {
		Jugador^ jugador = control->getJugador();
		System::Drawing::Rectangle jugadorRect = jugador->getRect();

		for each (System::Drawing::Rectangle plataforma in plataformas) {
			if (plataforma.IntersectsWith(jugadorRect)) {

				// Calcular distancias desde cada lado
				int distanciaArriba = Math::Abs(jugadorRect.Bottom - plataforma.Top);
				int distanciaAbajo = Math::Abs(jugadorRect.Top - plataforma.Bottom);
				int distanciaIzquierda = Math::Abs(jugadorRect.Right - plataforma.Left);
				int distanciaDerecha = Math::Abs(jugadorRect.Left - plataforma.Right);

				// Encontrar la distancia mínima
				int minDistancia = Math::Min(Math::Min(distanciaArriba, distanciaAbajo),
					Math::Min(distanciaIzquierda, distanciaDerecha));

				// Colisión desde arriba
				if (minDistancia == distanciaArriba) {
					jugador->SetY(plataforma.Top - jugadorRect.Height );
					jugador->SetDy(0);
				}
				// Colisión desde abajo
				else if (minDistancia == distanciaAbajo) {
					jugador->SetY(plataforma.Bottom);
					jugador->SetDy(0);
				}
				// Colisión desde la izquierda
				else if (minDistancia == distanciaIzquierda) {
					jugador->SetX(plataforma.Left - jugadorRect.Width );
					jugador->SetDx(0);
				}
				// Colisión desde la derecha
				else if (minDistancia == distanciaDerecha) {
					jugador->SetX(plataforma.Right);
					jugador->SetDx(0);
				}
			}
		}
	}

	// estas dos funcionas las hizo copilot, combine lo de poma aqui tmb ------------------
	private: void dibujarPlataformas(Graphics^ g) {
		if (!modoDebug) return;

		for each (System::Drawing::Rectangle plat in plataformas) {
			SolidBrush^ brushFill = gcnew SolidBrush(Color::FromArgb(50, 255, 255, 255));
			g->FillRectangle(brushFill, plat);
			g->DrawRectangle(Pens::White, plat);
			delete brushFill;
		}
	}
	private: void dibujarDebug(Graphics^ g) {
		Jugador^ jugador = control->getJugador();
		System::Drawing::Rectangle jugadorRect = jugador->getRect();
		for each (System::Drawing::Rectangle plat in plataformas) {
			g->DrawRectangle(Pens::White, plat);
		}

	}
	//------------------------------------------------------------------------------------

		   //tal cual hermano
	private: void guardarPlataformas() {

		StreamWriter^ writer = gcnew StreamWriter("plataformas.txt");

		for each (System::Drawing::Rectangle plat in plataformas) {
			String^ linea = String::Format("{0},{1},{2},{3}",
				plat.X, plat.Y, plat.Width, plat.Height);
			writer->WriteLine(linea);
		}

		writer->Close();
	}

    private: void cargarPlataformas() {
		
		if (plataformas == nullptr) {
			plataformas = gcnew System::Collections::Generic::List<System::Drawing::Rectangle>();
		}
		plataformas->Clear();

		if (System::IO::File::Exists("plataformas.txt")) {
			StreamReader^ reader = gcnew StreamReader("plataformas.txt");
			String^ linea;

			while ((linea = reader->ReadLine()) != nullptr) {
				cli::array<String^>^ datos = linea->Split(',');

				if (datos != nullptr && datos->Length == 4) {
					int x = Int32::Parse(datos[0]);
					int y = Int32::Parse(datos[1]);
					int ancho = Int32::Parse(datos[2]);
					int alto = Int32::Parse(datos[3]);

					System::Drawing::Rectangle plataforma = System::Drawing::Rectangle(x, y, ancho, alto);
				plataformas->Add(plataforma);
				}
			}
			reader->Close();
		}
    }

	private: void limpiarPlataformas() {
		if (plataformas != nullptr) {
			plataformas->Clear();
		}
		guardarPlataformas();
	}
private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
}
};
}
