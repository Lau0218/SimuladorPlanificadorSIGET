#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <thread>
#include <chrono>

/* * PROYECTO: Simulador de Planificador de CPU para SIGET
 * MATERIA: Sistemas Operativos
 * DESCRIPCION: Implementacion de algoritmos FIFO y Prioridades con gestion de estados.
 */

using namespace std;

// Definicion de los estados del proceso segun la rubrica
enum Estado { NUEVO, LISTO, EJECUCION, BLOQUEADO, TERMINADO };

// Funcion auxiliar para convertir el Enum de Estado a Texto
string obtenerNombreEstado(Estado e) {
    switch (e) {
    case NUEVO: return "NUEVO";
    case LISTO: return "LISTO";
    case EJECUCION: return "EJECUCION";
    case BLOQUEADO: return "BLOQUEADO";
    case TERMINADO: return "TERMINADO";
    default: return "DESCONOCIDO";
    }
}

// Estructura que representa el Bloque de Control de Proceso (PCB)
struct Proceso {
    string id;
    int tiempo_irrupcion;    // Tiempo total de CPU requerido
    int tiempo_restante;     // Tiempo que le falta para terminar
    int prioridad_alerta;    // Prioridad (1 es la mas alta para emergencias)
    Estado estado;           // Estado actual en el ciclo de vida

    Proceso(string _id, int t, int p) : id(_id), tiempo_irrupcion(t), prioridad_alerta(p) {
        tiempo_restante = t;
        estado = NUEVO;
    }
};

// Funcion para dibujar la interfaz en consola
void dibujarInterfaz(const vector<Proceso>& procesos, int reloj, string algoritmo) {
    system("cls"); // Limpiar pantalla para efecto de animacion
    cout << "================================================================" << endl;
    cout << "   SIMULADOR DE CPU SIGET | Algoritmo: " << algoritmo << endl;
    cout << "   Tiempo de Sistema: " << reloj << " unidades" << endl;
    cout << "================================================================" << endl;
    cout << left << setw(15) << "ID PROCESO"
        << setw(15) << "ESTADO"
        << setw(15) << "T. RESTANTE"
        << setw(12) << "PRIORIDAD" << endl;
    cout << "----------------------------------------------------------------" << endl;

    for (const auto& p : procesos) {
        cout << left << setw(15) << p.id
            << setw(15) << obtenerNombreEstado(p.estado)
            << setw(15) << p.tiempo_restante
            << setw(12) << p.prioridad_alerta << endl;
    }
    cout << "================================================================" << endl;
}

// Implementacion Algoritmo FIFO (First-In, First-Out)
void ejecutarFIFO(vector<Proceso> procesos) {
    int reloj = 0;

    // Todos los procesos llegan y pasan a estado LISTO
    for (auto& p : procesos) p.estado = LISTO;

    for (size_t i = 0; i < procesos.size(); i++) {
        procesos[i].estado = EJECUCION;

        while (procesos[i].tiempo_restante > 0) {
            dibujarInterfaz(procesos, reloj, "FIFO (Rutina)");
            this_thread::sleep_for(chrono::milliseconds(700)); // Delay para visualizacion
            procesos[i].tiempo_restante--;
            reloj++;
        }
        procesos[i].estado = TERMINADO;
    }
    dibujarInterfaz(procesos, reloj, "FIFO - FINALIZADO");
    cout << "\nSimulacion completada satisfactoriamente.\n";
    system("pause");
}

// Implementacion Algoritmo por Prioridad (Para Emergencias)
void ejecutarPrioridad(vector<Proceso> procesos) {
    int reloj = 0;
    int completados = 0;
    int n = procesos.size();

    for (auto& p : procesos) p.estado = LISTO;

    while (completados < n) {
        int mejorIndice = -1;
        int mayorPrioridad = 999;

        // Buscar el proceso con la prioridad mas alta (numero mas bajo)
        for (int i = 0; i < n; i++) {
            if (procesos[i].estado != TERMINADO) {
                if (procesos[i].prioridad_alerta < mayorPrioridad) {
                    mayorPrioridad = procesos[i].prioridad_alerta;
                    mejorIndice = i;
                }
            }
        }

        if (mejorIndice != -1) {
            procesos[mejorIndice].estado = EJECUCION;
            while (procesos[mejorIndice].tiempo_restante > 0) {
                dibujarInterfaz(procesos, reloj, "PRIORIDAD (Emergencias)");
                this_thread::sleep_for(chrono::milliseconds(700));
                procesos[mejorIndice].tiempo_restante--;
                reloj++;
            }
            procesos[mejorIndice].estado = TERMINADO;
            completados++;
        }
    }
    dibujarInterfaz(procesos, reloj, "PRIORIDAD - FINALIZADO");
    cout << "\nSimulacion de emergencias completada satisfactoriamente.\n";
    system("pause");
}

int main() {
    // Definicion inicial de procesos segun requerimientos del SIGET
    vector<Proceso> datosEntrada;
    datosEntrada.push_back(Proceso("TRAFICO_RUTINA", 6, 3)); // Tarea normal
    datosEntrada.push_back(Proceso("ALERTA_ACCID", 3, 1));  // Prioridad maxima
    datosEntrada.push_back(Proceso("SENSOR_CLIMA", 4, 2));  // Prioridad media

    int opc;
    do {
        system("cls");
        cout << "   SISTEMA OPERATIVO SIGET - PANEL DE CONTROL\n";
        cout << "   1. Ejecutar Planificador FIFO (Datos de Rutina)\n";
        cout << "   2. Ejecutar Planificador Prioridad (Emergencias)\n";
        cout << "   3. Salir del simulador\n";
        cout << "   Seleccione una opcion: ";
        cin >> opc;

        switch (opc) {
        case 1: ejecutarFIFO(datosEntrada); break;
        case 2: ejecutarPrioridad(datosEntrada); break;
        }
    } while (opc != 3);

    return 0;
}