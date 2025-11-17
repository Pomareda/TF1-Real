#pragma once
#include "Enemigo.h"
#include "Jugador.h"
#include "Recurso.h"
#include "Mapas.h"
#include <vector>
#include "Dialogo.h"
#include "Aliado.h"
#include "FormAliado.h"

using namespace System::Collections::Generic;
using namespace TF1;

ref class Controladora {
private:
	Jugador^ jugador;
	List<Enemigo^>^ enemigos;
	List <Recurso^>^ recursos;
	Aliado^ aliado;
public:
	Controladora(Bitmap^ bmp);
	~Controladora();

	void agregarEnemigo(Enemigo^ enemigo);
	void agregarRecurso(Recurso^ recursito);
	void crearRecursos(Bitmap^ recurso);
	void moverEnemigos(Graphics^ g, Bitmap^ bmp);
	void moverJugador(Graphics^ g, Bitmap^ bmp, const int mapa1[84][143]);
	void moverRecursos(Graphics^ g, Bitmap^ bmp);
	void dibujarEntidades(Graphics^ g, Bitmap^ bmp, Bitmap^ bmpEnemigo, Bitmap^ bmpRecurso, const int mapa1[84][143]);
	void dialogoConIA();
	void dibujarAliado(Graphics^ g, Bitmap^ bmp);
	void interactuarAliado();
	bool colisionAliado();
	bool colisionEnemigo(Graphics^ g);
	bool colisionRecurso(Graphics^ g);

	Jugador^ getJugador() { return jugador; }
};

inline Controladora::Controladora(Bitmap^ bmp) {
	jugador = gcnew Jugador(435, 80, bmp->Width / 6, bmp->Height / 6);
	enemigos = gcnew List<Enemigo^>();
	recursos = gcnew List<Recurso^>();
	aliado = gcnew Aliado(255, 560);
}


inline Controladora::~Controladora() {}

inline void Controladora::crearRecursos(Bitmap^ recurso)
{
	Recurso^ recursox = gcnew Recurso(recurso);
	recursos->Add(recursox);
}

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

inline void Controladora::moverJugador(Graphics^ g, Bitmap^ bmp, const int mapa1[84][143]) {
	int posicionAnteriorX = jugador->getX();
	int posicionAnteriorY = jugador->getY();

	jugador->mover(g, mapa1);

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

inline void Controladora::dibujarEntidades(Graphics^ g, Bitmap^ bmp, Bitmap^ bmpEnemigo, Bitmap^ bmpRecurso, const int mapa1[84][143]) {
	for each (Recurso ^ r in recursos) {
		r->dibujar(g, bmpRecurso, mapa1);
	}
	for each (Enemigo ^ enemigo in enemigos) {
		enemigo->dibujar(g, bmpEnemigo);
	}
	jugador->dibujar(g, bmp);

}

inline void Controladora::dibujarAliado(Graphics^ g, Bitmap^ bmp) {
	aliado->dibujar(g, bmp);
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

inline void Controladora::interactuarAliado() {
	if (jugador->getRect().IntersectsWith(aliado->getRectGrande())) {
		FormAliado^ FormA = gcnew FormAliado();
		FormA->ShowDialog();
	}
}

inline void Controladora::dialogoConIA()
{
	for (int i = 0; i < enemigos->Count; i++)
	{
		int distanciaX = jugador->getX() - enemigos[i]->getRect().X;
		int distanciaY = jugador->getY() - enemigos[i]->getRect().Y;

		if ((distanciaX < 60 && distanciaX > -60) && (distanciaY < 70 && distanciaY > -70)) {
			Dialogo^ dialogoForm = gcnew Dialogo(jugador);
			dialogoForm->ShowDialog();
			return;
		}
	}
}