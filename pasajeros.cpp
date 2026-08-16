#include <bits/stdc++.h>
using namespace std;

struct Pasajero {
    string nombre;
    int asiento;
};

class Avion {
private:
    int capacidadTotal;
    int cap1, cap2, cap3;
    Pasajero *clase1, *clase2, *clase3;
    int vendidos1, vendidos2, vendidos3;
    double precio1, precio2, precio3;

public:
    Avion(int capacidad, double p1, double p2, double p3) {
        capacidadTotal = capacidad;
        cap1 = (int) round(capacidad * 0.15);
        cap2 = (int) round(capacidad * 0.25);
        cap3 = capacidad - cap1 - cap2;

        clase1 = new Pasajero[cap1];
        clase2 = new Pasajero[cap2];
        clase3 = new Pasajero[cap3];

        vendidos1 = vendidos2 = vendidos3 = 0;
        precio1 = p1; precio2 = p2; precio3 = p3;
    }

    ~Avion() {
        delete[] clase1;
        delete[] clase2;
        delete[] clase3;
    }

    bool venderBoleto(int clase, const string &nombre) {
        if (clase == 1 && vendidos1 < cap1) {
            clase1[vendidos1] = {nombre, vendidos1 + 1};
            vendidos1++;
            return true;
        }
        if (clase == 2 && vendidos2 < cap2) {
            clase2[vendidos2] = {nombre, vendidos2 + 1};
            vendidos2++;
            return true;
        }
        if (clase == 3 && vendidos3 < cap3) {
            clase3[vendidos3] = {nombre, vendidos3 + 1};
            vendidos3++;
            return true;
        }
        return false;
    }

    bool avionLleno() const {
        return (vendidos1 + vendidos2 + vendidos3) >= capacidadTotal;
    }

    void mostrarVendidosPorClase() const {
        cout << "\n--- Asientos vendidos por clase ---\n";
        cout << "1ra clase: " << vendidos1 << " / " << cap1 << "\n";
        cout << "2da clase: " << vendidos2 << " / " << cap2 << "\n";
        cout << "3ra clase: " << vendidos3 << " / " << cap3 << "\n";
        cout << "Total vendidos: " << (vendidos1 + vendidos2 + vendidos3)
             << " / " << capacidadTotal << "\n";
    }

    void mostrarIngresos() const {
        double ing1 = vendidos1 * precio1;
        double ing2 = vendidos2 * precio2;
        double ing3 = vendidos3 * precio3;
        cout << fixed << setprecision(2);
        cout << "\n--- Ingreso estimado por clase ---\n";
        cout << "1ra clase: $" << ing1 << "\n";
        cout << "2da clase: $" << ing2 << "\n";
        cout << "3ra clase: $" << ing3 << "\n";
        cout << "Ingreso total: $" << (ing1 + ing2 + ing3) << "\n";
    }

    void listarPasajeros(int clase) const {
        const Pasajero *arr = (clase == 1) ? clase1 : (clase == 2) ? clase2 : clase3;
        int n = (clase == 1) ? vendidos1 : (clase == 2) ? vendidos2 : vendidos3;
        cout << "\nPasajeros clase " << clase << ":\n";
        for (int i = 0; i < n; i++)
            cout << "  Asiento " << arr[i].asiento << ": " << arr[i].nombre << "\n";
        if (n == 0) cout << "  (sin pasajeros registrados)\n";
    }
};

int main() {
    int capacidad;
    cout << "Capacidad total del avion: ";
    cin >> capacidad;

    double p1, p2, p3;
    cout << "Precio boleto 1ra clase: "; cin >> p1;
    cout << "Precio boleto 2da clase: "; cin >> p2;
    cout << "Precio boleto 3ra clase: "; cin >> p3;

    Avion vuelo(capacidad, p1, p2, p3);

    int opcion;
    do {
        cout << "\n===== MENU - GESTION DE PASAJEROS =====\n";
        cout << "1. Vender boleto\n";
        cout << "2. Mostrar vendidos por clase\n";
        cout << "3. Mostrar ingresos por clase\n";
        cout << "4. Listar pasajeros de una clase\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            if (vuelo.avionLleno()) {
                cout << "El avion esta completo. No se pueden vender mas boletos.\n";
                continue;
            }
            int clase;
            string nombre;
            cout << "Clase (1, 2 o 3): "; cin >> clase;
            cout << "Nombre completo del pasajero: ";
            cin.ignore();
            getline(cin, nombre);

            if (vuelo.venderBoleto(clase, nombre))
                cout << "Boleto vendido con exito.\n";
            else
                cout << "No hay asientos disponibles en esa clase o clase invalida.\n";
        } else if (opcion == 2) {
            vuelo.mostrarVendidosPorClase();
        } else if (opcion == 3) {
            vuelo.mostrarIngresos();
        } else if (opcion == 4) {
            int clase;
            cout << "Clase a listar (1, 2 o 3): "; cin >> clase;
            if (clase >= 1 && clase <= 3) vuelo.listarPasajeros(clase);
            else cout << "Clase invalida.\n";
        }
    } while (opcion != 0);

    return 0;
}

