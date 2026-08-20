#include <iostream>

using namespace std;

class Almacen {

private:
    int inventario[6][15];

public:

void registrarExistencias() {

    for (int almacen = 0; almacen < 6; almacen++) {

        cout << "\n--- Almacen " << almacen << " ---\n";

        for (int producto = 0; producto < 15; producto++) {

            cout << "Producto " << producto << ": ";
            cin >> inventario[almacen][producto];

        }
    }
}

void detectarAgotados() {
    for (int almacen = 0; almacen < 6; almacen++) {

        for (int producto = 0; producto < 15; producto++) {

            if (inventario[almacen][producto] == 0) {
                cout << "Producto " << producto << " en almacen " << almacen << " esta agotado.\n";
            }

        }
    }
}

void buscarMenorStock() {

    int menorStock = 0;
    int almacenMenor = 0;

    for (int almacen = 0; almacen < 6; almacen++) {

        int totalStock = 0;

        for (int producto = 0; producto < 15; producto++) {

            totalStock += inventario[almacen][producto];

        }

        if (totalStock < menorStock || almacen == 0) {
            menorStock = totalStock;
            almacenMenor = almacen;
        }
    }

    cout << "El almacen con menor stock es el almacen "
         << almacenMenor
         << " y tiene "
         << menorStock
         << " unidades.\n";
}

void generarAlertas(int umbral) {

    for (int almacen = 0; almacen < 6; almacen++) {

        for (int producto = 0; producto < 15; producto++) {

            if (inventario[almacen][producto] < umbral) {
                cout << "Alerta: Producto " << producto
                     << " en almacen " << almacen
                     << " tiene stock bajo: "
                     << inventario[almacen][producto]
                     << " unidades.\n";
            }

        }
    }
}
};

int main() {

    

    Almacen almacen;
     int umbral;

     cout << "Ingrese el umbral minimo: ";
        cin >> umbral;
        
    almacen.registrarExistencias();

    almacen.detectarAgotados();

    almacen.buscarMenorStock();
   

    almacen.generarAlertas(umbral);

    return 0;

}