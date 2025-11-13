#pragma once
#include "Entidad.h"
#include "Jugador.h"

class Enemigo : public Entidad {
protected:
	int dx, dy;
	Jugador* jugador; //para que los enemigos puedan interactuar con el jugador
	bool activo;

public:
	Enemigo(int x, int y, Jugador* jugador);
	~Enemigo();

	bool estaActivo() { return activo; }
	void desactivar() { activo = false; }

	void mover(char p);
	void dibujar();
	//bool colision();

	int getAncho() { return ancho; }
	int getAlto() { return alto; }
};


