#ifndef MATRIZ_H
#define MATRIZ_H

#define LARGO 3

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

class Matriz {
public:
    Matriz();
    Matriz(double** orig);
    Matriz(const std::string& orig);
    Matriz(const Matriz& orig);
    int getDimension();
    double getDeterminante();
    virtual ~Matriz();

    bool esMagico();
    std::string toString();
    std::string toWolframAlpha();
    std::string mostrar();
    Matriz invertida();
    Matriz invertir();
private:
    double determinante;
    double** matriz;
    void calcularDeterminante();
};

#endif /* MATRIZ_H */

