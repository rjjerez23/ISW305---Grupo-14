#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Paciente
{
    int turno;
    string nombre;
    int edad;
    int urgencia;
    string estado;
    string fechaAtencion;
};

string obtenerUrgencia(int urgencia)
{
    if (urgencia == 3)
        return "Alta";
    else if (urgencia == 2)
        return "Media";
    else
        return "Baja";
}

struct CompararPacientes
{
    bool operator()(const Paciente& p1, const Paciente& p2) const
    {
        if (p1.urgencia != p2.urgencia)
            return p1.urgencia < p2.urgencia;
        return p1.turno > p2.turno;
    }
};

void registrarPaciente(
    priority_queue<Paciente, vector<Paciente>, CompararPacientes>& cola,
    int& siguienteTurno)
{
    Paciente paciente{};

    cout << "\n============================================\n";
    cout << "             REGISTRAR PACIENTE\n";
    cout << "============================================\n";

    paciente.turno = siguienteTurno;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Nombre: ";
    getline(cin, paciente.nombre);

    cout << "Edad: ";
    while (!(cin >> paciente.edad) || paciente.edad <= 0)
    {
        cout << "Edad invalida. Introduzca una edad mayor que 0: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "\nNivel de urgencia:\n1 - Baja\n2 - Media\n3 - Alta\n";
    cout << "Seleccione el nivel: ";
    while (!(cin >> paciente.urgencia) || paciente.urgencia < 1 || paciente.urgencia > 3)
    {
        cout << "Nivel invalido. Seleccione 1, 2 o 3: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    paciente.estado = "En espera";
    paciente.fechaAtencion = "";
    cola.push(paciente);

    cout << "\nPaciente registrado correctamente.\n";
    cout << "Turno: " << paciente.turno << "\nNombre: " << paciente.nombre
         << "\nUrgencia: " << obtenerUrgencia(paciente.urgencia)
         << "\nEstado: " << paciente.estado << '\n';
    ++siguienteTurno;
}

void atenderPaciente(
    priority_queue<Paciente, vector<Paciente>, CompararPacientes>& cola,
    vector<Paciente>& historial)
{
    if (cola.empty())
    {
        cout << "\nNo hay pacientes en espera.\n";
        return;
    }

    Paciente paciente = cola.top();
    cola.pop();
    paciente.estado = "Atendido";

    cout << "Fecha de atencion (AAAA-MM-DD): ";
    cin >> paciente.fechaAtencion;
    while (paciente.fechaAtencion.size() != 10 ||
           paciente.fechaAtencion[4] != '-' || paciente.fechaAtencion[7] != '-')
    {
        cout << "Formato invalido. Use AAAA-MM-DD: ";
        cin >> paciente.fechaAtencion;
    }

    historial.push_back(paciente);

    cout << "\n============================================\n";
    cout << "            PACIENTE EN ATENCION\n";
    cout << "============================================\n";
    cout << "Turno: " << paciente.turno << "\nNombre: " << paciente.nombre
         << "\nEdad: " << paciente.edad << " años\nUrgencia: "
         << obtenerUrgencia(paciente.urgencia) << "\nEstado: " << paciente.estado
         << "\nFecha de atencion: " << paciente.fechaAtencion << '\n';
}

void mostrarPacientesEnEspera(
    priority_queue<Paciente, vector<Paciente>, CompararPacientes> cola)
{
    if (cola.empty())
    {
        cout << "\nNo hay pacientes en espera.\n";
        return;
    }

    cout << "\n============================================\n";
    cout << "           PACIENTES EN ESPERA\n";
    cout << "============================================\n";
    while (!cola.empty())
    {
        const Paciente paciente = cola.top();
        cola.pop();
        cout << "\nTurno: " << paciente.turno << "\nNombre: " << paciente.nombre
             << "\nEdad: " << paciente.edad << " años\nUrgencia: "
             << obtenerUrgencia(paciente.urgencia) << "\nEstado: " << paciente.estado
             << "\n--------------------------------------------\n";
    }
}

void mostrarHistorial(const vector<Paciente>& historial)
{
    if (historial.empty())
    {
        cout << "\nTodavia no se ha atendido ningun paciente.\n";
        return;
    }

    cout << "\n============================================\n";
    cout << "          HISTORIAL DE ATENCION\n";
    cout << "============================================\n";
    for (size_t i = 0; i < historial.size(); ++i)
    {
        const Paciente& paciente = historial[i];
        cout << "\nAtencion #" << i + 1 << "\nTurno: " << paciente.turno
             << "\nNombre: " << paciente.nombre << "\nEdad: " << paciente.edad
             << " años\nUrgencia: " << obtenerUrgencia(paciente.urgencia)
             << "\nEstado: " << paciente.estado << "\nFecha: "
             << paciente.fechaAtencion
             << "\n--------------------------------------------\n";
    }
}

const Paciente* buscarPacientePorNombre(const vector<Paciente>& historial,
                                        const string& nombre)
{
    for (const Paciente& paciente : historial)
        if (paciente.nombre == nombre)
            return &paciente;
    return nullptr;
}

void buscarPaciente(const vector<Paciente>& historial)
{
    if (historial.empty())
    {
        cout << "\nNo hay pacientes atendidos para buscar.\n";
        return;
    }

    string nombre;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Nombre exacto del paciente: ";
    getline(cin, nombre);

    const Paciente* paciente = buscarPacientePorNombre(historial, nombre);
    if (paciente == nullptr)
    {
        cout << "No se encontro un paciente atendido con ese nombre.\n";
        return;
    }

    cout << "\nPaciente encontrado:\nTurno: " << paciente->turno
         << "\nNombre: " << paciente->nombre << "\nEdad: " << paciente->edad
         << " años\nUrgencia: " << obtenerUrgencia(paciente->urgencia)
         << "\nEstado: " << paciente->estado
         << "\nFecha de atencion: " << paciente->fechaAtencion << '\n';
}

void ordenarPacientes(vector<Paciente>& historial, int criterio)
{
    for (size_t pasada = 0; pasada < historial.size(); ++pasada)
    {
        bool huboIntercambio = false;
        for (size_t i = 0; i + 1 < historial.size() - pasada; ++i)
        {
            bool debeIntercambiarse = criterio == 1
                ? historial[i].edad > historial[i + 1].edad
                : historial[i].fechaAtencion > historial[i + 1].fechaAtencion;
            if (debeIntercambiarse)
            {
                swap(historial[i], historial[i + 1]);
                huboIntercambio = true;
            }
        }
        if (!huboIntercambio)
            break;
    }
}

int contarMayoresDe60(const vector<Paciente>& historial, size_t indice = 0)
{
    if (indice >= historial.size())
        return 0;
    if (historial[indice].edad > 60)
        return 1 + contarMayoresDe60(historial, indice + 1);
    return contarMayoresDe60(historial, indice + 1);
}

int main()
{
    priority_queue<Paciente, vector<Paciente>, CompararPacientes> cola;
    vector<Paciente> historial;
    int siguienteTurno = 1;
    int opcion;

    do
    {
        cout << "\n\n============================================\n";
        cout << "        SISTEMA DE ATENCION MEDICA\n";
        cout << "                 DON FABIO\n";
        cout << "============================================\n";
        cout << "1. Registrar paciente\n2. Atender siguiente paciente\n";
        cout << "3. Mostrar pacientes en espera\n4. Mostrar historial de atencion\n";
        cout << "5. Buscar paciente atendido por nombre\n";
        cout << "6. Ordenar pacientes atendidos\n";
        cout << "7. Contar pacientes atendidos mayores de 60 años\n";
        cout << "8. Salir\nSeleccione una opcion: ";

        if (!(cin >> opcion))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opcion invalida.\n";
            continue;
        }

        switch (opcion)
        {
        case 1:
            registrarPaciente(cola, siguienteTurno);
            break;
        case 2:
            atenderPaciente(cola, historial);
            break;
        case 3:
            mostrarPacientesEnEspera(cola);
            break;
        case 4:
            mostrarHistorial(historial);
            break;
        case 5:
            buscarPaciente(historial);
            break;
        case 6:
            if (historial.empty())
            {
                cout << "No hay pacientes atendidos para ordenar.\n";
                break;
            }
            cout << "1. Por edad (menor a mayor)\n2. Por fecha (antigua a reciente)\n";
            cout << "Criterio: ";
            {
                int criterio;
                if (!(cin >> criterio) || (criterio != 1 && criterio != 2))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Criterio invalido.\n";
                    break;
                }
                ordenarPacientes(historial, criterio);
            }
            mostrarHistorial(historial);
            break;
        case 7:
            cout << "Pacientes atendidos mayores de 60 años: "
                 << contarMayoresDe60(historial) << '\n';
            break;
        case 8:
            cout << "Sistema cerrado correctamente. Gracias por utilizar el sistema de Don Fabio.\n";
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente.\n";
        }
    } while (opcion != 8);

    return 0;
}
