#pragma once

//Dependencies
#include "logic/input.hpp"
#include "logic/file.hpp"
#include "logic/particle.hpp"
#include "logic/neuralNet.hpp"
#include "graphics/ui.hpp"
float completionTime = 0.0f; // Tiempo que tarda el jugador en completar el mapa.
bool isCompleted = false; // Bandera para indicar si el jugador ha completado el mapa.

namespace gameEngine {
    extern gs::util::Clock timer;

    void create();
    void close();

    void updateEvents();
    void updateGraphics();

    void update() {
        timer.begin(); // Iniciar el temporizador al comienzo de la actualización.

        updateEvents();

        if (!isCompleted) { // Solo actualiza el tiempo si no se ha completado el mapa.
            completionTime += timer.getElapsedTime(); // Sumar el tiempo transcurrido.
        }

        // Lógica para detectar si el jugador ha completado el mapa.
        if (player.position.y > currentMap->size.y) { // Suponiendo que el jugador sale del mapa al completar.
            isCompleted = true; // Marcar como completado.
            saveCompletionTime(); // Guardar el tiempo en un archivo.
        }

        if (engine::render::window::renderFramerate != engine::render::window::eventFramerate) {
            if (ticks % (engine::render::window::eventFramerate / engine::render::window::renderFramerate) == 0)
                updateGraphics();
        }
        else {
            updateGraphics();
        }

        timer.end();
        timer.wait(engine::render::window::eventFramerate);
        ticks++;
    }
    void saveCompletionTime() {
        std::ofstream outFile("completion_times.txt", std::ios::app); // Abrir el archivo en modo append.
        if (outFile.is_open()) {
            outFile << "Tiempo completo: " << completionTime << " segundos\n"; // Guardar el tiempo.
            outFile.close(); // Cerrar el archivo.
        }
        else {
            std::cerr << "Error con el archivo." << std::endl; // Manejo de errores.
        }
    }

    bool isOpen();
}
