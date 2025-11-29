#pragma once

using namespace System;
using namespace System::Drawing;

ref class Boss {
	int x, y;
	int iY;
	int ancho, alto;
	int vida;
	bool subiendo;
public:
	Boss(int _x, int _y, int _ancho, int _alto, int _vida) {
		x = _x;
		y = _y;
		ancho = _ancho;
		alto = _alto;
		vida = _vida;
	}
	int mover() {
		if (subiendo) {
			iY--;
			if (iY <= -4) {
				subiendo = false;
			}
			else y--;
		}
		else {
			iY++;
			if (iY >= 0) {
				subiendo = true;
			}
			else y++;
		}
		return 0;
	}
	int getX() { return x; }
	int getY() { return y; }
	int getAncho() { return ancho; }
	int getAlto() { return alto; }
	int getVida() { return vida; }
	void setVida(int v) { vida = v; }
	System::Drawing::Rectangle getRect() {
		return System::Drawing::Rectangle(x, y, ancho, alto / 2);
	}
};

