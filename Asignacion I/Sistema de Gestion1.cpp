#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include <cstdlib>

using namespace std;

// ============================================================
// FUNCIONES GENERALES
// ============================================================

void limpiarPantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar()
{
    cout << "\nPresione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int leerEntero(string mensaje)
{
    int valor;

    while (true)
    {
        cout << mensaje;

        if (cin >> valor)
        {
            return valor;
        }

        cout << "Error: debe introducir un numero entero.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double leerDouble(string mensaje)
{
    double valor;

    while (true)
    {
        cout << mensaje;

        if (cin >> valor)
        {
            return valor;
        }

        cout << "Error: debe introducir un numero valido.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string leerTexto(string mensaje)
{
    string texto;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << mensaje;
    getline(cin, texto);

    return texto;
}


// ============================================================
// CLASE ESTUDIANTE
// ============================================================

class Estudiante
{
private:
    int id;
    string nombre;
    string carrera;
    double promedio;

public:

    Estudiante()
    {
        id = 0;
        nombre = "";
        carrera = "";
        promedio = 0;
    }

    Estudiante(int i, string n, string c, double p)
    {
        id = i;
        nombre = n;
        carrera = c;
        promedio = p;
    }

    int getId()
    {
        return id;
    }

    string getNombre()
    {
        return nombre;
    }

    string getCarrera()
    {
        return carrera;
    }

    double getPromedio()
    {
        return promedio;
    }

    void setNombre(string n)
    {
        nombre = n;
    }

    void setCarrera(string c)
    {
        carrera = c;
    }

    void setPromedio(double p)
    {
        promedio = p;
    }

    void mostrar()
    {
        cout << left
             << setw(8) << id
             << setw(25) << nombre
             << setw(25) << carrera
             << setw(10) << fixed << setprecision(2) << promedio
             << endl;
    }
};


// ============================================================
// CLASE EMPLEADO
// ============================================================

class Empleado
{
private:
    int id;
    string nombre;
    string puesto;
    double salario;

public:

    Empleado()
    {
        id = 0;
        nombre = "";
        puesto = "";
        salario = 0;
    }

    Empleado(int i, string n, string p, double s)
    {
        id = i;
        nombre = n;
        puesto = p;
        salario = s;
    }

    int getId()
    {
        return id;
    }

    string getNombre()
    {
        return nombre;
    }

    string getPuesto()
    {
        return puesto;
    }

    double getSalario()
    {
        return salario;
    }

    void setNombre(string n)
    {
        nombre = n;
    }

    void setPuesto(string p)
    {
        puesto = p;
    }

    void setSalario(double s)
    {
        salario = s;
    }

    void mostrar()
    {
        cout << left
             << setw(8) << id
             << setw(25) << nombre
             << setw(25) << puesto
             << setw(12) << fixed << setprecision(2) << salario
             << endl;
    }
};


// ============================================================
// CLASE PRODUCTO
// ============================================================

class Producto
{
private:
    int id;
    string nombre;
    string categoria;
    double precio;
    int cantidad;

public:

    Producto()
    {
        id = 0;
        nombre = "";
        categoria = "";
        precio = 0;
        cantidad = 0;
    }

    Producto(int i, string n, string c, double p, int cant)
    {
        id = i;
        nombre = n;
        categoria = c;
        precio = p;
        cantidad = cant;
    }

    int getId()
    {
        return id;
    }

    string getNombre()
    {
        return nombre;
    }

    string getCategoria()
    {
        return categoria;
    }

    double getPrecio()
    {
        return precio;
    }

    int getCantidad()
    {
        return cantidad;
    }

    void setNombre(string n)
    {
        nombre = n;
    }

    void setCategoria(string c)
    {
        categoria = c;
    }

    void setPrecio(double p)
    {
        precio = p;
    }

    void setCantidad(int c)
    {
        cantidad = c;
    }

    void mostrar()
    {
        cout << left
             << setw(8) << id
             << setw(25) << nombre
             << setw(20) << categoria
             << setw(12) << fixed << setprecision(2) << precio
             << setw(10) << cantidad
             << endl;
    }
};


// ============================================================
// CLASE CLIENTE
// ============================================================

class Cliente
{
private:
    int id;
    string nombre;
    string telefono;
    string correo;

public:

    Cliente()
    {
        id = 0;
        nombre = "";
        telefono = "";
        correo = "";
    }

    Cliente(int i, string n, string t, string c)
    {
        id = i;
        nombre = n;
        telefono = t;
        correo = c;
    }

    int getId()
    {
        return id;
    }

    string getNombre()
    {
        return nombre;
    }

    string getTelefono()
    {
        return telefono;
    }

    string getCorreo()
    {
        return correo;
    }

    void setNombre(string n)
    {
        nombre = n;
    }

    void setTelefono(string t)
    {
        telefono = t;
    }

    void setCorreo(string c)
    {
        correo = c;
    }

    void mostrar()
    {
        cout << left
             << setw(8) << id
             << setw(25) << nombre
             << setw(18) << telefono
             << setw(30) << correo
             << endl;
    }
};


// ============================================================
// VECTORES
// ============================================================

vector<Estudiante> estudiantes;
vector<Empleado> empleados;
vector<Producto> productos;
vector<Cliente> clientes;


// ============================================================
// FUNCIONES PARA BUSCAR ID
// ============================================================

bool existeEstudiante(int id)
{
    for (size_t i = 0; i < estudiantes.size(); i++)
    {
        if (estudiantes[i].getId() == id)
        {
            return true;
        }
    }

    return false;
}

bool existeEmpleado(int id)
{
    for (size_t i = 0; i < empleados.size(); i++)
    {
        if (empleados[i].getId() == id)
        {
            return true;
        }
    }

    return false;
}

bool existeProducto(int id)
{
    for (size_t i = 0; i < productos.size(); i++)
    {
        if (productos[i].getId() == id)
        {
            return true;
        }
    }

    return false;
}

bool existeCliente(int id)
{
    for (size_t i = 0; i < clientes.size(); i++)
    {
        if (clientes[i].getId() == id)
        {
            return true;
        }
    }

    return false;
}


// ============================================================
// GUARDAR ESTUDIANTES
// ============================================================

void guardarEstudiantes()
{
    ofstream archivo("estudiantes.txt");

    if (!archivo)
    {
        cout << "Error al guardar estudiantes.\n";
        return;
    }

    for (size_t i = 0; i < estudiantes.size(); i++)
    {
        archivo << estudiantes[i].getId() << "|"
                << estudiantes[i].getNombre() << "|"
                << estudiantes[i].getCarrera() << "|"
                << estudiantes[i].getPromedio() << endl;
    }

    archivo.close();
}


// ============================================================
// CARGAR ESTUDIANTES
// ============================================================

void cargarEstudiantes()
{
    ifstream archivo("estudiantes.txt");

    if (!archivo)
    {
        return;
    }

    estudiantes.clear();

    int id;
    double promedio;
    string nombre;
    string carrera;

    while (archivo >> id)
    {
        archivo.ignore();

        getline(archivo, nombre, '|');
        getline(archivo, carrera, '|');

        archivo >> promedio;
        archivo.ignore();

        estudiantes.push_back(
            Estudiante(id, nombre, carrera, promedio)
        );
    }

    archivo.close();
}


// ============================================================
// GUARDAR EMPLEADOS
// ============================================================

void guardarEmpleados()
{
    ofstream archivo("empleados.txt");

    if (!archivo)
    {
        cout << "Error al guardar empleados.\n";
        return;
    }

    for (size_t i = 0; i < empleados.size(); i++)
    {
        archivo << empleados[i].getId() << "|"
                << empleados[i].getNombre() << "|"
                << empleados[i].getPuesto() << "|"
                << empleados[i].getSalario() << endl;
    }

    archivo.close();
}


// ============================================================
// CARGAR EMPLEADOS
// ============================================================

void cargarEmpleados()
{
    ifstream archivo("empleados.txt");

    if (!archivo)
    {
        return;
    }

    empleados.clear();

    int id;
    double salario;
    string nombre;
    string puesto;

    while (archivo >> id)
    {
        archivo.ignore();

        getline(archivo, nombre, '|');
        getline(archivo, puesto, '|');

        archivo >> salario;
        archivo.ignore();

        empleados.push_back(
            Empleado(id, nombre, puesto, salario)
        );
    }

    archivo.close();
}


// ============================================================
// GUARDAR PRODUCTOS
// ============================================================

void guardarProductos()
{
    ofstream archivo("productos.txt");

    if (!archivo)
    {
        cout << "Error al guardar productos.\n";
        return;
    }

    for (size_t i = 0; i < productos.size(); i++)
    {
        archivo << productos[i].getId() << "|"
                << productos[i].getNombre() << "|"
                << productos[i].getCategoria() << "|"
                << productos[i].getPrecio() << "|"
                << productos[i].getCantidad() << endl;
    }

    archivo.close();
}


// ============================================================
// CARGAR PRODUCTOS
// ============================================================

void cargarProductos()
{
    ifstream archivo("productos.txt");

    if (!archivo)
    {
        return;
    }

    productos.clear();

    int id;
    double precio;
    int cantidad;
    string nombre;
    string categoria;

    while (archivo >> id)
    {
        archivo.ignore();

        getline(archivo, nombre, '|');
        getline(archivo, categoria, '|');

        archivo >> precio;
        archivo.ignore();

        archivo >> cantidad;
        archivo.ignore();

        productos.push_back(
            Producto(id, nombre, categoria, precio, cantidad)
        );
    }

    archivo.close();
}


// ============================================================
// GUARDAR CLIENTES
// ============================================================

void guardarClientes()
{
    ofstream archivo("clientes.txt");

    if (!archivo)
    {
        cout << "Error al guardar clientes.\n";
        return;
    }

    for (size_t i = 0; i < clientes.size(); i++)
    {
        archivo << clientes[i].getId() << "|"
                << clientes[i].getNombre() << "|"
                << clientes[i].getTelefono() << "|"
                << clientes[i].getCorreo() << endl;
    }

    archivo.close();
}


// ============================================================
// CARGAR CLIENTES
// ============================================================

void cargarClientes()
{
    ifstream archivo("clientes.txt");

    if (!archivo)
    {
        return;
    }

    clientes.clear();

    int id;
    string nombre;
    string telefono;
    string correo;

    while (archivo >> id)
    {
        archivo.ignore();

        getline(archivo, nombre, '|');
        getline(archivo, telefono, '|');
        getline(archivo, correo);

        clientes.push_back(
            Cliente(id, nombre, telefono, correo)
        );
    }

    archivo.close();
}


// ============================================================
// ESTUDIANTES - REGISTRAR
// ============================================================

void registrarEstudiante()
{
    limpiarPantalla();

    cout << "==============================================\n";
    cout << "          REGISTRAR ESTUDIANTE\n";
    cout << "==============================================\n";

    int id = leerEntero("ID: ");

    if (existeEstudiante(id))
    {
        cout << "\nError: ese ID ya existe.\n";
        pausar();
        return;
    }

    string nombre = leerTexto("Nombre: ");
    string carrera = leerTexto("Carrera: ");

    double promedio = leerDouble("Promedio: ");

    if (promedio < 0 || promedio > 100)
    {
        cout << "\nError: el promedio debe estar entre 0 y 100.\n";
        pausar();
        return;
    }

    estudiantes.push_back(
        Estudiante(id, nombre, carrera, promedio)
    );

    guardarEstudiantes();

    cout << "\nEstudiante registrado correctamente.\n";

    pausar();
}


// ============================================================
// ESTUDIANTES - MOSTRAR
// ============================================================

void mostrarEstudiantes()
{
    limpiarPantalla();

    cout << "================================================================\n";
    cout << "                    LISTA DE ESTUDIANTES\n";
    cout << "================================================================\n";

    if (estudiantes.empty())
    {
        cout << "\nNo hay estudiantes registrados.\n";
        pausar();
        return;
    }

    cout << left
         << setw(8) << "ID"
         << setw(25) << "Nombre"
         << setw(25) << "Carrera"
         << setw(10) << "Promedio"
         << endl;

    cout << "----------------------------------------------------------------\n";

    for (size_t i = 0; i < estudiantes.size(); i++)
    {
        estudiantes[i].mostrar();
    }

    pausar();
}


// ============================================================
// ESTUDIANTES - BUSCAR
// ============================================================

void buscarEstudiante()
{
    limpiarPantalla();

    int id = leerEntero("Digite el ID del estudiante: ");

    for (size_t i = 0; i < estudiantes.size(); i++)
    {
        if (estudiantes[i].getId() == id)
        {
            cout << "\nEstudiante encontrado:\n";
            cout << "ID: " << estudiantes[i].getId() << endl;
            cout << "Nombre: " << estudiantes[i].getNombre() << endl;
            cout << "Carrera: " << estudiantes[i].getCarrera() << endl;
            cout << "Promedio: " << estudiantes[i].getPromedio() << endl;

            pausar();
            return;
        }
    }

    cout << "\nEstudiante no encontrado.\n";

    pausar();
}


// ============================================================
// ESTUDIANTES - ACTUALIZAR
// ============================================================

void actualizarEstudiante()
{
    limpiarPantalla();

    int id = leerEntero("Digite el ID del estudiante: ");

    for (size_t i = 0; i < estudiantes.size(); i++)
    {
        if (estudiantes[i].getId() == id)
        {
            string nombre = leerTexto("Nuevo nombre: ");
            string carrera = leerTexto("Nueva carrera: ");

            double promedio = leerDouble("Nuevo promedio: ");

            if (promedio < 0 || promedio > 100)
            {
                cout << "\nPromedio no valido.\n";
                pausar();
                return;
            }

            estudiantes[i].setNombre(nombre);
            estudiantes[i].setCarrera(carrera);
            estudiantes[i].setPromedio(promedio);

            guardarEstudiantes();

            cout << "\nEstudiante actualizado correctamente.\n";

            pausar();
            return;
        }
    }

    cout << "\nEstudiante no encontrado.\n";

    pausar();
}


// ============================================================
// ESTUDIANTES - ELIMINAR
// ============================================================

void eliminarEstudiante()
{
    limpiarPantalla();

    int id = leerEntero("Digite el ID del estudiante: ");

    for (size_t i = 0; i < estudiantes.size(); i++)
    {
        if (estudiantes[i].getId() == id)
        {
            char opcion;

            cout << "\nEstudiante: "
                 << estudiantes[i].getNombre() << endl;

            cout << "Desea eliminarlo? (S/N): ";
            cin >> opcion;

            if (opcion == 'S' || opcion == 's')
            {
                estudiantes.erase(estudiantes.begin() + i);

                guardarEstudiantes();

                cout << "\nEstudiante eliminado correctamente.\n";
            }
            else
            {
                cout << "\nOperacion cancelada.\n";
            }

            pausar();
            return;
        }
    }

    cout << "\nEstudiante no encontrado.\n";

    pausar();
}


// ============================================================
// EMPLEADOS - REGISTRAR
// ============================================================

void registrarEmpleado()
{
    limpiarPantalla();

    cout << "==============================================\n";
    cout << "            REGISTRAR EMPLEADO\n";
    cout << "==============================================\n";

    int id = leerEntero("ID: ");

    if (existeEmpleado(id))
    {
        cout << "\nError: ese ID ya existe.\n";
        pausar();
        return;
    }

    string nombre = leerTexto("Nombre: ");
    string puesto = leerTexto("Puesto: ");

    double salario = leerDouble("Salario: ");

    if (salario < 0)
    {
        cout << "\nError: el salario no puede ser negativo.\n";
        pausar();
        return;
    }

    empleados.push_back(
        Empleado(id, nombre, puesto, salario)
    );

    guardarEmpleados();

    cout << "\nEmpleado registrado correctamente.\n";

    pausar();
}


// ============================================================
// EMPLEADOS - MOSTRAR
// ============================================================

void mostrarEmpleados()
{
    limpiarPantalla();

    cout << "================================================================\n";
    cout << "                     LISTA DE EMPLEADOS\n";
    cout << "================================================================\n";

    if (empleados.empty())
    {
        cout << "\nNo hay empleados registrados.\n";
        pausar();
        return;
    }

    cout << left
         << setw(8) << "ID"
         << setw(25) << "Nombre"
         << setw(25) << "Puesto"
         << setw(12) << "Salario"
         << endl;

    cout << "----------------------------------------------------------------\n";

    for (size_t i = 0; i < empleados.size(); i++)
    {
        empleados[i].mostrar();
    }

    pausar();
}


// ============================================================
// EMPLEADOS - BUSCAR
// ============================================================

void buscarEmpleado()
{
    limpiarPantalla();

    int id = leerEntero("Digite el ID del empleado: ");

    for (size_t i = 0; i < empleados.size(); i++)
    {
        if (empleados[i].getId() == id)
        {
            cout << "\nEmpleado encontrado:\n";
            cout << "ID: " << empleados[i].getId() << endl;
            cout << "Nombre: " << empleados[i].getNombre() << endl;
            cout << "Puesto: " << empleados[i].getPuesto() << endl;
            cout << "Salario: RD$ "
                 << fixed << setprecision(2)
                 << empleados[i].getSalario() << endl;

            pausar();
            return;
        }
    }

    cout << "\nEmpleado no encontrado.\n";

    pausar();
}


// ============================================================
// EMPLEADOS - ACTUALIZAR
// ============================================================

void actualizarEmpleado()
{
    limpiarPantalla();

    int id = leerEntero("Digite el ID del empleado: ");

    for (size_t i = 0; i < empleados.size(); i++)
    {
        if (empleados[i].getId() == id)
        {
            string nombre = leerTexto("Nuevo nombre: ");
            string puesto = leerTexto("Nuevo puesto: ");

            double salario = leerDouble("Nuevo salario: ");

            if (salario < 0)
            {
                cout << "\nSalario no valido.\n";
                pausar();
                return;
            }

            empleados[i].setNombre(nombre);
            empleados[i].setPuesto(puesto);
            empleados[i].setSalario(salario);

            guardarEmpleados();

            cout << "\nEmpleado actualizado correctamente.\n";

            pausar();
            return;
        }
    }

    cout << "\nEmpleado no encontrado.\n";

    pausar();
}


// ============================================================
// EMPLEADOS - ELIMINAR
// ============================================================

void eliminarEmpleado()
{
    limpiarPantalla();

    int id = leerEntero("Digite el ID del empleado: ");

    for (size_t i = 0; i < empleados.size(); i++)
    {
        if (empleados[i].getId() == id)
        {
            char opcion;

            cout << "\nEmpleado: "
                 << empleados[i].getNombre() << endl;

            cout << "Desea eliminarlo? (S/N): ";
            cin >> opcion;

            if (opcion == 'S' || opcion == 's')
            {
                empleados.erase(empleados.begin() + i);

                guardarEmpleados();

                cout << "\nEmpleado eliminado correctamente.\n";
            }
            else
            {
                cout << "\nOperacion cancelada.\n";
            }

            pausar();
            return;
        }
    }

    cout << "\nEmpleado no encontrado.\n";

    pausar();
}


// ============================================================
// PRODUCTOS - REGISTRAR
// ============================================================

void registrarProducto()
{
    limpiarPantalla();

    cout << "==============================================\n";
    cout << "             REGISTRAR PRODUCTO\n";
    cout << "==============================================\n";

    int id = leerEntero("ID: ");

    if (existeProducto(id))
    {
        cout << "\nError: ese ID ya existe.\n";
        pausar();
        return;
    }

    string nombre = leerTexto("Nombre: ");
    string categoria = leerTexto("Categoria: ");

    double precio = leerDouble("Precio: ");
    int cantidad = leerEntero("Cantidad: ");

    if (precio < 0 || cantidad < 0)
    {
        cout << "\nPrecio o cantidad no validos.\n";
        pausar();
        return;
    }

    productos.push_back(
        Producto(id, nombre, categoria, precio, cantidad)
    );

    guardarProductos();

    cout << "\nProducto registrado correctamente.\n";

    pausar();
}


// ============================================================
// PRODUCTOS - MOSTRAR
// ============================================================

void mostrarProductos()
{
    limpiarPantalla();

    cout << "======================================================================\n";
    cout << "                         LISTA DE PRODUCTOS\n";
    cout << "======================================================================\n";

    if (productos.empty())
    {
        cout << "\nNo hay productos registrados.\n";
        pausar();
        return;
    }

    cout << left
         << setw(8) << "ID"
         << setw(25) << "Nombre"
         << setw(20) << "Categoria"
         << setw(12) << "Precio"
         << setw(10) << "Cantidad"
         << endl;

    cout << "----------------------------------------------------------------------\n";

    for (size_t i = 0; i < productos.size(); i++)
    {
        productos[i].mostrar();
    }

    pausar();
}


// ============================================================
// PRODUCTOS - BUSCAR
// ============================================================

void buscarProducto()
{
    limpiarPantalla();

    int id = leerEntero("Digite el ID del producto: ");

    for (size_t i = 0; i < productos.size(); i++)
    {
        if (productos[i].getId() == id)
        {
            cout << "\nProducto encontrado:\n";
            cout << "ID: " << productos[i].getId() << endl;
            cout << "Nombre: " << productos[i].getNombre() << endl;
            cout << "Categoria: " << productos[i].getCategoria() << endl;
            cout << "Precio: RD$ "
                 << fixed << setprecision(2)
                 << productos[i].getPrecio() << endl;
            cout << "Cantidad: "
                 << productos[i].getCantidad() << endl;

            pausar();
            return;
        }
    }

    cout << "\nProducto no encontrado.\n";

    pausar();
}


// ============================================================
// PRODUCTOS - ACTUALIZAR
// ============================================================

void actualizarProducto()
{
    limpiarPantalla();

    int id = leerEntero("Digite el ID del producto: ");

    for (size_t i = 0; i < productos.size(); i++)
    {
        if (productos[i].getId() == id)
        {
            string nombre = leerTexto("Nuevo nombre: ");
            string categoria = leerTexto("Nueva categoria: ");

            double precio = leerDouble("Nuevo precio: ");
            int cantidad = leerEntero("Nueva cantidad: ");

            if (precio < 0 || cantidad < 0)
            {
                cout << "\nDatos no validos.\n";
                pausar();
                return;
            }

            productos[i].setNombre(nombre);
            productos[i].setCategoria(categoria);
            productos[i].setPrecio(precio);
            productos[i].setCantidad(cantidad);

            guardarProductos();

            cout << "\nProducto actualizado correctamente.\n";

            pausar();
            return;
        }
    }

    cout << "\nProducto no encontrado.\n";

    pausar();
}


// ============================================================
// PRODUCTOS - ELIMINAR
// ============================================================

void eliminarProducto()
{
    limpiarPantalla();

    int id = leerEntero("Digite el ID del producto: ");

    for (size_t i = 0; i < productos.size(); i++)
    {
        if (productos[i].getId() == id)
        {
            char opcion;

            cout << "\nProducto: "
                 << productos[i].getNombre() << endl;

            cout << "Desea eliminarlo? (S/N): ";
            cin >> opcion;

            if (opcion == 'S' || opcion == 's')
            {
                productos.erase(productos.begin() + i);

                guardarProductos();

                cout << "\nProducto eliminado correctamente.\n";
            }
            else
            {
                cout << "\nOperacion cancelada.\n";
            }

            pausar();
            return;
        }
    }

    cout << "\nProducto no encontrado.\n";

    pausar();
}


// ============================================================
// PRODUCTOS - VALOR DEL INVENTARIO
// ============================================================

void calcularInventario()
{
    limpiarPantalla();

    double total = 0;

    for (size_t i = 0; i < productos.size(); i++)
    {
        total += productos[i].getPrecio()
                 * productos[i].getCantidad();
    }

    cout << "==============================================\n";
    cout << "             VALOR DEL INVENTARIO\n";
    cout << "==============================================\n";

    cout << fixed << setprecision(2);

    cout << "\nValor total: RD$ " << total << endl;

    pausar();
}


// ============================================================
// CLIENTES - REGISTRAR
// ============================================================

void registrarCliente()
{
    limpiarPantalla();

    cout << "==============================================\n";
    cout << "              REGISTRAR CLIENTE\n";
    cout << "==============================================\n";

    int id = leerEntero("ID: ");

    if (existeCliente(id))
    {
        cout << "\nError: ese ID ya existe.\n";
        pausar();
        return;
    }

    string nombre = leerTexto("Nombre: ");
    string telefono = leerTexto("Telefono: ");
    string correo = leerTexto("Correo: ");

    clientes.push_back(
        Cliente(id, nombre, telefono, correo)
    );

    guardarClientes();

    cout << "\nCliente registrado correctamente.\n";

    pausar();
}


// ============================================================
// CLIENTES - MOSTRAR
// ============================================================

void mostrarClientes()
{
    limpiarPantalla();

    cout << "======================================================================\n";
    cout << "                           LISTA DE CLIENTES\n";
    cout << "======================================================================\n";

    if (clientes.empty())
    {
        cout << "\nNo hay clientes registrados.\n";
        pausar();
        return;
    }

    cout << left
         << setw(8) << "ID"
         << setw(25) << "Nombre"
         << setw(18) << "Telefono"
         << setw(30) << "Correo"
         << endl;

    cout << "----------------------------------------------------------------------\n";

    for (size_t i = 0; i < clientes.size(); i++)
    {
        clientes[i].mostrar();
    }

    pausar();
}


// ============================================================
// CLIENTES - BUSCAR
// ============================================================

void buscarCliente()
{
    limpiarPantalla();

    int id = leerEntero("Digite el ID del cliente: ");

    for (size_t i = 0; i < clientes.size(); i++)
    {
        if (clientes[i].getId() == id)
        {
            cout << "\nCliente encontrado:\n";
            cout << "ID: " << clientes[i].getId() << endl;
            cout << "Nombre: " << clientes[i].getNombre() << endl;
            cout << "Telefono: " << clientes[i].getTelefono() << endl;
            cout << "Correo: " << clientes[i].getCorreo() << endl;

            pausar();
            return;
        }
    }

    cout << "\nCliente no encontrado.\n";

    pausar();
}


// ============================================================
// CLIENTES - ACTUALIZAR
// ============================================================

void actualizarCliente()
{
    limpiarPantalla();

    int id = leerEntero("Digite el ID del cliente: ");

    for (size_t i = 0; i < clientes.size(); i++)
    {
        if (clientes[i].getId() == id)
        {
            string nombre = leerTexto("Nuevo nombre: ");
            string telefono = leerTexto("Nuevo telefono: ");
            string correo = leerTexto("Nuevo correo: ");

            clientes[i].setNombre(nombre);
            clientes[i].setTelefono(telefono);
            clientes[i].setCorreo(correo);

            guardarClientes();

            cout << "\nCliente actualizado correctamente.\n";

            pausar();
            return;
        }
    }

    cout << "\nCliente no encontrado.\n";

    pausar();
}


// ============================================================
// CLIENTES - ELIMINAR
// ============================================================

void eliminarCliente()
{
    limpiarPantalla();

    int id = leerEntero("Digite el ID del cliente: ");

    for (size_t i = 0; i < clientes.size(); i++)
    {
        if (clientes[i].getId() == id)
        {
            char opcion;

            cout << "\nCliente: "
                 << clientes[i].getNombre() << endl;

            cout << "Desea eliminarlo? (S/N): ";
            cin >> opcion;

            if (opcion == 'S' || opcion == 's')
            {
                clientes.erase(clientes.begin() + i);

                guardarClientes();

                cout << "\nCliente eliminado correctamente.\n";
            }
            else
            {
                cout << "\nOperacion cancelada.\n";
            }

            pausar();
            return;
        }
    }

    cout << "\nCliente no encontrado.\n";

    pausar();
}


// ============================================================
// MENU DE ESTUDIANTES
// ============================================================

void menuEstudiantes()
{
    int opcion;

    do
    {
        limpiarPantalla();

        cout << "==============================================\n";
        cout << "             GESTION DE ESTUDIANTES\n";
        cout << "==============================================\n";
        cout << "1. Registrar estudiante\n";
        cout << "2. Mostrar estudiantes\n";
        cout << "3. Buscar estudiante\n";
        cout << "4. Actualizar estudiante\n";
        cout << "5. Eliminar estudiante\n";
        cout << "6. Volver al menu principal\n";
        cout << "==============================================\n";

        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion)
        {
        case 1:
            registrarEstudiante();
            break;

        case 2:
            mostrarEstudiantes();
            break;

        case 3:
            buscarEstudiante();
            break;

        case 4:
            actualizarEstudiante();
            break;

        case 5:
            eliminarEstudiante();
            break;

        case 6:
            break;

        default:
            cout << "\nOpcion no valida.\n";
            pausar();
        }

    } while (opcion != 6);
}


// ============================================================
// MENU DE EMPLEADOS
// ============================================================

void menuEmpleados()
{
    int opcion;

    do
    {
        limpiarPantalla();

        cout << "==============================================\n";
        cout << "              GESTION DE EMPLEADOS\n";
        cout << "==============================================\n";
        cout << "1. Registrar empleado\n";
        cout << "2. Mostrar empleados\n";
        cout << "3. Buscar empleado\n";
        cout << "4. Actualizar empleado\n";
        cout << "5. Eliminar empleado\n";
        cout << "6. Volver al menu principal\n";
        cout << "==============================================\n";

        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion)
        {
        case 1:
            registrarEmpleado();
            break;

        case 2:
            mostrarEmpleados();
            break;

        case 3:
            buscarEmpleado();
            break;

        case 4:
            actualizarEmpleado();
            break;

        case 5:
            eliminarEmpleado();
            break;

        case 6:
            break;

        default:
            cout << "\nOpcion no valida.\n";
            pausar();
        }

    } while (opcion != 6);
}


// ============================================================
// MENU DE PRODUCTOS
// ============================================================

void menuProductos()
{
    int opcion;

    do
    {
        limpiarPantalla();

        cout << "==============================================\n";
        cout << "               GESTION DE PRODUCTOS\n";
        cout << "==============================================\n";
        cout << "1. Registrar producto\n";
        cout << "2. Mostrar productos\n";
        cout << "3. Buscar producto\n";
        cout << "4. Actualizar producto\n";
        cout << "5. Eliminar producto\n";
        cout << "6. Calcular valor del inventario\n";
        cout << "7. Volver al menu principal\n";
        cout << "==============================================\n";

        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion)
        {
        case 1:
            registrarProducto();
            break;

        case 2:
            mostrarProductos();
            break;

        case 3:
            buscarProducto();
            break;

        case 4:
            actualizarProducto();
            break;

        case 5:
            eliminarProducto();
            break;

        case 6:
            calcularInventario();
            break;

        case 7:
            break;

        default:
            cout << "\nOpcion no valida.\n";
            pausar();
        }

    } while (opcion != 7);
}


// ============================================================
// MENU DE CLIENTES
// ============================================================

void menuClientes()
{
    int opcion;

    do
    {
        limpiarPantalla();

        cout << "==============================================\n";
        cout << "                GESTION DE CLIENTES\n";
        cout << "==============================================\n";
        cout << "1. Registrar cliente\n";
        cout << "2. Mostrar clientes\n";
        cout << "3. Buscar cliente\n";
        cout << "4. Actualizar cliente\n";
        cout << "5. Eliminar cliente\n";
        cout << "6. Volver al menu principal\n";
        cout << "==============================================\n";

        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion)
        {
        case 1:
            registrarCliente();
            break;

        case 2:
            mostrarClientes();
            break;

        case 3:
            buscarCliente();
            break;

        case 4:
            actualizarCliente();
            break;

        case 5:
            eliminarCliente();
            break;

        case 6:
            break;

        default:
            cout << "\nOpcion no valida.\n";
            pausar();
        }

    } while (opcion != 6);
}


// ============================================================
// MENU PRINCIPAL
// ============================================================

void menuPrincipal()
{
    int opcion;

    do
    {
        limpiarPantalla();

        cout << "=====================================================\n";
        cout << "             SISTEMA DE GESTION INTEGRAL\n";
        cout << "=====================================================\n";
        cout << "1. Gestion de estudiantes\n";
        cout << "2. Gestion de empleados\n";
        cout << "3. Gestion de productos\n";
        cout << "4. Gestion de clientes\n";
        cout << "5. Salir\n";
        cout << "=====================================================\n";

        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion)
        {
        case 1:
            menuEstudiantes();
            break;

        case 2:
            menuEmpleados();
            break;

        case 3:
            menuProductos();
            break;

        case 4:
            menuClientes();
            break;

        case 5:
            cout << "\n============================================\n";
            cout << "      Gracias por utilizar el sistema.\n";
            cout << "============================================\n";
            break;

        default:
            cout << "\nError: opcion no valida.\n";
            pausar();
        }

    } while (opcion != 5);
}


// ============================================================
// FUNCION PRINCIPAL
// ============================================================

int main()
{
    // Cargar los datos guardados anteriormente
    cargarEstudiantes();
    cargarEmpleados();
    cargarProductos();
    cargarClientes();

    // Iniciar sistema
    menuPrincipal();

    return 0;
}
