#pragma once
#include "Controladora.h"
#include "Dialogo_IAsuprema.h"
#include "Camara.h"
#include "FormJuego2.h"
	
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
			camara = gcnew Camara();
			control = gcnew Controladora(bmpPersonajeHumano, camara, this->ClientRectangle.Width, this->ClientRectangle.Height);
			jugadorPtr = control->getJugador();


			Enemigo^ enemigo1 = gcnew Enemigo(1760, 100, 0, 0);
			Enemigo^ enemigo2 = gcnew Enemigo(1300, 1510, 0, 0);
			Enemigo^ enemigo3 = gcnew Enemigo(500, 540, 0, 0);
			Enemigo^ enemigo4 = gcnew Enemigo(2550, 1150, 0, 0);
			Enemigo^ enemigo5 = gcnew Enemigo(490, 1330, 0, 0);
			control->agregarEnemigo(enemigo1);
			control->agregarEnemigo(enemigo2);
			control->agregarEnemigo(enemigo3);
			control->agregarEnemigo(enemigo4);
			control->agregarEnemigo(enemigo5);

			cant_recursos = 0;
			contadorPlataformas = 0;
			modoDebug = false;
			creandoPlataforma = false;

			// IMPORTANTE: Inicializar la lista ANTES de cargar
			plataformas = gcnew System::Collections::Generic::List<System::Drawing::Rectangle>();
			cargarPlataformas(); // Esto carga y crea los PictureBox

			gameover = gcnew Game_Over();
			    mostrarDialogoInicial = true;

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
		Camara^ camara;
		
		List<Enemigo^>^ enemigos;

		Jugador^ jugadorPtr;
		int cant_recursos;

		bool modoDebug;
		bool creandoPlataforma;
		Point puntoInicio;
		Point puntoActual;
		int contadorPlataformas;
		System::Collections::Generic::List<System::Drawing::Rectangle>^ plataformas;

		Controladora^ control;
		Game_Over^ gameover;
		int contador = 0;
		bool mostrarDialogoInicial;

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
			this->Text = L"Mundo 1";
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
			case Keys::F1:
				modoDebug = !modoDebug;
				toggleVisibilidadPlataformas(modoDebug);
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

		System::Void MenuForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			control->getJugador()->setDireccion(Ninguna);
		}

		System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
			if (mostrarDialogoInicial) {
				this->timer1->Enabled = false;
				Dialogo_IAsuprema^ dialogoIA = gcnew Dialogo_IAsuprema();
				dialogoIA->ShowDialog();
				this->timer1->Enabled = true;
				mostrarDialogoInicial = false; // ⭐ Marcar como mostrado
			}
			Graphics^ gBuffer = buffer->Graphics;

			// CÁMARA
			camara->actualizarCamaraYDibujar(jugadorPtr, this->ClientSize.Width, this->ClientSize.Height, bmpMapa->Width, bmpMapa->Height, gBuffer, bmpMapa);
			moverPicturesBoxes(camara->getScrollY(), camara->getScrollX());

			// COLISIONES CON PLATAFORMAS
			verificarColisionesPlataformas();

			control->moverJugador(gBuffer, bmpPersonajeHumano);
			if (cant_recursos < 4) {
				control->crearRecursos(bmpRecurso);
			}
			control->dibujarAliado(gBuffer, bmpAliado);
			control->moverEnemigos(gBuffer, bmpEnemigoIA);
			control->moverRecursos(gBuffer, bmpRecurso);
			control->dibujarEntidades(gBuffer, bmpPersonajeHumano, bmpEnemigoIA, bmpRecurso);

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
			buffer->Render(g);
			cant_recursos++;
			contador++;
			
			if (jugadorPtr->getConfianza() > 100 && control->contestadaLaIA() ) //AQUI EL VALOR SE TIENE QUE CAMBIAR DESPUES
			{
					
				this->timer1->Enabled = false;
				this->Close();
				MyForm^ Mapa2 = gcnew MyForm();
				Mapa2->Show();
			}
			else if (jugadorPtr->getConfianza() < 70 && control->contestadaLaIA()) {

				this->timer1->Enabled = false;
				gameover->ShowDialog();
				if ( gameover->GetCondicion()) {
					MenuForm^ nuevo = gcnew MenuForm();
					this->Close();
					nuevo->Show();
				}
				else {
					this->Close();
				}
			}
		}
	
	private: System::Void MenuForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void MenuForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Right) {
			creandoPlataforma = true;
			puntoInicio = e->Location;
			puntoActual = e->Location;
		}
	}

	private: System::Void MenuForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (creandoPlataforma) {
			puntoActual = e->Location;
		}
	}

	private: System::Void MenuForm_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (creandoPlataforma && e->Button == System::Windows::Forms::MouseButtons::Right) {
			creandoPlataforma = false;

			// Convertir coordenadas de pantalla a coordenadas del mundo
			int x = Math::Min(puntoInicio.X, puntoActual.X) + camara->getScrollX();
			int y = Math::Min(puntoInicio.Y, puntoActual.Y) + camara->getScrollY();
			int ancho = Math::Abs(puntoActual.X - puntoInicio.X);
			int alto = Math::Abs(puntoActual.Y - puntoInicio.Y);

			// Crear solo si tiene tamaño
			if (ancho > 5 && alto > 5) {
				// Agregar el rectángulo en COORDENADAS DEL MUNDO
				System::Drawing::Rectangle plataforma = System::Drawing::Rectangle(x, y, ancho, alto);
				plataformas->Add(plataforma);

				// Crear el PictureBox visual (en coordenadas de pantalla)
				crearPictureBoxPlataforma(x, y, ancho, alto);

				// Guardar inmediatamente
				guardarPlataformas();
			}
		}
	}

		   // COLISIÓN ARREGLADA: Usa la List<Rectangle> en coordenadas del mundo
	private: void verificarColisionesPlataformas() {
		System::Drawing::Rectangle jugadorRect = jugadorPtr->getRect();

		// Iterar sobre la lista de Rectangles (coordenadas del mundo)
		for each (System::Drawing::Rectangle plat in plataformas) {
			// Verificar intersección
			if (!jugadorRect.IntersectsWith(plat))
				continue;

			// Calcular penetraciones
			int overlapLeft = jugadorRect.Right - plat.Left;
			int overlapRight = plat.Right - jugadorRect.Left;
			int overlapTop = jugadorRect.Bottom - plat.Top;
			int overlapBottom = plat.Bottom - jugadorRect.Top;

			int penX = Math::Min(Math::Abs(overlapLeft), Math::Abs(overlapRight));
			int penY = Math::Min(Math::Abs(overlapTop), Math::Abs(overlapBottom));

			// Resolver colisión
			if (penX < penY) {
				// Colisión horizontal
				if (Math::Abs(overlapLeft) < Math::Abs(overlapRight)) {
					jugadorPtr->SetX(jugadorPtr->getX() - overlapLeft);
				}
				else {
					jugadorPtr->SetX(jugadorPtr->getX() + overlapRight);
				}
				jugadorPtr->SetDx(0);
			}
			else {
				// Colisión vertical
				if (Math::Abs(overlapTop) < Math::Abs(overlapBottom)) {
					jugadorPtr->SetY(jugadorPtr->getY() - overlapTop);
				}
				else {
					jugadorPtr->SetY(jugadorPtr->getY() + overlapBottom);
				}
				jugadorPtr->SetDy(0);
			}

			jugadorRect = jugadorPtr->getRect();
		}
	}

	private: void dibujarDebug(Graphics^ g) {
		// Dibujar las plataformas en COORDENADAS DE PANTALLA
		for each (System::Drawing::Rectangle plat in plataformas) {
			int pantallaX = plat.X - camara->getScrollX();
			int pantallaY = plat.Y - camara->getScrollY();

			System::Drawing::Rectangle platPantalla = System::Drawing::Rectangle(
				pantallaX, pantallaY, plat.Width, plat.Height
			);

			g->FillRectangle(gcnew SolidBrush(Color::FromArgb(100, 255, 0, 0)), platPantalla);
			g->DrawRectangle(Pens::Red, platPantalla);
		}
	}
	
		   // GUARDAR: Guarda los Rectangles (coordenadas del mundo)
	private: void guardarPlataformas() {
		StreamWriter^ writer = gcnew StreamWriter("plataformas.txt");

		for each (System::Drawing::Rectangle plat in plataformas) {
			String^ linea = String::Format("{0},{1},{2},{3}",
				plat.X, plat.Y, plat.Width, plat.Height);
			writer->WriteLine(linea);
		}

		writer->Close();
	}

		   // CARGAR: Lee el archivo y recrea TODO
	private: void cargarPlataformas() {
		// Limpiar todo primero

		if (plataformas == nullptr) {
			plataformas = gcnew System::Collections::Generic::List<System::Drawing::Rectangle>();
		}
		plataformas->Clear();
		contadorPlataformas = 0;

		// Leer archivo si existe
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

					// Agregar a la lista (coordenadas del mundo)
					System::Drawing::Rectangle plataforma = System::Drawing::Rectangle(x, y, ancho, alto);
					plataformas->Add(plataforma);

					// Crear el PictureBox visual
					crearPictureBoxPlataforma(x, y, ancho, alto);
				}
			}
			reader->Close();
		}
	}



		   // Crea un PictureBox para visualización (recibe coordenadas del mundo)
	private: void crearPictureBoxPlataforma(int xMundo, int yMundo, int ancho, int alto) {
		PictureBox^ nuevaPlataforma = gcnew PictureBox();

		// Convertir a coordenadas de pantalla para posicionamiento inicial
		int xPantalla = xMundo - camara->getScrollX();
		int yPantalla = yMundo - camara->getScrollY();

		nuevaPlataforma->Location = Point(xPantalla, yPantalla);
		nuevaPlataforma->Size = System::Drawing::Size(ancho, alto);
		nuevaPlataforma->BackColor = Color::Transparent;
		nuevaPlataforma->Tag = "plataforma";
		nuevaPlataforma->Name = "plataforma" + contadorPlataformas++;
		nuevaPlataforma->Visible = modoDebug;

		// Guardar coordenadas originales del mundo en el Tag
		cli::array<int>^ coordsMundo = gcnew cli::array<int>(2) { xMundo, yMundo };
		nuevaPlataforma->Tag = "plataforma"; // Mantener el tag como string

		this->Controls->Add(nuevaPlataforma);
		nuevaPlataforma->BringToFront();
	}

	private: void toggleVisibilidadPlataformas(bool visible) {
		for each (Control ^ x in this->Controls) {
			if (x->Tag != nullptr && x->Tag->ToString() == "plataforma") {
				x->Visible = visible;
			}
		}
	}

		   // Mueve los PictureBox según el scroll de la cámara
	private: void moverPicturesBoxes(int scrollY, int scrollX) {
		static int lastScrollX = 0;
		static int lastScrollY = 0;

		int deltaX = scrollX - lastScrollX;
		int deltaY = scrollY - lastScrollY;

		for each (Control ^ c in this->Controls) {
			if (c->Tag == nullptr) continue;
			if (c->Tag->ToString() != "plataforma") continue;

			// Mover al revés del scroll
			c->Left -= deltaX;
			c->Top -= deltaY;
		}

		lastScrollX = scrollX;
		lastScrollY = scrollY;
	}
	private: void eliminarUltimaPlataforma() {
			// Quitar el último rectángulo del mundo si existe
			if (plataformas != nullptr && plataformas->Count > 0) {
				plataformas->RemoveAt(plataformas->Count - 1);
			}

			// Buscar el último control con Tag == "plataforma"
			Control^ ultimo = nullptr;
			for (int i = this->Controls->Count - 1; i >= 0; --i) {
				Control^ c = this->Controls[i];
				if (c->Tag != nullptr && c->Tag->ToString() == "plataforma") {
					ultimo = c;
					break;
				}
			}

			if (ultimo != nullptr) {
				this->Controls->Remove(ultimo);
				delete ultimo;
				if (contadorPlataformas > 0) --contadorPlataformas;
				guardarPlataformas();
			}
			else {
				MessageBox::Show("No hay plataformas para eliminar");
			}
		}



	};
}