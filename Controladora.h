#pragma once
#include "Enemigo.h"
#include "Jugador.h"
#include "Recurso.h"
#include "Mapas.h"
#include "Dialogo.h"
#include <vector>

using namespace System::Collections::Generic;
using namespace TF1;

ref class Controladora {
private:
	Jugador^ jugador;
	List<Enemigo^>^ enemigos;
	List <Recurso^>^ recursos;
public:
	Controladora(Bitmap^bmp);
	~Controladora();
	void agregarEnemigo(Enemigo^ enemigo);
	void agregarRecurso(Recurso^ recursito);
	void crearRecursos(Bitmap^ recurso);



	void moverEnemigos(Graphics^ g, Bitmap^ bmp);
	void moverJugador(Graphics^ g, Bitmap^ bmp, int mapa1[84][143]);
	void moverRecursos(Graphics^ g, Bitmap^ bmp);

	void dibujarEntidades(Graphics^ g, Bitmap^ bmp, Bitmap^ bmpEnemigo, Bitmap^ bmpRecurso, int mapa1[84][143]);
	bool colisionEnemigo(Graphics^ g);
	bool colisionRecurso(Graphics^ g);

	void dialogoConIA();

	Jugador^ getJugador() { return jugador; }
};

inline Controladora::Controladora(Bitmap^ bmp) {
	jugador = gcnew Jugador(435, 80, bmp->Width / 6, bmp->Height / 6);
	enemigos = gcnew List<Enemigo^>();
	recursos = gcnew List<Recurso^>();
}

inline Controladora::~Controladora() { }

inline void Controladora::agregarEnemigo(Enemigo^ enemigo) {
	enemigos->Add(enemigo);
}

inline void Controladora::agregarRecurso(Recurso^ recursito)
{
	recursos->Add(recursito);
}

inline void Controladora::crearRecursos(Bitmap^ recurso)
{
	Recurso^ recursox = gcnew Recurso(recurso);
	recursos->Add(recursox);	
}


inline void Controladora::moverEnemigos(Graphics^ g, Bitmap^ bmp) {
	for each (Enemigo^ enemigo in enemigos) {
		enemigo->mover();
	}
}

inline void Controladora::moverJugador(Graphics^ g, Bitmap^ bmp, int mapa1[84][143]) {
	int posX_anterior = jugador->getX();
	int posY_anterior = jugador->getY();

	jugador->mover(g,  mapa1);

	if (colisionEnemigo(g)) {
		jugador->SetX(posX_anterior);
		jugador->SetY(posY_anterior);
	}

	if (colisionRecurso(g)) {
		//pomactm
	}
}

inline void Controladora::moverRecursos(Graphics^ g, Bitmap^ bmp)
{
	for each (Recurso^ r in recursos) {
		r->moverRecurso();
	}
}

inline void Controladora::dibujarEntidades(Graphics^ g, Bitmap^ bmp, Bitmap^ bmpEnemigo, Bitmap^ bmpRecurso, int mapa1[84][143]) {
	for each (Recurso^ r in recursos) {
		r->dibujar(g, bmpRecurso, mapa1);
	}
	for each (Enemigo^ enemigo in enemigos) {
		enemigo->dibujar(g, bmpEnemigo);
	}
	jugador->dibujar(g, bmp);

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

inline void Controladora::dialogoConIA() {
	Dialogo^ dialogoForm = gcnew Dialogo();
	dialogoForm->ShowDialog();
}
