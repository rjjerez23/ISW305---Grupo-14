#include <iostream>
#include <limits>
#include "DependencyGraph.h"

using namespace std;

int main()
{
    GrafoDependencias grafo;
    int opcion = 0;

    do
    {
        cout << "\n1. Agregar dependencia" << endl;
        cout << "2. Mostrar orden de carga" << endl;
        cout << "3. Detectar ciclos de dependencia" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opcion invalida." << endl;
            continue;
        }

        if (opcion == 1)
        {
            string modulo;
            string dependencia;

            cout << "Ingrese modulo y dependencia (A B significa A -> B): ";
            cin >> modulo >> dependencia;

            if (modulo.empty() || dependencia.empty())
            {
                cout << "Nombres de modulos invalidos." << endl;
            }
            else
            {
                grafo.agregarDependencia(modulo, dependencia);
                cout << "Dependencia agregada: " << modulo << " -> " << dependencia << endl;
            }
        }
        else if (opcion == 2)
        {
            vector<string> orden = grafo.obtenerOrdenCarga();

            if (orden.empty())
            {
                cout << "No hay modulos registrados." << endl;
            }
            else
            {
                cout << "Orden de carga: ";

                for (const string& modulo : orden)
                {
                    cout << modulo << " ";
                }

                cout << endl;
            }
        }
        else if (opcion == 3)
        {
            if (grafo.tieneCiclo())
            {
                cout << "Se encontro un ciclo de dependencias." << endl;
            }
            else
            {
                cout << "No se encontraron ciclos de dependencias." << endl;
            }
        }
        else if (opcion != 4)
        {
            cout << "Opcion invalida." << endl;
        }
    }
    while (opcion != 4);

    cout << "Programa finalizado." << endl;
    return 0;
}
