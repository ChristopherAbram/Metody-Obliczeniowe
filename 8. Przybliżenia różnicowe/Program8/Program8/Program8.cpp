#include<iostream>
#include<conio.h>
#include<cmath>
#include<windows.h>
#include<fstream>

#define PI 3.14159265358979323846

#include "Difference.h"

/**
Napisz program w j�zyku �C/C++�, obliczaj�cy przybli�one warto�ci pierwszych pochodnych
funkcji f(x) = cos(x) w punktach ko�cowych i �rodkowym przedzia�u [0, pi/2] zmiennej x. Zastosuj
wszystkie omawiane na wyk�adzie i na �wiczeniach przybli�enia r�nicowe dwupunktowe i
trzypunktowe (jednostronne b�d� centralne, w zale�no�ci od po�o�enia punktu w przedziale) na sieci
jednorodnej o kroku h. 

Wykonaj (na jednym rysunku) wykresy przedstawiaj�ce zale�no�ci b��d�w
bezwzgl�dnych przybli�e� r�nicowych od kroku sieci, pos�uguj�c si� skal� logarytmiczn� (tzn.
wykresy zale�no�ci log10|b��du| od log10 h ). Na podstawie wykres�w wyznacz do�wiadczalnie rz�dy
dok�adno�ci przybli�e� r�nicowych. Sprawd�, czy tak wyznaczone rz�dy dok�adno�ci pokrywaj�
si� z rz�dami teoretycznymi i wyja�nij ewentualne rozbie�no�ci. Ponadto zidentyfikuj warto�ci
kroku sieci poni�ej kt�rych pojawia si� wp�yw b��d�w maszynowych. Obliczenia powt�rz dla
dw�ch typ�w zmiennych rzeczywistych (float, i double) i por�wnaj wyniki.

Uwaga: najwygodniej jest zastosowa� wzorzec funkcji (function template) z typem zmiennych jako
parametrem wzorca.
*/

HANDLE  hConsole;

float f_float(float x) { return cos(x); }
float df_float(float x) { return -sin(x); }

double f_double(double x) { return cos(x); }
double df_double(double x) { return -sin(x); }

