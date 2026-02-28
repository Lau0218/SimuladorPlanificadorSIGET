# SimuladorPlanificadorSIGET
Simulador de planificación de CPU desarrollado en C++ para la materia de Sistemas Operativos - Proyecto SIGET".

Simulador de Planificación de CPU - SIGET 
¡Hola! Soy estudiante de 3er semestre de Ingeniería de Software y este es mi proyecto para la materia de Sistemas Operativos. Este simulador ha sido diseñado para entender cómo un SO administra los recursos en un entorno de movilidad inteligente.

Descripción
Este software emula el comportamiento de un planificador de CPU para el motor de procesamiento de datos urbanos SIGET. El programa gestiona el ciclo de vida completo de los procesos, permitiendo visualizar la transición entre estados y comparar la eficiencia de diferentes estrategias de asignación de tiempo de procesador en un contexto de tráfico real.

Características Técnicas
Lenguaje: C++ (Implementación mediante Programación Orientada a Objetos y gestión de hilos).
Gestión de Estados: Representación dinámica y en tiempo real de los estados del ciclo de vida:
NUEVO: Proceso creado e inicializado.
LISTO: Proceso cargado en memoria esperando turno de CPU.
EJECUCION: Proceso haciendo uso activo del procesador.
TERMINADO: Proceso que ha completado su ráfaga de CPU con éxito.

Algoritmos de Planificación Implementados:
FIFO (First-In, First-Out): Procesamiento equitativo basado en el orden de llegada, ideal para tareas de sensorización de rutina.
Prioridades (No Apropiativo): Algoritmo optimizado para la respuesta inmediata a emergencias viales (Accidentes, bloqueos, ambulancias), donde el nivel de alerta define el orden de atención.

Análisis de Resultados y Casos de Prueba
Tras realizar diversas simulaciones con lotes de procesos con distintas ráfagas de CPU y niveles de prioridad, he llegado a las siguientes conclusiones:
Limitaciones de FIFO: El algoritmo presenta el "Efecto Convoy". Si un proceso de carga de datos masivos (largo) llega primero, retrasa injustificadamente alertas críticas de corta duración.
Ventaja de Prioridades en SIGET: Este modelo reduce drásticamente la latencia en eventos de emergencia. Al asignar la prioridad más alta a las alertas de accidentes, logramos que el sistema responda de forma casi inmediata tras liberar la CPU el proceso actual.
Visualización: La actualización constante del "Reloj de Sistema" en la simulación permite validar que los estados del PCB (Process Control Block) se actualizan correctamente según la lógica del kernel simulado.

Cómo ejecutarlo
Clonar el repositorio o descargar el archivo main.cpp.
Abrir el código en un IDE profesional como Visual Studio, CodeBlocks o CLion.
Compilar (usando el estándar C++11 o superior) y ejecutar para interactuar con el menú de control.
Este proyecto forma parte de mi proceso de formación académica, enfocándome en la comprensión profunda de la concurrencia, la transición de estados y la optimización de recursos en sistemas de misión crítica.
