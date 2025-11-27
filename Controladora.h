#pragma once
#include "Barra_Confianza.h"
#include "Enemigo.h"
#include "Jugador.h"
#include "Recurso.h"
#include <vector>
#include "Dialogo.h"
#include "Aliado.h"
#include "Camara.h"
#include "FormAliado.h"
#include "Dialogo_IAsuprema.h"
#include "Game_Over.h"
#include "Minimapa.h"
using namespace System::Collections::Generic;
using namespace TF1;

ref class Controladora {
private:
	Jugador^ jugador;
	Camara^ camara;
	List<Enemigo^>^ enemigos;
	List<Recurso^>^ recursos;
	Aliado^ aliado;
	int contador = 0;
	Minimapa^ minimapa;
	List<int>^ preguntas;
	int nivel_perdido;
	//Camara^ camara;
public:
	Controladora(Bitmap^ bmp, Camara^ cam, int anchoVentana, int altoVentana);
	~Controladora();

	void agregarEnemigo(Enemigo^ enemigo);
	void agregarRecurso(Recurso^ recursito);
	void moverEnemigos(Graphics^ g, Bitmap^ bmp);
	void moverJugador(Graphics^ g, Bitmap^ bmp, int an, int al);
	void moverRecursos(Graphics^ g, Bitmap^ bmp);
	void dibujarEntidades(Graphics^ g, Bitmap^ bmp, Bitmap^ bmpEnemigo, Bitmap^ bmpRecurso);
	void dialogoConIA();
	bool contestadaLaIA();
	void dibujarAliado(Graphics^ g, Bitmap^ bmp);
	void interactuarAliado();
	bool colisionAliado();
	bool colisionEnemigo(Graphics^ g);
	bool colisionRecurso(Graphics^ g);
	void barra_confianza();

	int getContestadaLaIA();
	int getTotalIAs();

	Minimapa^ getMinimap() { return minimapa; }
	Jugador^ getJugador() { return jugador; }
};

inline Controladora::Controladora(Bitmap^ bmp, Camara^ cam, int anchoVentana, int altoVentana) {
	jugador = gcnew Jugador(1310, 350, bmp->Width / 6, bmp->Height / 6);
	enemigos = gcnew List<Enemigo^>();
	recursos = gcnew List<Recurso^>();
	aliado = gcnew Aliado(760, 1600);
	preguntas = gcnew List<int>(); 
	camara = cam;
	minimapa = gcnew Minimapa(0, 0);
}


inline Controladora::~Controladora() {}

inline void Controladora::agregarEnemigo(Enemigo^ enemigo) {
	enemigos->Add(enemigo);
}

inline void Controladora::agregarRecurso(Recurso^ recursito)
{
	recursos->Add(recursito);
}

inline void Controladora::moverEnemigos(Graphics^ g, Bitmap^ bmp) {
	for each (Enemigo ^ enemigo in enemigos) {
		enemigo->mover();
	}
}

inline void Controladora::moverJugador(Graphics^ g, Bitmap^ bmp, int an, int al) {
	int posicionAnteriorX = jugador->getX();
	int posicionAnteriorY = jugador->getY();

	jugador->mover(g, an, al);

	if (colisionEnemigo(g) || colisionAliado()) {
		jugador->SetX(posicionAnteriorX);
		jugador->SetY(posicionAnteriorY);
		return;
	}

	if (colisionRecurso(g)) {
		//pomactm
	}
}

inline void Controladora::moverRecursos(Graphics^ g, Bitmap^ bmp)
{
	for each (Recurso ^ r in recursos) {
		r->moverRecurso();
	}
}

inline void Controladora::dibujarEntidades(Graphics^ g, Bitmap^ bmp, Bitmap^ bmpEnemigo, Bitmap^ bmpRecurso) {
	for each (Recurso ^ r in recursos) {
		r->dibujar(g, bmpRecurso, camara->getScrollX(), camara->getScrollY());
	}
	for each (Enemigo ^ enemigo in enemigos) {
		enemigo->dibujar(g, bmpEnemigo, camara->getScrollX(), camara->getScrollY());
	}
	jugador->dibujar(g, bmp, camara->getScrollY(), camara->getScrollX());

}

inline void Controladora::dibujarAliado(Graphics^ g, Bitmap^ bmp) {
	aliado->dibujar(g, bmp, camara->getScrollX(), camara->getScrollY());
}

inline bool Controladora::colisionEnemigo(Graphics^ g) {
	for (int i = 0; i < enemigos->Count; i++)
	{
		if (jugador->getRect().IntersectsWith(enemigos[i]->getRect())) {
			return true;
		}
	}
	return false;
}

inline bool Controladora::colisionRecurso(Graphics^ g)
{
	for (int i = 0; i < recursos->Count; i++)
	{
		if (jugador->getRect().IntersectsWith(recursos[i]->getRect())) {
			jugador->setConfianza(jugador->getConfianza() + 30);
			recursos[i]->setActivo(false);
			recursos->RemoveAt(i);
		}

	}

	return false;
}

inline bool Controladora::colisionAliado() {
	if (jugador->getRect().IntersectsWith(aliado->getRect())) {
		return true;
	}
	else return false;
}

inline void Controladora::barra_confianza() {
	Barra_Confianza^ barra = gcnew	Barra_Confianza(jugador, minimapa, 2787, 1680);
	barra->ShowDialog();
}

inline void Controladora::interactuarAliado() {
	static int unavez = 0;
	int distanciaX = jugador->getX() - aliado->getRect().X;
	int distanciaY = jugador->getY() - aliado->getRect().Y;

	if ((distanciaX < 100 && distanciaX > -100) && (distanciaY < 90 && distanciaY > -120) && unavez == 0) {
		FormAliado^ FormA = gcnew FormAliado(jugador);
		FormA->ShowDialog();
		unavez = 1;
	}
}

inline void Controladora::dialogoConIA()
{
	for (int i = 0; i < enemigos->Count; i++)
	{
		if (enemigos[i]->verPregunta()) {
			continue;
		}

		int distanciaX = jugador->getX() - enemigos[i]->getRect().X;
		int distanciaY = jugador->getY() - enemigos[i]->getRect().Y;




		if ((distanciaX < 100 && distanciaX > -100) && (distanciaY < 90 && distanciaY > -120)) {
			Random ^r = gcnew Random();
			int a = r->Next(5);
		
			if (contador == 0) {
				preguntas->Add(a);
				Dialogo^ dialogoForm = gcnew Dialogo(jugador, a);
				dialogoForm->ShowDialog();
				enemigos[i]->preguntaContestada();
				contador++;
			}
			else {
				while (preguntas->Contains(a)) {
					a = r->Next(5);
				}
				
				preguntas->Add(a);
				Dialogo^ dialogoForm = gcnew Dialogo(jugador, a);
				dialogoForm->ShowDialog();
				enemigos[i]->preguntaContestada();
				return;
			}
		}
	}
}

inline bool Controladora::contestadaLaIA() {
	for (int i = 0; i < enemigos->Count; i++) {
		if (!enemigos[i]->verPregunta()) {
			return false; 
		}
	}
	return true; 
}

inline int Controladora::getContestadaLaIA() {
	int contestadas = 0;
	for (int i = 0; i < enemigos->Count; i++) {
		if (enemigos[i]->verPregunta()) {
			contestadas++;
		}
	}
	return contestadas;
}
inline int Controladora::getTotalIAs() {
	return enemigos->Count;
}