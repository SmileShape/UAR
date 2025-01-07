#include "SkokJednostkowy.h"

double SkokJednostkowy::skokJednostkowy(int czas, int chwilaAktywacji, double A) {

    if (czas >= chwilaAktywacji)
        return A;
    else
        return 0;
}