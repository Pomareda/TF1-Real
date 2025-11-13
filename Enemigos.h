#pragma once
#include "Entidad.h"
#include "Jugador.h"

class Enemigos : public Entidad {
protected:
	int dx, dy;
	Jugador* jugador; //para que los enemigos puedan interactuar con el jugador
	bool activo;

public:
	Enemigos(int x, int y, Jugador* jugador);
	~Enemigos();

	bool estaActivo() { return activo; }
	void desactivar() { activo = false; }

	void mover(char p);
	void dibujar();
	//bool colision();

	int getAncho() { return ancho; }
	int getAlto() { return alto; }
};


