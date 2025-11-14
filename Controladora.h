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
	void dibujarEntidades(Graphics^ g, Bitmap^ bmp);
};

