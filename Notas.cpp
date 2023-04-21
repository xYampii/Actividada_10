#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// Definición de la estructura Estudiante
struct Estudiante {
    int id;
    char nombres[50];
    char apellidos[50];
    float notas[4];
    float promedio;
    char resultado[10];
};

// Prototipos de funciones
void crear();
void leer();
void actualizar();
void eliminar();
void mostrar(Estudiante est);
void agregar(Estudiante* est, int n);
void calcular_promedio(Estudiante* est, int n);
void actualizar_resultado(Estudiante* est, int n);

// Función principal
int main() {
    int opcion;
    do {
        cout << "Seleccione una opción:" << endl;
        cout << "1. Crear registro" << endl;
        cout << "2. Leer registros" << endl;
        cout << "3. Actualizar registro" << endl;
        cout << "4. Eliminar registro" << endl;
        cout << "5. Salir" << endl;
        cin >> opcion;

        switch (opcion) {
            case 1:
                crear();
                break;
            case 2:
                leer();
                break;
            case 3:
                actualizar();
                break;
            case 4:
                eliminar();
                break;
            case 5:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción inválida. Intente de nuevo." << endl;
                break;
        }
    } while (opcion != 5);

    return 0;
}

// Función para crear un registro
void crear() {
    int n;
    cout << "Ingrese la cantidad de estudiantes que desea registrar: ";
    cin >> n;

    // Crear un arreglo de estructuras para almacenar los datos de los estudiantes
    Estudiante* estudiantes = new Estudiante[n];

    // Solicitar los datos de cada estudiante y agregarlos al arreglo
    agregar(estudiantes, n);

    // Calcular el promedio y actualizar el resultado de cada estudiante
    calcular_promedio(estudiantes, n);
    actualizar_resultado(estudiantes, n);

    // Escribir los datos de los estudiantes en el archivo binario
    ofstream archivo("notas.dat", ios::binary);
    if (archivo) {
        archivo.write((char*) estudiantes, n * sizeof(Estudiante));
        cout << "Registros guardados correctamente." << endl;
    } else {
        cout << "Error al abrir el archivo." << endl;
    }

    // Liberar la memoria asignada al arreglo de estudiantes
    delete[] estudiantes;
}

// Función para leer los registros almacenados en el archivo binario
void leer() {
    ifstream archivo("notas.dat", ios::binary);
    if (archivo) {
        Estudiante est;
        while (archivo.read((char*) &est, sizeof(Estudiante))) {
            mostrar(est);
        }
    } else {
        cout << "Error al abrir el archivo." << endl;
    }
}

// Función para actualizar un registro
void actualizar() {
    int id;
    cout << "Ingrese el ID del estudiante que desea actualizar: ";
    cin >> id;

    // Abrir el archivo en modo lectura/escritura
    fstream archivo("notas.dat", ios::in | ios::out | ios::binary);
    if (archivo) {
        bool encontrado = false;
        Estudiante est;
        while (archivo.read((char*) &est, sizeof(Estudiante))) {
            if (est.id == id) {
                // Mostrar los datos actuales del estudiante
                mostrar(est);

                // Solicitar los nuevos datos del estudiante
                cout << "Ingrese los nuevos datos del estudiante:" << endl;
                cout << "ID: ";
                cin >> est.id;
                cout << "Nombres: ";
                cin.ignore();
                cin.getline(est.nombres, 50);
                cout << "Apellidos: ";
                cin.getline(est.apellidos, 50);
                cout << "Nota 1: ";
                cin >> est.notas[0];
                cout << "Nota 2: ";
                cin >> est.notas[1];
                cout << "Nota 3: ";
                cin >> est.notas[2];
                cout << "Nota 4: ";
                cin >> est.notas[3];

                // Calcular el promedio y actualizar el resultado del estudiante
                est.promedio = (est.notas[0] + est.notas[1] + est.notas[2] + est.notas[3]) / 4.0;
                if (est.promedio >= 60) {
                    strcpy(est.resultado, "Aprobado");
                } else {
                    strcpy(est.resultado, "Reprobado");
                }

                // Escribir los nuevos datos del estudiante en el archivo
                archivo.seekp(-sizeof(Estudiante), ios::cur);
                archivo.write((char*) &est, sizeof(Estudiante));

                cout << "Registro actualizado correctamente." << endl;
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            cout << "No se encontró el estudiante con ID " << id << "." << endl;
        }
    } else {
        cout << "Error al abrir el archivo." << endl;
    }
}

// Función para eliminar un registro
void eliminar() {
    int id;
    cout << "Ingrese el ID del estudiante que desea eliminar: ";
    cin >> id;

    // Crear un archivo temporal para almacenar los registros no eliminados
    ofstream archivo_temp("temp.dat", ios::binary);

    // Abrir el archivo original en modo lectura
    ifstream archivo("notas.dat", ios::binary);
    if (archivo) {
        bool encontrado = false;
        Estudiante est;
        while (archivo.read((char*) &est, sizeof(Estudiante))) {
            if (est.id == id) {
                mostrar(est);
                encontrado = true;
            } else {
                archivo_temp.write((char*) &est, sizeof(Estudiante));
            }
        }
        if (!encontrado) {
            cout << "No se encontró el estudiante con ID " << id << "." << endl;
        } else {
            // Cerrar los archivos y eliminar el archivo original
            archivo.close();
            archivo_temp.close();
            remove("notas.dat");

            // Renombrar el archivo temporal como el archivo original
            rename("temp.dat", "notas.dat");

            cout << "Registro eliminado correctamente." << endl;
        }
    } else {
        cout << "Error al abrir el archivo." << endl;
    }
}

// Función para mostrar todos los registros
void mostrar_todo() {
    ifstream archivo("notas.dat", ios::binary);
    if (archivo) {
        Estudiante est;
        while (archivo.read((char*) &est, sizeof(Estudiante))) {
            mostrar(est);
        }
    } else {
        cout << "Error al abrir el archivo." << endl;
    }
}

// Función principal
int main() {
    int opcion;
    do {
        cout << "===== CRUD de estudiantes =====" << endl;
        cout << "1. Agregar registro" << endl;
        cout << "2. Mostrar registro" << endl;
        cout << "3. Actualizar registro" << endl;
        cout << "4. Eliminar registro" << endl;
        cout << "5. Mostrar todos los registros" << endl;
        cout << "6. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                agregar();
                break;
            case 2:
                mostrar();
                break;
            case 3:
                actualizar();
                break;
            case 4:
                eliminar();
                break;
            case 5:
                mostrar_todo();
                break;
            case 6:
                cout << "Adiós" << endl;
                break;
            default:
                cout << "Opción inválida." << endl;
                break;
        }
        cout << endl;
    } while (opcion != 6);

    return 0;
}