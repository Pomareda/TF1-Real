#pragma once
#include "Enemigo.h"
#include "Jugador.h"
#include "Recurso.h"
#include <vector>

class Controladora {
private:
	Jugador jugador;
	vector<Enemigo*> enemigos;
	vector <Recurso*> recursos;
public:
	Controladora(Bitmap^bmp);
	~Controladora();
	void agregarEnemigo(Enemigo* enemigo);
	void agregarRecurso(Recurso* recursito);
	void crearRecursos(Bitmap^ recurso);



	void moverEnemigos(Graphics^ g, Bitmap^ bmp);
	void moverJugador(Graphics^ g, Bitmap^ bmp);
	void moverRecursos(Graphics^ g, Bitmap^ bmp);

	void dibujarEntidades(Graphics^ g, Bitmap^ bmp, Bitmap^ bmpEnemigo, Bitmap^ bmpRecurso);
	bool colisionEnemigo(Graphics^ g);
	bool colisionRecurso(Graphics^ g);
	Jugador* getJugador() { return &jugador; }
};

inline Controladora::Controladora(Bitmap ^bmp) : jugador(100, 80, bmp->Width/6, bmp->Height/6) {
}

inline Controladora::~Controladora() {
	for (Enemigo* enemigo : enemigos) {
		delete enemigo;
	}
}

inline void Controladora::agregarEnemigo(Enemigo* enemigo) {
	enemigos.push_back(enemigo);
}

inline void Controladora::agregarRecurso(Recurso* recursito)
{
	recursos.push_back(recursito);
}

inline void Controladora::crearRecursos(Bitmap^ recurso)
{
	static int contador  = 0;
	if(contador >= 10)
	{
		Recurso* recursox = new Recurso(recurso);
		recursos.push_back(recursox);
		contador = 0;
	}

	contador++;

}


inline void Controladora::moverEnemigos(Graphics^ g, Bitmap^ bmp) {
	for (Enemigo* enemigo : enemigos) {
		enemigo->mover();
	}
}

inline void Controladora::moverJugador(Graphics^ g, Bitmap^ bmp) {
	int posX_anterior = jugador.getX();
	int posY_anterior = jugador.getY();

	jugador.mover();

	if (colisionEnemigo(g)) {
		jugador.SetX(posX_anterior);
		jugador.SetY(posY_anterior);
	}

	if(colisionRecurso(g))
	{
		jugador.setConfianza(jugador.getConfianza() + 10);
		
	}
}

inline void Controladora::moverRecursos(Graphics^ g, Bitmap^ bmp)
{
	for (Recurso* r : recursos) {
		r->moverRecurso();
	}
}

inline void Controladora::dibujarEntidades(Graphics^ g, Bitmap^ bmp, Bitmap^ bmpEnemigo, Bitmap^ bmpRecurso) {
	for (Recurso* r : recursos) {
		r->dibujar(g, bmpRecurso);
	}
	for (Enemigo* enemigo : enemigos) {
		enemigo->dibujar(g, bmpEnemigo);
	}
	jugador.dibujar(g, bmp);

}

inline bool Controladora::colisionEnemigo(Graphics^ g) {
	for (int i = 0; i < enemigos.size(); i++)
	{
		if (jugador.getRect().IntersectsWith(enemigos[i]->getRect())) {
			return true;
		}

	}

	

	return false;
}

inline bool Controladora::colisionRecurso(Graphics^ g)
{
	for (int i = 0; i < recursos.size(); i++)
	{
		if (jugador.getRect().IntersectsWith(recursos[i]->getRect())) {
			recursos[i]->setActivo(false);
			recursos.erase(recursos.begin() + i);
			return true;
		}

	}

	return false;
}
