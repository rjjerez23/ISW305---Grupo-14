#include <iostream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Nodo {
public:
    string url;
    string fechaHora;
    Nodo* anterior;
    Nodo* siguiente;

    Nodo(string _url, string _fechaHora) {
        url = _url;
        fechaHora = _fechaHora;
        anterior = nullptr;
        siguiente = nullptr;
    }
};

class Historial {
private:
    Nodo* cabeza;
    Nodo* cola;
    Nodo* actual;

public:
    Historial() {
        cabeza = nullptr;
        cola = nullptr;
        actual = nullptr;
    }

    ~Historial() {
        Nodo* temp = cabeza;
        while (temp != nullptr) {
            Nodo* siguienteNodo = temp->siguiente;
            delete temp;
            temp = siguienteNodo;
        }
    }

    void insertarVisita(string url, string fechaHora) {
        Nodo* nuevo = new Nodo(url, fechaHora);

        if (cabeza == nullptr) {

            cabeza = nuevo;
            cola = nuevo;
        } else {
            nuevo->anterior = cola;
            cola->siguiente = nuevo;
            cola = nuevo;
        }

        actual = nuevo;
    }

    bool retroceder() {
        if (actual == nullptr || actual->anterior == nullptr) {
            cout << "No hay paginas anteriores en el historial.\n";
            return false;
        }
        actual = actual->anterior;
        cout << "Retrocediste a: " << actual->url
             << " (" << actual->fechaHora << ")\n";
        return true;
    }

    bool avanzar() {
        if (actual == nullptr || actual->siguiente == nullptr) {
            cout << "No hay paginas siguientes en el historial.\n";
            return false;
        }
        actual = actual->siguiente;
        cout << "Avanzaste a: " << actual->url
             << " (" << actual->fechaHora << ")\n";
        return true;
    }

    bool eliminarURL(string url) {
        Nodo* temp = cabeza;

        while (temp != nullptr) {
            if (temp->url == url) {

                if (temp->anterior != nullptr) {
                    temp->anterior->siguiente = temp->siguiente;
                } else {
                    cabeza = temp->siguiente;
                }

                if (temp->siguiente != nullptr) {
                    temp->siguiente->anterior = temp->anterior;
                } else {
                    cola = temp->anterior;
                }

                if (actual == temp) {
                    if (temp->anterior != nullptr) actual = temp->anterior;
                    else actual = temp->siguiente;
                }

                delete temp;
                cout << "URL eliminada: " << url << "\n";
                return true;
            }
            temp = temp->siguiente;
        }

        cout << "URL no encontrada en el historial: " << url << "\n";
        return false;
    }

    void mostrarHistorialInverso() {
        Nodo* temp = cola;

        if (temp == nullptr) {
            cout << "El historial esta vacio.\n";
            return;
        }

        cout << "----- Historial (mas reciente primero) -----\n";
        while (temp != nullptr) {
            cout << "URL: " << temp->url
                 << " | Fecha/Hora: " << temp->fechaHora;
            if (temp == actual) cout << "  <-- (pagina actual)";
            cout << "\n";
            temp = temp->anterior;
        }
    }
};

double milisegundos(high_resolution_clock::time_point inicio,
                    high_resolution_clock::time_point fin) {
    return duration<double, milli>(fin - inicio).count();
}

int main() {

    auto inicioPrograma = high_resolution_clock::now();

    Historial navegador;

    auto t1 = high_resolution_clock::now();
    navegador.insertarVisita("www.google.com",    "2026-08-20 08:00:00");
    navegador.insertarVisita("www.wikipedia.org", "2026-08-20 08:05:00");
    navegador.insertarVisita("www.github.com",    "2026-08-20 08:10:00");
    navegador.insertarVisita("www.stackoverflow.com", "2026-08-20 08:15:00");
    navegador.insertarVisita("www.youtube.com",   "2026-08-20 08:20:00");
    auto t2 = high_resolution_clock::now();
    double tiempoInsercion = milisegundos(t1, t2);

    cout << "\n===== Historial luego de insertar visitas =====\n";
    navegador.mostrarHistorialInverso();

    auto t3 = high_resolution_clock::now();
    cout << "\n===== Navegacion (atras / adelante) =====\n";
    navegador.retroceder();
    navegador.retroceder();
    navegador.avanzar();
    auto t4 = high_resolution_clock::now();
    double tiempoNavegacion = milisegundos(t3, t4);

    auto t5 = high_resolution_clock::now();
    cout << "\n===== Eliminando una URL del historial =====\n";
    navegador.eliminarURL("www.wikipedia.org");
    auto t6 = high_resolution_clock::now();
    double tiempoEliminacion = milisegundos(t5, t6);

    auto t7 = high_resolution_clock::now();
    cout << "\n===== Historial final (orden cronologico inverso) =====\n";
    navegador.mostrarHistorialInverso();
    auto t8 = high_resolution_clock::now();
    double tiempoMostrar = milisegundos(t7, t8);

    auto finPrograma = high_resolution_clock::now();
    double tiempoTotal = milisegundos(inicioPrograma, finPrograma);

    cout << "\n===== Tiempos de ejecucion =====\n";
    cout << "Insercion de visitas   : " << tiempoInsercion  << " ms\n";
    cout << "Navegacion (avanzar/retroceder): " << tiempoNavegacion << " ms\n";
    cout << "Eliminacion de URL     : " << tiempoEliminacion << " ms\n";
    cout << "Mostrar historial      : " << tiempoMostrar << " ms\n";
    cout << "TIEMPO TOTAL PROGRAMA  : " << tiempoTotal << " ms\n";

    return 0;
}