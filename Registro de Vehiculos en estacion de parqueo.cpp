#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// Clase Vehiculo
class Vehiculo {
private:
    string placa;
    string marca;
    string modelo;
    string color;
    string tipo;
    int horaEntrada;
    int horaSalida;

public:

    // Constructor
    Vehiculo(string p, string ma, string mo, string c,
             string t, int entrada) {
        placa = p;
        marca = ma;
        modelo = mo;
        color = c;
        tipo = t;
        horaEntrada = entrada;
        horaSalida = -1;
    }

    // Obtener placa
    string getPlaca() {
        return placa;
    }

    // Registrar salida
    void registrarSalida(int salida) {
        horaSalida = salida;
    }

    // Saber si el vehiculo sigue dentro
    bool estaDentro() {
        return horaSalida == -1;
    }

    // Calcular horas estacionado
    int calcularHoras() {

        if (horaSalida == -1) {
            return 0;
        }

        int horas = horaSalida - horaEntrada;

        if (horas <= 0) {
            horas = 1;
        }

        return horas;
    }

    // Calcular precio
    double calcularPago() {

        int horas = calcularHoras();

        if (tipo == "Motocicleta" || tipo == "motocicleta") {
            return horas * 25.00;
        }
        else if (tipo == "Camioneta" || tipo == "camioneta") {
            return horas * 60.00;
        }
        else {
            return horas * 50.00;
        }
    }

    // Mostrar informacion
    void mostrarVehiculo() {

        cout << "\n----------------------------------------\n";
        cout << "Placa: " << placa << endl;
        cout << "Marca: " << marca << endl;
        cout << "Modelo: " << modelo << endl;
        cout << "Color: " << color << endl;
        cout << "Tipo: " << tipo << endl;
        cout << "Hora de entrada: " << horaEntrada << ":00" << endl;

        if (horaSalida == -1) {
            cout << "Estado: DENTRO DEL PARQUEO" << endl;
        }
        else {
            cout << "Hora de salida: " << horaSalida << ":00" << endl;
            cout << "Horas estacionado: "
                 << calcularHoras() << endl;

            cout << fixed << setprecision(2);
            cout << "Total a pagar: RD$ "
                 << calcularPago() << endl;
        }

        cout << "----------------------------------------\n";
    }
};


// Clase Parqueo
class Parqueo {
private:
    vector<Vehiculo> vehiculos;
    int capacidad;

public:

    // Constructor
    Parqueo(int capacidadMaxima) {
        capacidad = capacidadMaxima;
    }

    // Registrar vehiculo
    void registrarVehiculo() {

        if (vehiculos.size() >= capacidad) {
            cout << "\nEl parqueo esta lleno.\n";
            return;
        }

        string placa;
        string marca;
        string modelo;
        string color;
        string tipo;
        int hora;

        cout << "\n========== REGISTRO DE VEHICULO ==========\n";

        cout << "Digite la placa: ";
        getline(cin, placa);

        // Verificar placa repetida
        for (int i = 0; i < vehiculos.size(); i++) {

            if (vehiculos[i].getPlaca() == placa &&
                vehiculos[i].estaDentro()) {

                cout << "\nError: este vehiculo ya esta dentro del parqueo.\n";
                return;
            }
        }

        cout << "Digite la marca: ";
        getline(cin, marca);

        cout << "Digite el modelo: ";
        getline(cin, modelo);

        cout << "Digite el color: ";
        getline(cin, color);

        cout << "Digite el tipo de vehiculo: ";
        getline(cin, tipo);

        cout << "Digite la hora de entrada (0 - 23): ";
        cin >> hora;

        if (hora < 0 || hora > 23) {
            cout << "\nHora invalida.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Vehiculo nuevo(
            placa,
            marca,
            modelo,
            color,
            tipo,
            hora
        );

        vehiculos.push_back(nuevo);

        cout << "\nVehiculo registrado correctamente.\n";
    }

