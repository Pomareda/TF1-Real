#pragma once
using namespace System::Drawing;
ref class Camara {
private:
    int x, y;
    int ancho, alto;
    int mapaAncho, mapaAlto;

public:
    Camara(int ancho, int alto, int mapaAncho, int mapaAlto) {
        this->ancho = ancho;
        this->alto = alto;
        this->mapaAncho = mapaAncho;
        this->mapaAlto = mapaAlto;
        x = 0;
        y = 0;
    }

    ~Camara() {}

    void seguirJugador(int jugadorX, int jugadorY, int jugadorAncho, int jugadorAlto) {
        // Centrar la cámara en el jugador
        x = jugadorX + (jugadorAncho / 2) - (ancho / 2);
        y = jugadorY + (jugadorAlto / 2) - (alto / 2);

        // Limitar la cámara para que no se salga del mapa
        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x + ancho > mapaAncho) x = mapaAncho - ancho;
        if (y + alto > mapaAlto) y = mapaAlto - alto;
    }

    int getX() { return x; }
    int getY() { return y; }
    int getAncho() { return ancho; }
    int getAlto() { return alto; }

    // Convierte coordenadas del mundo a coordenadas de pantalla
    void aplicarTransformacion(Graphics^ g) {
        g->TranslateTransform(-x, -y);
    }
};
