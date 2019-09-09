#include "Matriz.h"

/**
 * 
 */
Matriz::Matriz() {
    this->matriz = new double*[LARGO];
    for (int i = 0; i < LARGO; i++) {
        this->matriz[i] = new double[LARGO];
        for (int j = 0; j < LARGO; j++) {
            // Inicializamos con valores que no sean cuadrados mágicos
            this->matriz[i][j] = (double) (i * j);
        }
    }
    calcularDeterminante();
}

/**
 * 
 * @param orig
 */
Matriz::Matriz(double** orig) {
    this->matriz = new double*[LARGO];
    for (int i = 0; i < LARGO; i++) {
        this->matriz[i] = new double[LARGO];
        for (int j = 0; j < LARGO; j++) {
            // Inicializamos con valores que no sean cuadrados mágicos
            this->matriz[i][j] = orig[i][j];
        }
    }
    calcularDeterminante();
}

/**
 * 
 * @param orig
 */
Matriz::Matriz(const std::string& orig) {
    try {
        this->matriz = new double*[LARGO];
        std::string linea(orig.c_str());
        if (!linea.empty()) {
            // Quitamos caracters innecesarios
            linea.erase(std::remove(linea.begin(), linea.end(), '['), linea.end());
            linea.erase(std::remove(linea.begin(), linea.end(), ']'), linea.end());

            // Obtenemos un token
            std::replace(linea.begin(), linea.end(), ';', ' ');


            std::vector<std::string> arreglo;
            std::stringstream ss(linea);
            std::string temp;
            while (ss >> temp) {
                arreglo.push_back(temp);
            }

            for (int i = 0; i < LARGO; i++) {
                std::string fila = arreglo[i];
                std::replace(fila.begin(), fila.end(), ',', ' ');

                std::vector<std::string> columnas;
                std::stringstream sf(fila);
                std::string tmp;
                while (sf >> tmp) {
                    columnas.push_back(tmp);
                }

                this->matriz[i] = new double[LARGO];
                for (int j = 0; j < LARGO; j++) {
                    std::string valor = columnas[j];
                    double numero = atof(valor.c_str());
                    this->matriz[i][j] = numero;
                }
            }
        }
    } catch (...) {
        Matriz();
    }
    calcularDeterminante();
}

/**
 * 
 * @param orig
 */
Matriz::Matriz(const Matriz& orig) {
    this->matriz = new double*[LARGO];
    for (int i = 0; i < LARGO; i++) {
        this->matriz[i] = new double[LARGO];
        for (int j = 0; j < LARGO; j++) {
            this->matriz[i][j] = orig.matriz[i][j];
        }
    }
    calcularDeterminante();
}

/**
 * 
 * @return 
 */
int Matriz::getDimension() {
    return LARGO;
}

/**
 * 
 * @return 
 */
double Matriz::getDeterminante() {
    return determinante;
}

/**
 * 
 */
Matriz::~Matriz() {
    delete matriz;
}

/**
 * 
 * @return 
 */
bool Matriz::esMagico() {
    bool ok = false;
    try {
        double fila1 = (this->matriz[0][0] + this->matriz[0][1] + this->matriz[0][2]);
        double fila2 = (this->matriz[1][0] + this->matriz[1][1] + this->matriz[1][2]);
        double fila3 = (this->matriz[2][0] + this->matriz[2][1] + this->matriz[2][2]);

        double columna1 = (this->matriz[0][0] + this->matriz[1][0] + this->matriz[2][0]);
        double columna2 = (this->matriz[0][1] + this->matriz[1][1] + this->matriz[2][1]);
        double columna3 = (this->matriz[0][2] + this->matriz[1][2] + this->matriz[2][2]);

        double diagonal1 = (this->matriz[0][0] + this->matriz[1][1] + this->matriz[2][2]);
        double diagonal2 = (this->matriz[0][2] + this->matriz[1][1] + this->matriz[2][0]);

        if ((fila1 == fila2) && (fila1 == fila3)) {
            if ((columna1 == columna2) && (columna1 == columna3)) {
                if (diagonal1 == diagonal2) {
                    ok = true;
                }
            }
        }
    } catch (...) {
        ok = false;
    }
    return ok;
}

/**
 * 
 * @return 
 */
