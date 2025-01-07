#include "sygnalSinusoidalny.h"
#include <cmath>


double sygnalSinusoidalny(int czas, double okres, double amplituda)
{
	const double PI = 3.14159265;
	double sygnal;


		sygnal = amplituda * sin((czas % static_cast<int>(okres)) * (2 * PI / okres));
	
	return sygnal;
}