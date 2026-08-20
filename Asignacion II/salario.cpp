// Asignacion I, Rikeini Jerez
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Clase que representa cada nodo de la lista
class Nodo {
public:
    string nombre;
    double salarioBase;
    double porcentajeDescuento;
    Nodo* siguiente;

    Nodo(string nom, double salario, double descuento) {
        nombre = nom;
        salarioBase = salario;
        porcentajeDescuento = descuento;
        siguiente = nullptr;
    }
};

// Clase para manejar la lista simplemente enlazada
class ListaEmpleados {
private:
    Nodo* cabeza;

public:
    // Constructor
    ListaEmpleados() {
        cabeza = nullptr;
    }

    // Insertar empleado al inicio de la lista
    void insertarEmpleado(string nombre, double salarioBase, double porcentajeDescuento) {
        Nodo* nuevo = new Nodo(nombre, salarioBase, porcentajeDescuento);

        nuevo->siguiente = cabeza;
        cabeza = nuevo;

        cout << "\nEmpleado registrado correctamente.\n";
    }

    // Calcular el salario neto
    double calcularSalarioNeto(double salarioBase, double porcentajeDescuento) {
        double descuento = salarioBase * (porcentajeDescuento / 100);

        return salarioBase - descuento;
    }

    // Mostrar todos los empleados con su salario neto
    void mostrarEmpleados() {
        if (cabeza == nullptr) {
            cout << "\nNo hay empleados registrados.\n";
            return;
        }

        Nodo* actual = cabeza;

        cout << "\n========== LISTA DE EMPLEADOS ==========\n";

        while (actual != nullptr) {
            double salarioNeto = calcularSalarioNeto(
                actual->salarioBase,
                actual->porcentajeDescuento
            );

            cout << "\nNombre: " << actual->nombre;
            cout << "\nSalario base: RD$ "
                 << fixed << setprecision(2)
                 << actual->salarioBase;

            cout << "\nDescuento: "
                 << actual->porcentajeDescuento << "%";

            cout << "\nSalario neto: RD$ "
                 << salarioNeto << "\n";

            cout << "----------------------------------------\n";

            actual = actual->siguiente;
        }
    }

    // Mostrar empleados con salario neto mayor a RD$50,000
    void mostrarSalariosMayoresA50000() {
        if (cabeza == nullptr) {
            cout << "\nNo hay empleados registrados.\n";
            return;
        }

        Nodo* actual = cabeza;
        bool encontrado = false;

        cout << "\n===== EMPLEADOS CON SALARIO NETO MAYOR A RD$50,000 =====\n";

        while (actual != nullptr) {
            double salarioNeto = calcularSalarioNeto(
                actual->salarioBase,
                actual->porcentajeDescuento
            );

            if (salarioNeto > 50000) {
                cout << "\nNombre: " << actual->nombre;
                cout << "\nSalario neto: RD$ "
                     << fixed << setprecision(2)
                     << salarioNeto << "\n";

                cout << "----------------------------------------\n";

                encontrado = true;
            }

            actual = actual->siguiente;
        }

        if (!encontrado) {
            cout << "\nNo hay empleados con un salario neto mayor a RD$50,000.\n";
        }
    }

    // Destructor para liberar la memoria
    ~ListaEmpleados() {
        Nodo* actual = cabeza;

        while (actual != nullptr) {
            Nodo* temporal = actual;
            actual = actual->siguiente;

            delete temporal;
        }
    }
};


int main() {
    ListaEmpleados lista;

    int opcion;
    string nombre;
    double salarioBase;
    double porcentajeDescuento;

    do {
        cout << "\n========================================";
        cout << "\n   SISTEMA DE CALCULO DE SALARIO NETO";
        cout << "\n========================================";

        cout << "\n1. Registrar empleado";
        cout << "\n2. Mostrar todos los empleados";
        cout << "\n3. Mostrar empleados con salario neto mayor a RD$50,000";
        cout << "\n4. Salir";

        cout << "\n\nSeleccione una opcion: ";
        cin >> opcion;

        cin.ignore();

        switch (opcion) {

        case 1:
            cout << "\nIngrese el nombre del empleado: ";
            getline(cin, nombre);

            cout << "Ingrese el salario base: ";
            cin >> salarioBase;

            cout << "Ingrese el porcentaje de descuento por impuestos: ";
            cin >> porcentajeDescuento;

            lista.insertarEmpleado(
                nombre,
                salarioBase,
                porcentajeDescuento
            );

            break;

        case 2:
            lista.mostrarEmpleados();
            break;

        case 3:
            lista.mostrarSalariosMayoresA50000();
            break;

        case 4:
            cout << "\nSaliendo del programa...\n";
            break;

        default:
            cout << "\nOpcion no valida. Intente nuevamente.\n";
        }

    } while (opcion != 4);

    return 0;
}
