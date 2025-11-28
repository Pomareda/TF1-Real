#pragma once
#include "Entidad.h"
#include "ProyectilM2.h"
using namespace System::Collections::Generic;

ref class EnemigoM2 : public Entidad {
private:
    List<ProyectilM2^>^ proyectiles;
    int contadorDisparo;
    int tiempoEntreDisparos;
    int rangoDeteccion;
	Bitmap^ bmpEnemigo;

public:
    EnemigoM2(int x, int y, int dx, int dy) : Entidad(x, y, 60, 60) {
        this->dx = dx;
        this->dy = dy;
        proyectiles = gcnew List<ProyectilM2^>();
		bmpEnemigo = gcnew Bitmap("Imagenes/roca.png");//cambiar por imagen de enemigo
        contadorDisparo = 0;
        tiempoEntreDisparos = 100; 
        rangoDeteccion = 1500;
    }

    void actualizar(int jugadorX, int jugadorY, int anchoMapa, int altoMapa) {

        int distX = jugadorX - x;
        int distY = jugadorY - y;
        double distancia = Math::Sqrt(distX * distX + distY * distY);

        if (distancia <= rangoDeteccion) {
            contadorDisparo++;
            if (contadorDisparo >= tiempoEntreDisparos) {
                disparar(jugadorX, jugadorY);
                contadorDisparo = 0;
            }
        }

        for (int i = proyectiles->Count - 1; i >= 0; i--) {
            proyectiles[i]->mover();

            if (proyectiles[i]->estaFueraDePantalla(anchoMapa, altoMapa)) {
                proyectiles->RemoveAt(i);
            }
        }
    }

    void disparar(int targetX, int targetY) {
        int centroX = x + ancho / 2;
        int centroY = y + alto / 2;

        ProyectilM2^ nuevoProyectil = gcnew ProyectilM2(centroX, centroY, targetX, targetY);
        proyectiles->Add(nuevoProyectil);
    }

    void dibujar(Graphics^ g, int scrollY) {
        int pantallaY = y - scrollY;

        System::Drawing::Rectangle rect = System::Drawing::Rectangle(x, pantallaY, ancho, alto);
        g->FillRectangle(Brushes::Purple, rect);
        g->DrawRectangle(Pens::White, rect);

        // Dibujar proyectiles
        for each (ProyectilM2 ^ p in proyectiles) {
            p->dibujar(g, scrollY);
        }
    }

    bool colisionConJugador(System::Drawing::Rectangle jugadorRect) {
        for (int i = proyectiles->Count - 1; i >= 0; i--) {
            if (proyectiles[i]->getRect().IntersectsWith(jugadorRect)) {
                proyectiles->RemoveAt(i);
                return true;
            }
        }
        return false;
    }

    System::Drawing::Rectangle getRect() override {
        return System::Drawing::Rectangle(x, y, ancho, alto);
    }

    List<ProyectilM2^>^ getProyectiles() { return proyectiles; }
};