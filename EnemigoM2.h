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
    int contadorAnimacion;
    int velocidadAnimacion;
    bool mirarIzquierda; 
    bool vaDisparar;


public:
    EnemigoM2(int x, int y, int dx, int dy) : Entidad(x, y, 950 / 5, 178) {
        this->dx = dx;
        this->dy = dy;
        proyectiles = gcnew List<ProyectilM2^>();
        bmpEnemigo = gcnew Bitmap("Imagenes/EnemigoM2.png");
        contadorDisparo = 0;
        tiempoEntreDisparos = 150;
        rangoDeteccion = 600;
        contadorAnimacion = 0;
        velocidadAnimacion = 5;
        mirarIzquierda = false;
        vaDisparar = false;
    }

    EnemigoM2(int x, int y, int dx, int dy, bool voltear) : Entidad(x, y, 950 / 5, 178) {
        this->dx = dx;
        this->dy = dy;
        proyectiles = gcnew List<ProyectilM2^>();
        bmpEnemigo = gcnew Bitmap("Imagenes/EnemigoM2.png");
        contadorDisparo = 0;
        tiempoEntreDisparos = 150;
        rangoDeteccion = 600;
        contadorAnimacion = 0;
        velocidadAnimacion = 5;
        vaDisparar = false;
        mirarIzquierda = voltear;
        idX = 4;
    }

    void actualizar(int jugadorX, int jugadorY, int anchoMapa, int altoMapa) {
        int distX = jugadorX - x;
        int distY = jugadorY - y;
        double distancia = Math::Sqrt(distX * distX + distY * distY);
        if (distancia <= rangoDeteccion) {
            contadorDisparo++;
            if (contadorDisparo >= tiempoEntreDisparos) {
                vaDisparar = true;
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
        int centroX = x /*+ ancho / 2*/;
        int centroY = y + 7;
        ProyectilM2^ nuevoProyectil = gcnew ProyectilM2(centroX, centroY, targetX, targetY);
        proyectiles->Add(nuevoProyectil);
    }

    void mover() override {
        if (vaDisparar) {

            contadorAnimacion += 2;
            if (!mirarIzquierda) {
                if (contadorAnimacion >= velocidadAnimacion) {
                    contadorAnimacion = 0;
                    idX++;
                    if (idX >= 5) {
                        idX = 0;
                        vaDisparar = false;
                    }
                }

            }
            else {
                
                if (contadorAnimacion >= velocidadAnimacion) {
                    contadorAnimacion = 0;
                    idX--;
                    if (idX <= 0) {
                        idX = 4;
                        vaDisparar = false;
                    }
                }


            }
        }
       
    }

    void dibujar(Graphics^ g, Bitmap^ bmp, int scrollY) {
        int pantallaY = y - scrollY;
        System::Drawing::Rectangle src = System::Drawing::Rectangle(idX * ancho, idY * alto, ancho, alto);
        System::Drawing::Rectangle dest = System::Drawing::Rectangle(x, pantallaY, ancho * 0.4, alto * 0.4);

        // Si debe mirar a la izquierda, voltear la imagen
        if (mirarIzquierda) {
            Bitmap^ bmpVolteado = (Bitmap^)bmp->Clone();
            bmpVolteado->RotateFlip(RotateFlipType::RotateNoneFlipX);
            g->DrawImage(bmpVolteado, dest, src, GraphicsUnit::Pixel);
            delete bmpVolteado;
        }
        else {
            g->DrawImage(bmp, dest, src, GraphicsUnit::Pixel);
        }

        // Dibujar proyectiles
        for each(ProyectilM2 ^ p in proyectiles) {
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