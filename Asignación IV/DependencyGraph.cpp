#include "DependencyGraph.h"

void GrafoDependencias::agregarDependencia(const string& modulo, const string& dependencia)
{
    dependencias[modulo].push_back(dependencia);

    if (dependencias.find(dependencia) == dependencias.end())
    {
        dependencias[dependencia] = vector<string>();
    }
}

void GrafoDependencias::dfsOrdenCarga(const string& modulo,
                                      unordered_map<string, bool>& visitados,
                                      vector<string>& orden)
{
    visitados[modulo] = true;

    for (const string& dependencia : dependencias[modulo])
    {
        if (!visitados[dependencia])
        {
            dfsOrdenCarga(dependencia, visitados, orden);
        }
    }

    orden.push_back(modulo);
}

vector<string> GrafoDependencias::obtenerOrdenCarga()
{
    unordered_map<string, bool> visitados;
    vector<string> orden;

    for (const auto& elemento : dependencias)
    {
        if (!visitados[elemento.first])
        {
            dfsOrdenCarga(elemento.first, visitados, orden);
        }
    }

    return orden;
}

bool GrafoDependencias::dfsCiclo(const string& modulo, unordered_map<string, int>& estado)
{
    estado[modulo] = 1;

    for (const string& dependencia : dependencias[modulo])
    {
        if (estado[dependencia] == 1)
        {
            return true;
        }

        if (estado[dependencia] == 0 && dfsCiclo(dependencia, estado))
        {
            return true;
        }
    }

    estado[modulo] = 2;
    return false;
}

bool GrafoDependencias::tieneCiclo()
{
    unordered_map<string, int> estado;

    for (const auto& elemento : dependencias)
    {
        if (estado[elemento.first] == 0 && dfsCiclo(elemento.first, estado))
        {
            return true;
        }
    }

    return false;
}
