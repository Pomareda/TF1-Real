#pragma once
#include <Windows.h>
#include <iostream>

using namespace System::Drawing;
using namespace System;

ref class Minimapa {
private:
    int x, y;
    int dx, dy;

public:
    Minimapa(int x, int y);
    ~Minimapa();

    void actualizar(int jugadorX, int jugadorY, int mapaAncho, int mapaAlto, int minimapaAncho, int minimapaAlto);
    void dibujar(Graphics^ g);

    int getX() { return x; }
    int getY() { return y; }
};

inline Minimapa::Minimapa(int x, int y) {
    this->x = x;
    this->y = y;
    dx = 0;
    dy = 0;
}

inline Minimapa::~Minimapa() {}

inline void Minimapa::actualizar(int jugadorX, int jugadorY, int mapaAncho, int mapaAlto, int minimapaAncho, int minimapaAlto) {
    x = (jugadorX * minimapaAncho) / mapaAncho;
    y = (jugadorY * minimapaAlto) / mapaAlto;
}

inline void Minimapa::dibujar(Graphics^ g) {
    g->FillEllipse(Brushes::Red, x - 5, y - 6, 10, 10);
    g->DrawEllipse(Pens::Black, x - 5, y - 6, 10, 10);
}
