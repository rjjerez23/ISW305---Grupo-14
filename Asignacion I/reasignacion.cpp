#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Almacen {

private:

    static const int almacenes = 6;
    static const int productos = 15;

    int inventario[almacenes][productos];
    int distancia[almacenes][almacenes];
    int umbral[productos];

    struct Movimiento {
        int producto;
        int origen;
        int destino;
        int cantidad;
        int costo;
    };

    vector<Movimiento> movimientos;


    struct Arista {
        int destino;
        int capacidad;
        int costo;
        int reversa;
    };


    void agregarArista(
        vector<vector<Arista>>& grafo,
        int origen,
        int destino,
        int capacidad,
        int costo
    ) {

        Arista adelante{
            destino,
            capacidad,
            costo,
            static_cast<int>(grafo[destino].size())
        };

        Arista reversa{
            origen,
            0,
            -costo,
            static_cast<int>(grafo[origen].size())
        };

        grafo[origen].push_back(adelante);
        grafo[destino].push_back(reversa);
    }


    void redistribuirProducto(int producto) {

        const int fuente = 0;
        const int primer_origen = 1;
        const int primer_destino = 7;
        const int sumidero = 13;

        const int nodos = 14;

        vector<vector<Arista>> grafo(nodos);
        int disponible[almacenes] = {0};
        int necesita[almacenes] = {0};


        for (int almacen = 0; almacen < almacenes; almacen++) {

            if (inventario[almacen][producto] > umbral[producto]) {

                disponible[almacen] =
                    inventario[almacen][producto] - umbral[producto];

            }
            else if (inventario[almacen][producto] < umbral[producto]) {

                necesita[almacen] =
                    umbral[producto] - inventario[almacen][producto];
            }
        }
        for (int origen = 0; origen < almacenes; origen++) {

            if (disponible[origen] > 0) {

                agregarArista(
                    grafo,
                    fuente,
                    primer_origen + origen,
                    disponible[origen],
                    0
                );
            }
        }


        for (int origen = 0; origen < almacenes; origen++) {

            if (disponible[origen] <= 0) {
                continue;
            }

            for (int destino = 0; destino < almacenes; destino++) {

                if (necesita[destino] <= 0) {
                    continue;
                }
                agregarArista(
                    grafo,
                    primer_origen + origen,
                    primer_destino + destino,
                    disponible[origen],
                    distancia[origen][destino]
                );
            }
        }


        for (int destino = 0; destino < almacenes; destino++) {

            if (necesita[destino] > 0) {

                agregarArista(
                    grafo,
                    primer_destino + destino,
                    sumidero,
                    necesita[destino],
                    0
                );
            }
        }
        struct ReferenciaMovimiento {
            int origen;
            int destino;
            int posicion;
        };

        vector<ReferenciaMovimiento> referencias;

        for (int origen = 0; origen < almacenes; origen++) {

            if (disponible[origen] <= 0) {
                continue;
            }

            for (int destino = 0; destino < almacenes; destino++) {

                if (necesita[destino] <= 0) {
                    continue;
                }

                int nodoOrigen = primer_origen + origen;
                for (
                    int posicion = 0;
                    posicion < static_cast<int>(grafo[nodoOrigen].size());
                    posicion++
                ) {

                    if (
                        grafo[nodoOrigen][posicion].destino ==
                        primer_destino + destino
                    ) {

                        referencias.push_back({
                            origen,
                            destino,
                            posicion
                        });

                        break;
                    }
                }
            }
        }
        int flujoTotal = 0;
        int costoTotal = 0;

        while (true) {

            const int INF = numeric_limits<int>::max();

            vector<int> distanciaNodo(nodos, INF);
            vector<int> padreNodo(nodos, -1);
            vector<int> padreArista(nodos, -1);

            vector<bool> visitado(nodos, false);

            distanciaNodo[fuente] = 0;
            for (int iteracion = 0; iteracion < nodos; iteracion++) {

                int nodoActual = -1;

                for (int nodo = 0; nodo < nodos; nodo++) {

                    if (
                        !visitado[nodo] &&
                        distanciaNodo[nodo] != INF &&
                        (
                            nodoActual == -1 ||
                            distanciaNodo[nodo] <
                            distanciaNodo[nodoActual]
                        )
                    ) {

                        nodoActual = nodo;
                    }
                }

                if (nodoActual == -1) {
                    break;
                }

                visitado[nodoActual] = true;


                for (
                    int i = 0;
                    i < static_cast<int>(grafo[nodoActual].size());
                    i++
                ) {

                    Arista& arista = grafo[nodoActual][i];

                    if (arista.capacidad <= 0) {
                        continue;
                    }

                    int nuevaDistancia =
                        distanciaNodo[nodoActual] + arista.costo;

                    if (nuevaDistancia < distanciaNodo[arista.destino]) {

                        distanciaNodo[arista.destino] =
                            nuevaDistancia;

                        padreNodo[arista.destino] =
                            nodoActual;

                        padreArista[arista.destino] =
                            i;
                    }
                }
            }
            if (distanciaNodo[sumidero] == INF) {
                break;
            }

            int cantidadMover = numeric_limits<int>::max();

            int nodo = sumidero;

            while (nodo != fuente) {

                int padre = padreNodo[nodo];
                int posicion = padreArista[nodo];

                cantidadMover = min(
                    cantidadMover,
                    grafo[padre][posicion].capacidad
                );

                nodo = padre;
            }
            nodo = sumidero;

            while (nodo != fuente) {

                int padre = padreNodo[nodo];
                int posicion = padreArista[nodo];

                Arista& arista = grafo[padre][posicion];

                arista.capacidad -= cantidadMover;

                grafo[nodo][arista.reversa].capacidad +=
                    cantidadMover;

                nodo = padre;
            }


            flujoTotal += cantidadMover;

            costoTotal +=
                cantidadMover * distanciaNodo[sumidero];
            nodo = sumidero;

            int nodoDestino = padreNodo[nodo];
            int nodoOrigen = padreNodo[nodoDestino];

            if (
                nodoOrigen >= primer_origen &&
                nodoOrigen < primer_destino &&
                nodoDestino >= primer_destino &&
                nodoDestino < sumidero
            ) {

                int origen =
                    nodoOrigen - primer_origen;

                int destino =
                    nodoDestino - primer_destino;

                int costoMovimiento =
                    cantidadMover *
                    distancia[origen][destino];

                movimientos.push_back({
                    producto,
                    origen,
                    destino,
                    cantidadMover,
                    costoMovimiento
                });

                inventario[origen][producto] -= cantidadMover;
                inventario[destino][producto] += cantidadMover;
            }
        }
    }


