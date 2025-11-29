#pragma once
#include "Plataforma.h"
using namespace System::Drawing;

ref class Cables {
private:
	int ancho, alto, yFinal;
	int x, y, xPlataforma, dy;
	int idx;
	int tiempoEspera, tiempoAdvertencia;
	bool activo, regresando, advertencia;
public:
	Cables(int _ancho, int _alto) {
		ancho = _ancho;
		alto = _alto;
		activo = false;
		dy = 25;
		idx = 0;
	}
	~Cables() {};

	void activar(Plataforma^ p) {
		x = p->getX();
		xPlataforma = p->getX() + (p->getAncho() / 2) - 50; //para la advertencia
		y = 900;
		yFinal = p->getY() - 180;

		activo = true;
		regresando = false;
		advertencia = true;
		tiempoEspera = 0;
		tiempoAdvertencia = 0;
		idx = 0;
	}

	void desactivar() { activo = false; }

	void aumentarIdx() {
		idx++;
		if (idx > 3) idx = 0;
	}

	void mover() {
		//20 ticks = 1 segundo (para tiempos)
		if (!activo) return;

		if (advertencia) {
			tiempoAdvertencia++;
			if (tiempoAdvertencia > 20) {
				advertencia = false;
			}
			return;
		}

		if (!regresando) {

			if (y > yFinal) {
				y -= dy; //sube
			}
			else {
				tiempoEspera++;
				if (tiempoEspera >= 30) {
					regresando = true; //empieza a bajar
				}
			}
		}
		else {
			y += dy; //baja
			if (y > 900) {
				activo = false;
			}
		}
	}

	int getX() { return x; }
	int getIDX() { return idx; }
	int getY() { return y; }
	int getYFinal() { return yFinal; }
	int getAncho() { return ancho; }
	int getAlto() { return alto; }
	int getXPlataforma() { return xPlataforma; }
	bool esActivo() { return activo; }
	bool esAdvertencia() { return advertencia; }

	System::Drawing::Rectangle getRect() { return System::Drawing::Rectangle(x, y, ancho, alto); }
};


