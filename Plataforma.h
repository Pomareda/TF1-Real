#pragma once

using namespace System;
using namespace System::Drawing;

ref class Plataforma
{
private:
	int x, y;
	int iY;
	int ancho, alto;
	bool subiendo; //saber si la plataforma sube o baja

public:
	Plataforma(int _x, int _y, int _ancho, int _alto, int iY, bool subiendo) {
		x = _x;
		y = _y;
		ancho = _ancho;
		alto = _alto;
		this->iY = iY;
		this->subiendo = subiendo;
	}

	int getX() { return x; }
	int getY() { return y; }
	int getAncho() { return ancho; }
	int getAlto() { return alto; }
	System::Drawing::Rectangle getRect() {
		return System::Drawing::Rectangle(x, y - 5, ancho, alto);
	}

	void mover() {
		if (subiendo) {
			iY--;
			if (iY <= -2) {
				subiendo = false;
			}
			else y--;
		}
		else {
			iY++;
			if (iY >= 2) {
				subiendo = true;
			}
			else y++;
		}

	}
};

