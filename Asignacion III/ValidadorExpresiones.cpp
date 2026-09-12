#include <iostream>
#include <stack>
#include <string>

using namespace std;

class ValidadorExpresiones
{
private:
    stack<char> pila;

public:
    bool esAbierto(char caracter)
    {
        return caracter == '(' ||
               caracter == '[' ||
               caracter == '{';
    }

    bool esCierre(char caracter)
    {
        return caracter == ')' ||
               caracter == ']' ||
               caracter == '}';
    }

    bool corresponde(char abierto, char cierre)
    {
        return (abierto == '(' && cierre == ')') ||
               (abierto == '[' && cierre == ']') ||
               (abierto == '{' && cierre == '}');
    }

    bool validar(string expresion)
    {
        while (!pila.empty())
        {
            pila.pop();
        }

        for (char caracter : expresion)
        {
            if (esAbierto(caracter))
            {
                pila.push(caracter);
            }
            else if (esCierre(caracter))
            {
                if (pila.empty())
                {
                    return false;
                }

                char abierto = pila.top();

                if (!corresponde(abierto, caracter))
                {
                    return false;
                }

                pila.pop();
            }
        }

        return pila.empty();
    }
};

int main()
{
    string expresion;

    cout << "Ingrese una expresion matematica: ";
    getline(cin, expresion);

    ValidadorExpresiones validador;

    if (validador.validar(expresion))
    {
        cout << "Expresion balanceada correctamente." << endl;
    }
    else
    {
        cout << "Error: parentesis desbalanceados." << endl;
    }

    return 0;
}
