#pragma once
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ctime>
#include <direct.h>

using namespace std;

struct Score {
    char nombreJugador[50];
    int mundo;  // 1, 2 o 3
    int puntaje;
    int confianza;  // Solo para Mundo 1
    int vidas;      // Para Mundos 2 y 3
    int tiempo;     // Para Mundo 2 (en segundos)
    int enemigosVencidos;
    int recursosRecogidos;
    int dano;       // Para Mundo 3
    char fecha[20];
};

// PARAMETERS.txt - Mundo 1
class FileParametersMundo1 {
private:
    ofstream fileWrite;
    string rutaArchivo;
    void crearDirectorio() { _mkdir("FILES"); }

public:
    FileParametersMundo1() {
        rutaArchivo = "FILES/PARAMETERS_M1.txt";
    }

    void GuardarConfiguracion(int numEnem, int numAliad, int numRec,
        int enemX[], int enemY[],
        int recX[], int recY[],
        int aliX, int aliY) {
        crearDirectorio();
        fileWrite.open(rutaArchivo, ios::out);

        if (fileWrite.fail()) return;

        fileWrite << numEnem << endl << numAliad << endl << numRec << endl;
        for (int i = 0; i < numEnem && i < 10; i++) {
            fileWrite << enemX[i] << endl << enemY[i] << endl;
        }
        for (int i = 0; i < numRec && i < 10; i++) {
            fileWrite << recX[i] << endl << recY[i] << endl;
        }
        fileWrite << aliX << endl << aliY << endl;
        fileWrite.close();
    }
};

// PARAMETERS.txt - Mundo 2
class FileParametersMundo2 {
private:
    ofstream fileWrite;
    string rutaArchivo;
    void crearDirectorio() { _mkdir("FILES"); }

public:
    FileParametersMundo2() {
        rutaArchivo = "FILES/PARAMETERS_M2.txt";
    }

    void GuardarConfiguracion(int numEnemigos, int posEnemX[], int posEnemY[]) {
        crearDirectorio();
        fileWrite.open(rutaArchivo, ios::out);

        if (fileWrite.fail()) return;

        fileWrite << numEnemigos << endl;
        for (int i = 0; i < numEnemigos && i < 5; i++) {
            fileWrite << posEnemX[i] << endl << posEnemY[i] << endl;
        }
        fileWrite.close();
    }
};

// PARAMETERS.txt - Mundo 3
class FileParametersMundo3 {
private:
    ofstream fileWrite;
    string rutaArchivo;
    void crearDirectorio() { _mkdir("FILES"); }

public:
    FileParametersMundo3() {
        rutaArchivo = "FILES/PARAMETERS_M3.txt";
    }

    void GuardarConfiguracion(int vidaBoss, int numPlataformas,
        int platX[], int platY[]) {
        crearDirectorio();
        fileWrite.open(rutaArchivo, ios::out);

        if (fileWrite.fail()) return;

        fileWrite << vidaBoss << endl << numPlataformas << endl;
        for (int i = 0; i < numPlataformas && i < 5; i++) {
            fileWrite << platX[i] << endl << platY[i] << endl;
        }
        fileWrite.close();
    }
};

// SCORES.bin 
class FileScores {
private:
    string rutaArchivo;
    void crearDirectorio() { _mkdir("FILES"); }

    string obtenerFechaActual() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        char buffer[20];
        sprintf_s(buffer, "%02d/%02d/%04d",
            ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
        return string(buffer);
    }

    
public:
    FileScores() {
        rutaArchivo = "FILES/SCORES.bin";
    }

    int ObtenerProximoIDJugador() {
        vector<Score> scores = LeerTodosLosScores();

        int maxID = 0;
        for (size_t i = 0; i < scores.size(); i++) {
            string nombre = scores[i].nombreJugador;
            if (strncmp(nombre.c_str(), "Jugador", 7) == 0) {
                int id = atoi(nombre.c_str() + 7);
                if (id > maxID) maxID = id;
            }
        }
        return maxID + 1; 
    }

