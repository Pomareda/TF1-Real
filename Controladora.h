#pragma once
#include "Enemigo.h"
#include "Jugador.h"
#include <vector>

class Controladora {
private:
	Jugador jugador;
	vector<Enemigo*> enemigos;
public:
	Controladora();
	~Controladora();
	void agregarEnemigo(Enemigo* enemigo);
	void moverEnemigos(Graphics^ g, Bitmap^ bmp);
	void moverJugador(Graphics^ g, Bitmap^ bmp);
	void dibujarEntidades(Graphics^ g, Bitmap^ bmp, Bitmap^ bmpEnemigo);

	Jugador* getJugador() { return &jugador; }
};

inline Controladora::Controladora() : jugador(100, 100, 64, 64) {
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
	jugador.mover();
}

inline void Controladora::dibujarEntidades(Graphics^ g, Bitmap^ bmp, Bitmap^ bmpEnemigo) {
	jugador.dibujar(g, bmp);
	for (Enemigo* enemigo : enemigos) {
		enemigo->dibujar(g, bmpEnemigo);
	}
}