public:

    void registrarUmbrales() {

        cout << "\n--- Umbrales minimos ---\n";

        for (int producto = 0; producto < productos; producto++) {

            cout << "Umbral del producto "
                 << producto
                 << ": ";

            cin >> umbral[producto];
        }
    }
    void registrarInventario() {

        cout << "\n--- Registro de inventario ---\n";

        for (int almacen = 0; almacen < almacenes; almacen++) {

            cout << "\n--- Almacen "
                 << almacen
                 << " ---\n";

            for (int producto = 0; producto < productos; producto++) {

                cout << "Producto "
                     << producto
                     << ": ";

                cin >> inventario[almacen][producto];
            }
        }
    }
    void registrarDistancias() {

        cout << "\n--- Matriz de distancias ---\n";

        for (int origen = 0; origen < almacenes; origen++) {

            for (int destino = 0; destino < almacenes; destino++) {

                if (origen == destino) {

                    distancia[origen][destino] = 0;

                } else {

                    cout << "Distancia de Almacen "
                         << origen
                         << " a Almacen "
                         << destino
                         << ": ";

                    cin >> distancia[origen][destino];
                }
            }
        }
    }
    void redistribuir() {

        movimientos.clear();

        for (int producto = 0; producto < productos; producto++) {

            redistribuirProducto(producto);
        }
    }
    void mostrarMovimientos() {

        cout << "\n====================================\n";
        cout << " MOVIMIENTOS DE REDISTRIBUCION\n";
        cout << "====================================\n";

        if (movimientos.empty()) {

            cout << "No fue necesario realizar movimientos.\n";
            return;
        }

        int costoTotal = 0;

        for (const Movimiento& movimiento : movimientos) {

            cout << "Producto "
                 << movimiento.producto
                 << ": "
                 << movimiento.cantidad
                 << " unidades movidas de Almacen "
                 << movimiento.origen
                 << " a Almacen "
                 << movimiento.destino
                 << ". Costo: "
                 << movimiento.costo
                 << "\n";

            costoTotal += movimiento.costo;
        }

        cout << "\nTotal de movimientos realizados: "
             << movimientos.size()
             << "\n";

        cout << "Costo total: "
             << costoTotal
             << "\n";
    }
    void mostrarInventarioFinal() {

        cout << "\n====================================\n";
        cout << " INVENTARIO FINAL\n";
        cout << "====================================\n";

        for (int almacen = 0; almacen < almacenes; almacen++) {

            cout << "\nAlmacen " << almacen << ":\n";

            for (int producto = 0; producto < productos; producto++) {

                cout << "Producto "
                     << producto
                     << ": "
                     << inventario[almacen][producto]
                     << " unidades\n";
            }
        }
    }
};
int main() {

    Almacen almacen;
    almacen.registrarUmbrales();

    almacen.registrarInventario();

    almacen.registrarDistancias();

    almacen.redistribuir();

    almacen.mostrarMovimientos();

    almacen.mostrarInventarioFinal();


    return 0;
}
