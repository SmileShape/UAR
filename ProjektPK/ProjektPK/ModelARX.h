

#ifndef UNTITLED3_MODELARX_H
#define UNTITLED3_MODELARX_H

#include <vector>
#include <stdexcept>
using namespace std;

class ModelARX {
private:
    std::vector<double> wspolczynnikiA;
    std::vector<double> wspolczynnikiB;
    int opoznienieD;
    std::vector<double> historiaWejsc;
    std::vector<double> historiaWyjsc;

public:
    ModelARX(const std::vector<double>& wspA, const std::vector<double>& wspB, int d, int poczatkowaHistoria = 100);

    double symuluj(double wejscie);
};






#endif