    // Registrar salida
    void registrarSalida() {

        string placa;
        int horaSalida;

        cout << "\n========== REGISTRAR SALIDA ==========\n";

        cout << "Digite la placa del vehiculo: ";
        getline(cin, placa);

        for (int i = 0; i < vehiculos.size(); i++) {

            if (vehiculos[i].getPlaca() == placa &&
                vehiculos[i].estaDentro()) {

                cout << "Digite la hora de salida (0 - 23): ";
                cin >> horaSalida;

                if (horaSalida < 0 || horaSalida > 23) {
                    cout << "\nHora invalida.\n";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    return;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                vehiculos[i].registrarSalida(horaSalida);

                cout << fixed << setprecision(2);

                cout << "\nSalida registrada correctamente.\n";
                cout << "Horas estacionado: "
                     << vehiculos[i].calcularHoras() << endl;

                cout << "Total a pagar: RD$ "
                     << vehiculos[i].calcularPago()
                     << endl;

                return;
            }
        }

        cout << "\nNo se encontro un vehiculo con esa placa dentro del parqueo.\n";
    }

    // Mostrar vehiculos actualmente dentro
    void mostrarVehiculosDentro() {

        bool encontrado = false;

        cout << "\n========== VEHICULOS DENTRO ==========\n";

        for (int i = 0; i < vehiculos.size(); i++) {

            if (vehiculos[i].estaDentro()) {
                vehiculos[i].mostrarVehiculo();
                encontrado = true;
            }
        }

        if (!encontrado) {
            cout << "No hay vehiculos dentro del parqueo.\n";
        }
    }

    // Buscar vehiculo
    void buscarVehiculo() {

        string placa;

        cout << "\n========== BUSCAR VEHICULO ==========\n";

        cout << "Digite la placa: ";
        getline(cin, placa);

        for (int i = 0; i < vehiculos.size(); i++) {

            if (vehiculos[i].getPlaca() == placa) {
                vehiculos[i].mostrarVehiculo();
                return;
            }
        }

        cout << "\nVehiculo no encontrado.\n";
    }

    // Mostrar todos los registros
    void mostrarTodos() {

        if (vehiculos.empty()) {
            cout << "\nNo existen vehiculos registrados.\n";
            return;
        }

        cout << "\n========== TODOS LOS REGISTROS ==========\n";

        for (int i = 0; i < vehiculos.size(); i++) {
            vehiculos[i].mostrarVehiculo();
        }
    }

    // Mostrar espacios disponibles
    void mostrarEstadoParqueo() {

        int ocupados = 0;

        for (int i = 0; i < vehiculos.size(); i++) {

            if (vehiculos[i].estaDentro()) {
                ocupados++;
            }
        }

        cout << "\n========== ESTADO DEL PARQUEO ==========\n";
        cout << "Capacidad total: " << capacidad << endl;
        cout << "Espacios ocupados: " << ocupados << endl;
        cout << "Espacios disponibles: "
             << capacidad - ocupados << endl;
    }
};


// Funcion para mostrar el menu
void mostrarMenu() {

    cout << "\n\n";
    cout << "============================================\n";
    cout << "      SISTEMA DE ESTACION DE PARQUEO\n";
    cout << "============================================\n";
    cout << "1. Registrar vehiculo\n";
    cout << "2. Registrar salida\n";
    cout << "3. Mostrar vehiculos dentro\n";
    cout << "4. Buscar vehiculo\n";
    cout << "5. Mostrar todos los registros\n";
    cout << "6. Mostrar estado del parqueo\n";
    cout << "7. Salir\n";
    cout << "============================================\n";
    cout << "Seleccione una opcion: ";
}


// Funcion principal
int main() {

    Parqueo parqueo(50);

    int opcion;

    do {

        mostrarMenu();

        cin >> opcion;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {

            case 1:
                parqueo.registrarVehiculo();
                break;

            case 2:
                parqueo.registrarSalida();
                break;

            case 3:
                parqueo.mostrarVehiculosDentro();
                break;

            case 4:
                parqueo.buscarVehiculo();
                break;

            case 5:
                parqueo.mostrarTodos();
                break;

            case 6:
                parqueo.mostrarEstadoParqueo();
                break;

            case 7:
                cout << "\nSaliendo del sistema...\n";
                break;

            default:
                cout << "\nOpcion invalida. Intente nuevamente.\n";
        }

    } while (opcion != 7);

    return 0;
}
