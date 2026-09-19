#ifndef DEPENDENCYGRAPH_H
#define DEPENDENCYGRAPH_H

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class GrafoDependencias
{
private:
    unordered_map<string, vector<string>> dependencias;

    void dfsOrdenCarga(const string& modulo, unordered_map<string, bool>& visitados,
                       vector<string>& orden);
    bool dfsCiclo(const string& modulo, unordered_map<string, int>& estado);

public:
    void agregarDependencia(const string& modulo, const string& dependencia);
    vector<string> obtenerOrdenCarga();
    bool tieneCiclo();
};

#endif
