#include "ModelARX.h"
#include <vector>
#include <cstdlib>
using namespace std;

ModelARX::ModelARX(const std::vector<double>& wspA, const std::vector<double>& wspB, int d, int poczatkowaHistoria)
    : wspolczynnikiA(wspA), wspolczynnikiB(wspB), opoznienieD(d) {
    if (d < 0) {
        throw std::invalid_argument("Opoznienie nie moze byc ujemne");
    }
    historiaWejsc.resize(poczatkowaHistoria, 0.0);
    historiaWyjsc.resize(poczatkowaHistoria, 0.0);
}


double ModelARX::symuluj(double wejscie) {
    historiaWejsc.push_back(wejscie);

    double wyjscie = 0.0;

    for (size_t i = 0; i < wspolczynnikiA.size(); ++i) {
        if (historiaWyjsc.size() > i) {
            wyjscie -= wspolczynnikiA[i] * historiaWyjsc[historiaWyjsc.size() - 1 - i];
        }
    }

    for (size_t i = 0; i < wspolczynnikiB.size(); ++i) {
        if (historiaWejsc.size() > opoznienieD + i) {
            wyjscie += wspolczynnikiB[i] * historiaWejsc[historiaWejsc.size() - 1 - opoznienieD - i];
        }
    }

    historiaWyjsc.push_back(wyjscie);
    return wyjscie;
}



