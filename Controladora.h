#pragma once
#include "Enemigo.h"
#include "Jugador.h"
#include <vector>

class Controladora {
private:
	Jugador jugador;
	vector<Enemigo*> enemigos;
public:
	Controladora(Bitmap^bmp);
	~Controladora();
	void agregarEnemigo(Enemigo* enemigo);
	void moverEnemigos(Graphics^ g, Bitmap^ bmp);
	void moverJugador(Graphics^ g, Bitmap^ bmp);
	void dibujarEntidades(Graphics^ g, Bitmap^ bmp, Bitmap^ bmpEnemigo);
	bool colision(Graphics^ g);
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

inline void Controladora::moverEnemigos(Graphics^ g, Bitmap^ bmp) {
	for (Enemigo* enemigo : enemigos) {
		enemigo->mover();
	}
}

inline void Controladora::moverJugador(Graphics^ g, Bitmap^ bmp) {
	int posX_anterior = jugador.getX();
	int posY_anterior = jugador.getY();

	jugador.mover();

	if (colision(g)) {
		jugador.SetX(posX_anterior);
		jugador.SetY(posY_anterior);
	}
}

inline void Controladora::dibujarEntidades(Graphics^ g, Bitmap^ bmp, Bitmap^ bmpEnemigo) {
	for (Enemigo* enemigo : enemigos) {
		enemigo->dibujar(g, bmpEnemigo);
	}
	jugador.dibujar(g, bmp);
	
}

inline bool Controladora::colision(Graphics^ g) {
	for (int i = 0; i < enemigos.size(); i++)
	{
		if (jugador.getRect().IntersectsWith(enemigos[i]->getRect())) {
			return true;
		}
	}
	return false;
}