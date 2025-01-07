#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "PID.h"
#include "TestyPID.h"
#include "ModelARX.h"
#include "Testy.h"

using namespace std;

void uruchamianieSymulacjiARX();
void uruchamianieRegulatoraPID();
void uruchamianiePetliSprzezeniaZwrotnego();


int main() {
    int wybor = -1;

    while (wybor != 0) {
        cout << "\n=== Menu ===\n";
        cout << "1. Uruchom symulacje Model ARX" << endl;;
        cout << "2. Uruchom regulator PID" << endl;
        cout << "3. Uruchom petle sprzezenia zwrotnego" << endl;
        cout << "0. Wyjscie" << endl;;
        cout << "Wybierz opcje: ";
        cin >> wybor;

        switch (wybor) {
        case 1:
            uruchamianieSymulacjiARX();
            break;
        case 2:
            uruchamianieRegulatoraPID();
            break;
        case 3:
            uruchamianiePetliSprzezeniaZwrotnego();
        case 0:
            cout << "Koniec programu." << endl;;
            break;
        default:
            cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;;
        }
    }

    return 0;
}

void uruchamianieSymulacjiARX() {
    srand(static_cast<unsigned int>(time(NULL)));

    double wspolczynnikA, wspolczynnikB;
    int opoznienieD;
    int zakresCzasu = -1;
    double rozdzielczoscCzasu = -1;

    cout << "Podaj wspolczynnik A: ";
    cin >> wspolczynnikA;

    cout << "Podaj wspolczynnik B: ";
    cin >> wspolczynnikB;

    cout << "Podaj opoznienie D: ";
    cin >> opoznienieD;

    while (zakresCzasu <= 0) {
        cout << "Podaj zakres czasu (musi być wiekszy od 0): ";
        cin >> zakresCzasu;
    }

    while (rozdzielczoscCzasu <= 0) {
        cout << "Podaj rozdzielczosc czasu (musi byc wieksza od 0): ";
        cin >> rozdzielczoscCzasu;
    }

    ModelARX model({ static_cast<double>(wspolczynnikA) },
        { static_cast<double>(wspolczynnikB) },
        opoznienieD);

    vector<double> wyniki;
    vector<double> przechowywanieWartosciCzasu;

    for (double t = 0; t <= zakresCzasu; t += rozdzielczoscCzasu) {
        double wejscie = (rand() / static_cast<double>(RAND_MAX)) * 2.0 - 1.0;
        wyniki.push_back(model.symuluj(wejscie));
        przechowywanieWartosciCzasu.push_back(t);
    }

    cout << "\nWyniki symulacji:\n";
    for (size_t i = 0; i < wyniki.size(); ++i) {
        cout << "Czas t = " << przechowywanieWartosciCzasu[i]
            << ", y(t) = " << wyniki[i] << endl;
    }
}

void uruchamianieRegulatoraPID() {
    double wartoscZadana, wartoscRzeczywista, roznicaCzasu = 1.0;
    double sygnalSterujacy;

    cout << "Podaj wartosc zadana: ";
    cin >> wartoscZadana;

    cout << "Podaj wartosc rzeczywista: ";
    cin >> wartoscRzeczywista;

    RegulatorPID regulator(1.0, 2.0, 3.0);
    sygnalSterujacy = regulator.obliczanieSygnalySterujacego(wartoscZadana, wartoscRzeczywista, roznicaCzasu);

    cout << "Sygnal sterujacy: " << sygnalSterujacy << endl;

    double kp, ki, kd;
    cout << "Podaj nowe nastawy regulatora (Kp, Ki, Kd): ";
    cin >> kp >> ki >> kd;
    regulator.zmianaNastawRegulator(kp, ki, kd);
    cout << "Nastawy regulatora zmienione." << endl;
}

void uruchamianiePetliSprzezeniaZwrotnego() {
    double wspolczynnikA, wspolczynnikB;
    int opoznienieD;
    double setpoint;
    cout << "Podaj setpointa (double): ";
    cin >> setpoint;


    cout << "Podaj wspolczynnik A: ";
    cin >> wspolczynnikA;

    cout << "Podaj wspolczynnik B: ";
    cin >> wspolczynnikB;

    cout << "Podaj opoznienie D: ";
    cin >> opoznienieD;

    vector<double> wspA = { wspolczynnikA };
    vector<double> wspB = { wspolczynnikB };


    ModelARX model(wspA, wspB, opoznienieD);

    double wspolczynnikProporcjonalny;
    double wspolczynnikCalkujacy;
    double wspolczynnikRozniczkujacy;

    cout << "\nTeraz tworzymy objekt PID\n";
    cout << "Podaj wpolczynnik proporcjonalny: ";
    cin >> wspolczynnikProporcjonalny;
    cout << "Podaj wspolczynnik calkujacy: ";
    cin >> wspolczynnikCalkujacy;
    cout << " Podaj wspolczynnik rozniczkujacy:";
    cin >> wspolczynnikRozniczkujacy;

    RegulatorPID regulator(wspolczynnikProporcjonalny, wspolczynnikCalkujacy, wspolczynnikRozniczkujacy);


    double aktualnaWartosc = 0.0;
    double interwalCzasowy = 0.1;
    int maksymalnyCzas = 100;
    int liczbaIteracji = static_cast<int>(maksymalnyCzas / interwalCzasowy);

    for (int i = 0; i < liczbaIteracji; i++) {
        double aktualnyCzas = i * interwalCzasowy;
        double blad = setpoint - aktualnaWartosc;
        double sygnalSterujacy = regulator.obliczanieSygnalySterujacego(blad, aktualnaWartosc, interwalCzasowy);
        aktualnaWartosc = model.symuluj(sygnalSterujacy);

        cout << "\nCzas: " << aktualnyCzas << " s, " << endl;
        cout << "Blad: " << blad << endl;
        cout << "Sygnal sterujacy: " << sygnalSterujacy << endl;
        cout << "aktuana wartosc: " << aktualnaWartosc << endl;

        if (fabs(blad) < 0.01) {
            cout << "Blad jest wystarczajaco maly. Koniec symulacji." << endl;
            cout << "Symulacja zatrzymana po " << aktualnyCzas << " sekundach." << " Ostateczny blad: " << blad << endl;

            break;
        }
    }
}