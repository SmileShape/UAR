
#ifndef PID_PID_H
#define PID_PID_H

class RegulatorPID {
private:
    double wspolczynnikProporcjonalny;
    double wspolczynnikCalkujacy;
    double wspolczynnikRozniczkujacy;

    double bladPoprzedniejIteracji;
    double sumaBledowDoSkladnikaCalkujacego;
    double aktualnySygnalSterujacy;

public:
    RegulatorPID(double wP, double wC = 0.0, double wR = 0.0);
    double obliczanieSygnalySterujacego(double wartoscZadana, double wartoscRzeczywistaProcesu, double roznicaCzasu);
    void zmianaNastawRegulator(double wP, double wC, double wR);
    void resetowaniePamieciRegulatora();
    double symuluj(double wartoscWe);

};

#endif 