std::string Matriz::toString() {
    std::stringstream ss;
    ss << '[' << this->matriz[0][0] << ',' << this->matriz[0][1] << ',' << this->matriz[0][2] << ';' << this->matriz[1][0] << ',' << this->matriz[1][1] << ',' << this->matriz[1][2] << ';' << this->matriz[2][0] << ',' << this->matriz[2][1] << ',' << this->matriz[2][2] << ']' << std::endl;
    return ss.str();
}

/**
 * 
 * @return 
 */
std::string Matriz::toWolframAlpha() {
    std::stringstream ss;
    ss << "{{" << this->matriz[0][0] << ',' << this->matriz[0][1] << ',' << this->matriz[0][2] << "},{" << this->matriz[1][0] << ',' << this->matriz[1][1] << ',' << this->matriz[1][2] << "},{" << this->matriz[2][0] << ',' << this->matriz[2][1] << ',' << this->matriz[2][2] << "}}" << std::endl;
    return ss.str();
}

/**
 * 
 * @return 
 */
std::string Matriz::mostrar() {
    std::stringstream ss;
    ss << "\t[" << this->matriz[0][0] << "\t | \t" << this->matriz[0][1] << "\t | \t" << this->matriz[0][2] << "\t]" << std::endl;
    ss << "\t[" << this->matriz[1][0] << "\t | \t" << this->matriz[1][1] << "\t | \t" << this->matriz[1][2] << "\t]" << std::endl;
    ss << "\t[" << this->matriz[2][0] << "\t | \t" << this->matriz[2][1] << "\t | \t" << this->matriz[2][2] << "\t]" << std::endl;
    return ss.str();
}

/**
 * 
 */
void Matriz::calcularDeterminante() {
    this->determinante = 0.0;
    if (LARGO == 3) {
        this->determinante = (this->matriz[0][0] * (this->matriz[1][1] * this->matriz[2][2] - this->matriz[2][1] * this->matriz[1][2])) -
                (this->matriz[0][1] * (this->matriz[1][0] * this->matriz[2][2] - this->matriz[1][2] * this->matriz[2][0])) +
                (this->matriz[0][2] * (this->matriz[1][0] * this->matriz[2][1] - this->matriz[1][1] * this->matriz[2][0]));
    }
}

/**
 * 
 * @return 
 */
Matriz Matriz::invertida() {
    double** inversa = new double*[LARGO];
    for (int i = 0; i < LARGO; i++) {
        inversa[i] = new double[LARGO];
        for (int j = 0; j < LARGO; j++) {
            inversa[i][j] = 0.0;
        }
    }

    if (determinante != 0.0) {
        double determinateInvertido = 1 / this->determinante;

        inversa[0][0] = (this->matriz[1][1] * this->matriz[2][2] - this->matriz[2][1] * this->matriz[1][2]) * determinateInvertido;
        inversa[0][1] = (this->matriz[0][2] * this->matriz[2][1] - this->matriz[0][1] * this->matriz[2][2]) * determinateInvertido;
        inversa[0][2] = (this->matriz[0][1] * this->matriz[1][2] - this->matriz[0][2] * this->matriz[1][1]) * determinateInvertido;
        inversa[1][0] = (this->matriz[1][2] * this->matriz[2][0] - this->matriz[1][0] * this->matriz[2][2]) * determinateInvertido;
        inversa[1][1] = (this->matriz[0][0] * this->matriz[2][2] - this->matriz[0][2] * this->matriz[2][0]) * determinateInvertido;
        inversa[1][2] = (this->matriz[1][0] * this->matriz[0][2] - this->matriz[0][0] * this->matriz[1][2]) * determinateInvertido;
        inversa[2][0] = (this->matriz[1][0] * this->matriz[2][1] - this->matriz[2][0] * this->matriz[1][1]) * determinateInvertido;
        inversa[2][1] = (this->matriz[2][0] * this->matriz[0][1] - this->matriz[0][0] * this->matriz[2][1]) * determinateInvertido;
        inversa[2][2] = (this->matriz[0][0] * this->matriz[1][1] - this->matriz[1][0] * this->matriz[0][1]) * determinateInvertido;
    }

    Matriz resultado(inversa);
    delete inversa;

    return resultado;
}
