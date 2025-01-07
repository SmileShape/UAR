#include "sygnalProstokatny.h"

double sygnalProstokatny(int czas, double okres, double wypelnienie, double amplituda)
{
	double sygnal;
	
		if ((czas % static_cast<int>(okres)) < static_cast<int>(wypelnienie * okres)) {
			sygnal = amplituda;
		}
		else {
			sygnal = 0.0;
		}

	return sygnal;
}