    void GuardarScoreMundo1(int confianza, int enemigosVencidos, int recursosRecogidos, int idJugador) {
        crearDirectorio();
        ofstream file(rutaArchivo, ios::binary | ios::app);
        if (file.fail()) return;

        Score nuevoScore = {};
        sprintf_s(nuevoScore.nombreJugador, "Jugador%d", idJugador);

        nuevoScore.mundo = 1;
        nuevoScore.puntaje = confianza * 10 + enemigosVencidos * 50 + recursosRecogidos * 20;
        nuevoScore.confianza = confianza;
        nuevoScore.enemigosVencidos = enemigosVencidos;
        nuevoScore.recursosRecogidos = recursosRecogidos;
        nuevoScore.vidas = 0;
        nuevoScore.tiempo = 0;
        nuevoScore.dano = 0;

        string fecha = obtenerFechaActual();
        strncpy_s(nuevoScore.fecha, fecha.c_str(), 19);

        file.write(reinterpret_cast<char*>(&nuevoScore), sizeof(Score));
        file.close();
    }

    void GuardarScoreMundo2(int vidas, int tiempoSegundos, int idJugador) {
        crearDirectorio();
        ofstream file(rutaArchivo, ios::binary | ios::app);
        if (file.fail()) return;

        Score nuevoScore = {};
        sprintf_s(nuevoScore.nombreJugador, "Jugador%d", idJugador);

        nuevoScore.mundo = 2;
        nuevoScore.puntaje = max(0, (vidas * 100) - (tiempoSegundos * 10));
        nuevoScore.vidas = vidas;
        nuevoScore.tiempo = tiempoSegundos;
        nuevoScore.confianza = 0;
        nuevoScore.enemigosVencidos = 0;
        nuevoScore.recursosRecogidos = 0;
        nuevoScore.dano = 0;

        string fecha = obtenerFechaActual();
        strncpy_s(nuevoScore.fecha, fecha.c_str(), 19);

        file.write(reinterpret_cast<char*>(&nuevoScore), sizeof(Score));
        file.close();
    }

    void GuardarScoreMundo3(int danoInfligido, int vidasRestantes, int tiempoSegundos, int idJugador) {
        crearDirectorio();
        ofstream file(rutaArchivo, ios::binary | ios::app);
        if (file.fail()) return;

        Score nuevoScore = {};
        sprintf_s(nuevoScore.nombreJugador, "Jugador%d", idJugador);

        nuevoScore.mundo = 3;
        nuevoScore.puntaje = max(0,
            (danoInfligido * 10) + (vidasRestantes * 50) - (tiempoSegundos * 5)
        );
        nuevoScore.dano = danoInfligido;
        nuevoScore.vidas = vidasRestantes;
        nuevoScore.tiempo = tiempoSegundos;
        nuevoScore.confianza = 0;
        nuevoScore.enemigosVencidos = 0;
        nuevoScore.recursosRecogidos = 0;

        string fecha = obtenerFechaActual();
        strncpy_s(nuevoScore.fecha, fecha.c_str(), 19);

        file.write(reinterpret_cast<char*>(&nuevoScore), sizeof(Score));
        file.close();
    }

    vector<Score> LeerTodosLosScores() {
        vector<Score> scores;
        ifstream file(rutaArchivo, ios::binary);
        if (file.fail()) return scores;

        Score temp;
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(Score))) {
            scores.push_back(temp);
        }
        file.close();
        return scores;
    }

    vector<Score> LeerScoresPorMundo(int mundo) {
        vector<Score> todosScores = LeerTodosLosScores();
        vector<Score> scoresMundo;

        for (size_t i = 0; i < todosScores.size(); i++) {
            if (todosScores[i].mundo == mundo) {
                scoresMundo.push_back(todosScores[i]);
            }
        }
        return scoresMundo;
    }

    bool ValidarIntegridad() {
        ifstream file(rutaArchivo, ios::binary);
        if (file.fail()) return true;

        file.seekg(0, ios::end);
        streampos tamaño = file.tellg();
        file.close();

        return (tamaño % sizeof(Score) == 0);
    }

    void LimpiarArchivo() {
        crearDirectorio();
        ofstream file(rutaArchivo, ios::binary | ios::trunc);
        file.close();
    }
};