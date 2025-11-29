#pragma once
#include "JugadorM3.h"

using namespace System::Drawing;

ref class Bala {
private:
	int x, y, dx, dy, ancho, alto;
	bool activa;
public:
	Bala(Bitmap^ bmp, JugadorM3^ jugador) {
		//dependiendo de a donde mira el jugador, la bala sale en distintos lados:
		switch (jugador->getUltima()) {
		case Derecha:
			x = jugador->getX() + jugador->getAncho();
			y = jugador->getY() + jugador->getAlto() / 2;
			dx = 15; dy = 0;
			break;
		case Izquierda:
			x = jugador->getX();
			y = jugador->getY() + jugador->getAlto() / 2;
			dx = -15; dy = 0;
			break;
		default:
			//para q no crashee, pero no debería entrar aquí xd
			//posición y salida raras para ver si falla
			x = jugador->getX() + jugador->getAncho(); y = jugador->getY() + jugador->getAlto();
			dy = 10;
			break;
		}
		//el jugador no mira hacia abajo

		ancho = bmp->Width / 10;
		alto = bmp->Height / 10;
		activa = true;
	};
	~Bala() {};
	void mover() {
		x += dx;
		y += dy;
		//desactivar si sale de la pantalla
		if (x < 0 || x > 1000 || y < 0 || y > 600) {
			activa = false;
		}

	}

	int getX() { return x; }
	int getY() { return y; }
	bool getActiva() { return activa; }
	System::Drawing::Rectangle getRect() { return System::Drawing::Rectangle(x + 5, y, ancho, alto); }
};


