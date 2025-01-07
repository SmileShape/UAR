
#include "PID.h"




RegulatorPID::RegulatorPID(double wP, double wC, double wR) : wspolczynnikProporcjonalny(wP), wspolczynnikCalkujacy(wC), wspolczynnikRozniczkujacy(wR),
bladPoprzedniejIteracji(0),
sumaBledowDoSkladnikaCalkujacego(0),
aktualnySygnalSterujacy(0) {
    bladPoprzedniejIteracji = 0;
    sumaBledowDoSkladnikaCalkujacego = 0;
}

double RegulatorPID::obliczanieSygnalySterujacego(double wartoscZadana, double wartoscRzeczywistaProcesu, double roznicaCzasu)
{
    double skladnikRozniczkujacy;

    double blad = wartoscZadana - wartoscRzeczywistaProcesu;
    double skladnikProporcjonalny = wspolczynnikProporcjonalny * blad;
    sumaBledowDoSkladnikaCalkujacego += blad * roznicaCzasu;

    double skladnikCalkujacy = wspolczynnikCalkujacy * sumaBledowDoSkladnikaCalkujacego;

    if (roznicaCzasu <= 0) {
        skladnikRozniczkujacy = 0;
    }
    else {
        skladnikRozniczkujacy = wspolczynnikRozniczkujacy * (blad - bladPoprzedniejIteracji) / roznicaCzasu;
    }
    double sygnalSterujacy = skladnikCalkujacy + skladnikProporcjonalny + skladnikRozniczkujacy;
    bladPoprzedniejIteracji = blad;
    return sygnalSterujacy;
}


void RegulatorPID::zmianaNastawRegulator(double wP, double wC, double wR) {
    wspolczynnikProporcjonalny = wP;
    wspolczynnikCalkujacy = wC;
    wspolczynnikRozniczkujacy = wR;

}


void RegulatorPID::resetowaniePamieciRegulatora() {
    sumaBledowDoSkladnikaCalkujacego = 0;
    bladPoprzedniejIteracji = 0;
}


double RegulatorPID::symuluj(double wartoscWe) {
    double blad = wartoscWe;
    sumaBledowDoSkladnikaCalkujacego += blad;

    double skladnikP = wspolczynnikProporcjonalny * blad;
    double skladnikI = (wspolczynnikCalkujacy > 0) ? (1.0 / wspolczynnikCalkujacy) * sumaBledowDoSkladnikaCalkujacego : 0.0;
    double skladnikD = (wspolczynnikRozniczkujacy > 0) ? wspolczynnikRozniczkujacy * (blad - bladPoprzedniejIteracji) : 0.0;
    aktualnySygnalSterujacy = skladnikP + skladnikI + skladnikD;
    bladPoprzedniejIteracji = blad;

    return aktualnySygnalSterujacy;

}