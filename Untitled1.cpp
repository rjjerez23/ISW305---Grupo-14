#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Clase que representa el navegador
class Navegador {
private:
    vector<string> historial;
    int posicionActual;

public:

    // Constructor
    Navegador() {
        historial.push_back("Inicio");
        posicionActual = 0;
    }

    // Mostrar la pagina actual
    void mostrarPaginaActual() {
        cout << "\n========================================\n";
        cout << "          PAGINA ACTUAL\n";
        cout << "========================================\n";
        cout << "Pagina: " << historial[posicionActual] << endl;
        cout << "Posicion: " << posicionActual + 1
             << " de " << historial.size() << endl;
        cout << "========================================\n";
    }

    // Visitar una nueva pagina
    void visitarPagina(string pagina) {

        // Eliminar las paginas que estaban hacia adelante
        if (posicionActual < historial.size() - 1) {
            historial.erase(
                historial.begin() + posicionActual + 1,
                historial.end()
            );
        }

        // Agregar la nueva pagina
        historial.push_back(pagina);

        // Actualizar posicion
        posicionActual = historial.size() - 1;

        cout << "\nHas visitado: " << pagina << endl;
    }

    // Ir hacia atras
    void irAtras() {

        if (posicionActual > 0) {
            posicionActual--;

            cout << "\nHas retrocedido a: "
                 << historial[posicionActual] << endl;
        }
        else {
            cout << "\nNo puedes retroceder mas.\n";
            cout << "Ya estas en la primera pagina.\n";
        }
    }

    // Ir hacia adelante
    void irAdelante() {

        if (posicionActual < historial.size() - 1) {
            posicionActual++;

            cout << "\nHas avanzado a: "
                 << historial[posicionActual] << endl;
        }
        else {
            cout << "\nNo puedes avanzar mas.\n";
            cout << "No existen paginas hacia adelante.\n";
        }
    }

    // Mostrar todo el historial
    void mostrarHistorial() {

        cout << "\n========================================\n";
        cout << "             HISTORIAL\n";
        cout << "========================================\n";

        for (int i = 0; i < historial.size(); i++) {

            if (i == posicionActual) {
                cout << "-> ";
            }
            else {
                cout << "   ";
            }

            cout << i + 1 << ". "
                 << historial[i];

            if (i == posicionActual) {
                cout << "  <--- PAGINA ACTUAL";
            }

            cout << endl;
        }

        cout << "========================================\n";
    }
};


// Funcion para mostrar el menu
void mostrarMenu() {

    cout << "\n\n";
    cout << "========================================\n";
    cout << "       SISTEMA DE NAVEGACION WEB\n";
    cout << "========================================\n";
    cout << "1. Visitar nueva pagina\n";
    cout << "2. Ir hacia atras\n";
    cout << "3. Ir hacia adelante\n";
    cout << "4. Mostrar pagina actual\n";
    cout << "5. Mostrar historial\n";
    cout << "6. Salir\n";
    cout << "========================================\n";
    cout << "Seleccione una opcion: ";
}


// Funcion principal
int main() {

    Navegador navegador;

    int opcion;
    string pagina;

    do {

        mostrarMenu();

        cin >> opcion;

        // Limpiar el buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {

            case 1:

                cout << "\nEscriba el nombre de la pagina: ";
                getline(cin, pagina);

                if (pagina.empty()) {
                    cout << "\nError: debe escribir un nombre de pagina.\n";
                }
                else {
                    navegador.visitarPagina(pagina);
                }

                break;


            case 2:

                navegador.irAtras();

                break;


            case 3:

                navegador.irAdelante();

                break;


            case 4:

                navegador.mostrarPaginaActual();

                break;


            case 5:

                navegador.mostrarHistorial();

                break;


            case 6:

                cout << "\n========================================\n";
                cout << "      Saliendo del navegador...\n";
                cout << "========================================\n";

                break;


            default:

                cout << "\nOpcion invalida.\n";
                cout << "Seleccione una opcion del 1 al 6.\n";
        }

    } while (opcion != 6);

    return 0;
}