int main(int argc, char** argv) {

	using namespace std;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	try {
		/* FLoating point calculations */
		using type = float;

		type error;
		Difference<type> diff;
		diff.setFunction(f_float);

		ofstream out_file;
		out_file.open("results_float.dat", ofstream::out);

		if (out_file) {
			type begin = 10e-17f, end = 10e-2f;
			type x;

			/* For x = 0 */
			x = 0.f;
			// Forward difference two-points:
			for (type h = begin; h <= end; h *= 10.f) {
				diff.setIncrease(h);
				error = log10(abs(diff.forward(x) - df_float(x)));
				if(isfinite(error))
					out_file << log10(abs(h)) << " " << error << " ";
			}
			out_file << endl;
			// Forward difference three-points:
			for (type h = begin; h <= end; h *= 10.f) {
				diff.setIncrease(h);
				error = log10(abs(diff.forward(x, Difference<type>::Points::THREE) - df_float(x)));
				if (isfinite(error))
					out_file << log10(abs(h)) << " " << error << " ";
			}
			out_file << endl;



			/* For x = pi/4 */
			x = PI / 4.f;
			// Forward difference two-points:
			for (type h = begin; h <= end; h *= 10.f) {
				diff.setIncrease(h);
				error = log10(abs(diff.forward(x) - df_float(x)));
				if (isfinite(error))
					out_file << log10(abs(h)) << " " << error << " ";
			}
			out_file << endl;
			// Central difference two-points:
			for (type h = begin; h <= end; h *= 10.f) {
				diff.setIncrease(h);
				error = log10(abs(diff.central(x) - df_float(x)));
				if (isfinite(error))
					out_file << log10(abs(h)) << " " << error << " ";
			}
			out_file << endl;
			// Backward difference two-points:
			for (type h = begin; h <= end; h *= 10.f) {
				diff.setIncrease(h);
				error = log10(abs(diff.backward(x) - df_float(x)));
				if (isfinite(error))
					out_file << log10(abs(h)) << " " << error << " ";
			}
			out_file << endl;




			/* For x = pi/2 */
			x = PI / 2.f;
			// Backward difference two-points:
			for (type h = begin; h <= end; h *= 10.f) {
				diff.setIncrease(h);
				error = log10(abs(diff.backward(x) - df_float(x)));
				if (isfinite(error))
					out_file << log10(abs(h)) << " " << error << " ";
			}
			out_file << endl;
			// Backward difference three-points:
			for (type h = begin; h <= end; h *= 10.f) {
				diff.setIncrease(h);
				error = log10(abs(diff.backward(x, Difference<type>::Points::THREE) - df_float(x)));
				if (isfinite(error))
					out_file << log10(abs(h)) << " " << error << " ";
			}
			out_file << endl;

			out_file.close();
		}
	}
	catch (DifferenceException& de) {
		cout << "FLOAT: " << de.what() << endl;
	}



	try {
		/* Double point calculations */
		using type = double;

		type error;
		Difference<type> diff;
		diff.setFunction(f_double);

		ofstream out_file;
		out_file.open("results_double.dat", ofstream::out);

		if (out_file) {
			type begin = 10.e-17, end = 10.e-2;
			type x;

			/* For x = 0 */
			x = 0.;
			// Forward difference two-points:
			for (type h = begin; h <= end; h *= 10.) {
				diff.setIncrease(h);
				error = log10(abs(diff.forward(x) - df_float(x)));
				if (isfinite(error))
					out_file << log10(abs(h)) << " " << error << " ";
			}
			out_file << endl;
			// Forward difference three-points:
			for (type h = begin; h <= end; h *= 10.) {
				diff.setIncrease(h);
				error = log10(abs(diff.forward(x, Difference<type>::Points::THREE) - df_float(x)));
				if (isfinite(error))
					out_file << log10(abs(h)) << " " << error << " ";
			}
			out_file << endl;



			/* For x = pi/4 */
			x = PI / 4.;
			// Forward difference two-points:
			for (type h = begin; h <= end; h *= 10.) {
				diff.setIncrease(h);
				error = log10(abs(diff.forward(x) - df_float(x)));
				if (isfinite(error))
					out_file << log10(abs(h)) << " " << error << " ";
			}
			out_file << endl;
			// Central difference two-points:
			for (type h = begin; h <= end; h *= 10.) {
				diff.setIncrease(h);
				error = log10(abs(diff.central(x) - df_float(x)));
				if (isfinite(error))
					out_file << log10(abs(h)) << " " << error << " ";
			}
			out_file << endl;
			// Backward difference two-points:
			for (type h = begin; h <= end; h *= 10.) {
				diff.setIncrease(h);
				error = log10(abs(diff.backward(x) - df_float(x)));
				if (isfinite(error))
					out_file << log10(abs(h)) << " " << error << " ";
			}
			out_file << endl;



			/* For x = pi/2 */
			x = PI / 2.;
			// Backward difference two-points:
			for (type h = begin; h <= end; h *= 10.) {
				diff.setIncrease(h);
				error = log10(abs(diff.backward(x) - df_float(x)));
				if (isfinite(error))
					out_file << log10(abs(h)) << " " << error << " ";
			}
			out_file << endl;
			// Backward difference three-points:
			for (type h = begin; h <= end; h *= 10.) {
				diff.setIncrease(h);
				error = log10(abs(diff.backward(x, Difference<type>::Points::THREE) - df_float(x)));
				if (isfinite(error))
					out_file << log10(abs(h)) << " " << error << " ";
			}
			out_file << endl;

			out_file.close();
		}
	}
	catch (DifferenceException& de) {
		cout << "Double: " << de.what() << endl;
	}

	cout << endl << endl << "Press any button to finish...";
	_getch();
	return EXIT_SUCCESS;
}// end main