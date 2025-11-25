#pragma once
using namespace System::Drawing;

enum Direccioness { Ningunaa, Derechaa, Izquierdaa };

ref class JugadorIA
{
private:
    double velY;
    double gravedad;

    //VARIABLES PARA CARGAR SALTO
    double cargaActual;
    double maxCarga;
    bool cargando;
    bool subiendo;
    //--------------------------
    int x, y, dx, ancho, alto, idx, idy;
    bool izq, der, enSuelo;
    Direccioness Ultima;
    Bitmap^ bmpJugador;

public:
    JugadorIA(Bitmap^ bmp) {
        x = 50; y = 50;
        dx = 10;
        velY = 0;
        gravedad = 1.5;

        cargaActual = 0;
        maxCarga = 30;
        cargando = false;
        subiendo = true;

        idx = idy = 0;
        ancho = bmp->Width / 6;
        alto = bmp->Height / 4;
        bmpJugador = bmp;
        Ultima = Ningunaa;
        izq = der = false;
        enSuelo = false;
    };

    ~JugadorIA() {};


    void empezarCarga() {
        if (enSuelo && cargaActual == 0) {
            cargando = true;
            cargaActual = 0;
            subiendo = true;
        }
    }

    void aumentarCarga() {
        if (cargando && enSuelo) {
            if (subiendo) {
                cargaActual += 2;
            }
            else {
                cargaActual -= 2;
            }

            if (cargaActual >= maxCarga) {
                cargaActual = maxCarga;
                subiendo = false;
            }
            if (cargaActual <= 0) {
                cargaActual = 0;
                subiendo = true;
            }
        }
    }

    void liberarSalto() {
        if (cargando && enSuelo) {
            double saltoFinal = (cargaActual < 5.0) ? 5.0 : cargaActual;
            velY = -saltoFinal;  // Velocidad negativa (hacia arriba)
            cargando = false;
            enSuelo = false;  // Ya no está en el suelo
            cargaActual = 0;
        }
        else {
            cargando = false;
        }
    }

    void mover() {
        if (cargando) return; // Se queda quieto al cargar

        if (izq && x > 0) {
            x -= dx;
            idy = 1;
            Ultima = Izquierdaa;
        }
        if (der && x + ancho < 420) {
            x += dx;
            idy = 2;
            Ultima = Derechaa;
        }
        if (izq || der) {
            idx++;
            if (idx > 2) idx = 0;
        }
    }


    void dibujarConScroll(Graphics^ g, int scrollY) {
        // Convertir posición del mundo a posición de pantalla
        int pantallaY = y - scrollY;

        System::Drawing::Rectangle porcion = System::Drawing::Rectangle(idx * ancho, idy * alto, ancho, alto);
        System::Drawing::Rectangle destino = System::Drawing::Rectangle(x, pantallaY, ancho * 2.5, alto * 2.5);

        g->DrawImage(bmpJugador, destino, porcion, GraphicsUnit::Pixel);

        if (cargando) {
            g->FillRectangle(Brushes::Gray, x, pantallaY - 20, 50, 10);
            g->DrawRectangle(Pens::Black, x, pantallaY - 20, 50, 10);
            int anchoBarra = (int)((cargaActual / maxCarga) * 50);
            g->FillRectangle(Brushes::Red, x, pantallaY - 20, anchoBarra, 10);
        }
    }


    void aplicarGravedad(int altoTotal) {
        // Siempre aplicar gravedad, las colisiones manejarán enSuelo
        velY += gravedad;
        y += (int)velY;
    }

    // Setters
    void setIzquierda(bool v) { izq = v; }
    void setDerecha(bool v) { der = v; }
    void setY(int nuevaY) { y = nuevaY; }
    void setX(int nuevaX) { x = nuevaX; }

    int getY() { return y; }

    System::Drawing::Rectangle getRect() {
        return System::Drawing::Rectangle(x, y, ancho * 2.5, alto * 2.5);
    }

    bool getIzquierda() { return izq; }
    bool getDerecha() { return der; }
    bool getEnSuelo() { return enSuelo; }
    int getVelY() { return (int)velY; }

    void setEnSuelo(bool v) {
        enSuelo = v;
    }
    void setVelY(double v) {
        velY = v;
    }
};