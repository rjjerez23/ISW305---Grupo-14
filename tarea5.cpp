#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

class Caja {
private:
    string id;
    string descripcion;

public:
    Caja() {
        id = "";
        descripcion = "";
    }

    Caja(string idParam, string descripcionParam) {
        id = idParam;
        descripcion = descripcionParam;
    }

    string getId() const { return id; }
    string getDescripcion() const { return descripcion; }
};

class ColaEmpaque {
private:
    queue<Caja> cola;

public:
    void agregar(string id, string descripcion) {
        Caja nuevaCaja(id, descripcion);
        cola.push(nuevaCaja);
        cout << "Caja " << id << " agregada a la cola." << endl;
    }

    void procesar() {
        if (cola.empty()) {
            cout << "No hay cajas en la cola para procesar." << endl;
            return;
        }
        Caja caja = cola.front();
        cola.pop();
        cout << "Procesando caja " << caja.getId() << ": "
             << caja.getDescripcion() << endl;
    }

    void verCola() const {
        if (cola.empty()) {
            cout << "La cola de empaque esta vacia." << endl;
            return;
        }

        queue<Caja> copia = cola;
        cout << "Cajas en espera (" << copia.size() << "):" << endl;
        int posicion = 1;
        while (!copia.empty()) {
            Caja c = copia.front();
            cout << "  " << posicion << ". " << c.getId() << " - "
                 << c.getDescripcion() << endl;
            copia.pop();
            posicion++;
        }
    }

    bool estaVacia() const { return cola.empty(); }
    int tamano() const { return (int)cola.size(); }
};

vector<string> tokenizar(string linea) {
    vector<string> tokens;
    stringstream ss(linea);
    string palabra;
    while (ss >> palabra) {
        tokens.push_back(palabra);
    }
    return tokens;
}

int main() {
    ColaEmpaque cola;
    string linea;

    cout << "=== Simulador de Cola de Empaque ===" << endl;
    cout << "Comandos: agregar <ID> <descripcion>, procesar, verCola, salir" << endl;

    while (true) {
        cout << endl << "> ";
        if (!getline(cin, linea)) break;
        if (linea.empty()) continue;

        vector<string> tokens = tokenizar(linea);
        string comando = tokens[0];

        if (comando == "agregar") {
            if (tokens.size() < 3) {
                cout << "Uso: agregar <ID> <descripcion>" << endl;
                continue;
            }
            string id = tokens[1];
            string descripcion = "";
            for (unsigned int i = 2; i < tokens.size(); i++) {
                descripcion += tokens[i];
                if (i != tokens.size() - 1) descripcion += " ";
            }
            cola.agregar(id, descripcion);
        }
        else if (comando == "procesar") {
            cola.procesar();
        }
        else if (comando == "verCola") {
            cola.verCola();
        }
        else if (comando == "salir") {
            cout << "Fin del simulador." << endl;
            break;
        }
        else {
            cout << "Comando no reconocido." << endl;
        }
    }

    return 0;
}