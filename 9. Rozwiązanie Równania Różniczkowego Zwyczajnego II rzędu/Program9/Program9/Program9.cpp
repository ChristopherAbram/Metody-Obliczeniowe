#include<iostream>
#include <conio.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include<fstream>
#include<string>

#include "SolvingLinearSystem.h"

/* Napisz program w j�zyku �C/C++�, rozwi�zuj�cy r�wnanie r�niczkowe zwyczajne drugiego rz�du:
U''(x) + U(x) + 2sin(x) = 0, okre�lone na przedziale 0 <= x <= pi/2,
z warunkami brzegowymi U(0) = 0, U(pi/2) = 0. Zastosuj typ double oraz trzypunktow�
dyskretyzacj� konwencjonaln� oraz dyskretyzacj� Numerowa na sieci jednorodnej. Do rozwi�zania
uk�adu liniowych r�wna� algebraicznych zastosuj algorytm Thomasa (patrz zaj�cia nr 6). Wykonaj
rusynek przedstawiaj�cy por�wnanie uzyskanych wynik�w numerycznych z rozwi�zaniem
analitycznym U(x) = xcos(x) . Poka�, �e rz�d dok�adno�ci
rozwi�za� numerycznych jest zgodny z przewidywaniami teoretycznymi wynikaj�cymi z zadania 2.
W tym celu wykonaj (na jednym rysunku) wykresy przedstawiaj�ce zale�no�ci maksymalnego b��du
bezwzgl�dnego rozwi�za� od kroku sieci h, pos�uguj�c si� skal� logarytmiczn� (tzn. wykresy
zale�no�ci log10|b��du| od log10 h ). Na podstawie wykres�w wyznacz do�wiadczalnie rz�dy
dok�adno�ci rozwi�za� uzyskanych za pomoc� r�nych metod, i por�wnaj je z rz�dami
teoretycznymi. Ponadto zidentyfikuj warto�ci kroku sieci poni�ej kt�rych pojawia si� wp�yw b��d�w
maszynowych.
*/

using type = double;
using type_pointer = type*;




type p(type x) { return 1.; }
type q(type x) { return 0.; }
type r(type x) { return 1.; }
type s(type x) { return (2.*sin(x)); }
type U(type x) { return (x*cos(x)); }



type error(type yi, type y) { return abs(yi - y); }
bool S(type x, type s) { return ((x >= (s - 10.e-16)) && (x <= (s + 10.e-16))); }





int main(int argc, char** argv) {

	using namespace std;

	// Przedzia� [0, pi/2]:
	type a_ = 0., _b = M_PI_2;


	// Warunki brzegowe:
	type alfa = 0., fi = 0., beta = 1., psi = 1., gamma = 0., theta = 0.;


	// Siatka:
	type h_step = 0.05;
	type h_ = 10.e-6, _h = 10.e-2, _h_ = pow(10., h_step);
	__int64 N;

	// Trzypunktowa dyskretyzacja:
	type_pointer l, d, u, b;


	__int64 max_size = (__int64)((_b - a_) / h_);
	char file_name[32];
	ofstream error_three, error_numerow;
	error_three.open("errors_three.dat", ofstream::out);
	error_numerow.open("errors_numerow.dat", ofstream::out);


	if (error_three && error_numerow) {
		int i = 0;
		for (__int64 N = 5; N < (_b - a_) / h_; N += 100){

			type h = (_b - a_) / (N - 1);

			std::cout << "Obliczenia dla h: " << h << "  Wektor o rozmiarze: " << N + 1 << endl;

			// Warunek do zapisywwania wynik�w (tylko wyniki dla poszczeg�lnych h):
			bool cond = N == 5 || N == 105 || N == 1005;

			// Inicjalizacja wektor�w dla kolejnych punkt�w siatki do algorytmu Thomas'a:
			type_pointer l = new type[N];
			type_pointer d = new type[N];
			type_pointer u = new type[N];
			type_pointer b = new type[N];

			d[0] = beta - alfa / h;
			u[0] = alfa / h;
			b[0] = -gamma;

			type xi = a_;
			for (__int64 k = 1; k < N - 1; ++k) {
				xi += h;

				l[k - 1] = p(xi)/(h*h) - q(xi)/(2.*h);
				d[k] = (-2.*p(xi))/(h*h) + r(xi);
				u[k] = p(xi)/(h*h) + q(xi)/(2.*h);
				b[k] = -s(xi);
			}
			l[N - 2] = (-fi / h);
			d[N - 1] = (-fi / h + psi);
			b[N - 1] = (-theta);

			// Rozwi�zanie uk�adu algorytmem Thomas'a:
			SLS<type> solver(l, d, u, N);
			solver.setb(b).solveThomas();
			b = solver.getSolutions();

			// Zapisywanie b��d�w:
			type max_err = -1.;
			type tmp = 0.;
			xi = a_;
			for (__int64 k = 0; k < N; k++) {
				tmp = error(b[k], U(xi));
				if (tmp > max_err)
					max_err = tmp;
				xi += h;
			}
			error_three << log10(h) << " " << log10(max_err) << " ";

			// Zapisywanie wynik�w w formacie: (x0 y0 x1 y1 ... xi yi ... xn yn):
			if (cond) {
				memset((void*)file_name, 0, 32);
				sprintf_s(file_name, 32, "results_three%d.dat", i);

				ofstream file;
				file.open(file_name, ofstream::out);

				if (file) {
					int j = 0;
					for (type xi = a_; xi <= _b; xi += h, ++j)
						if (j < N)
							file << xi << " " << b[j] << " ";
					file.close();
				}
				++i;
			}

			// Czyszczenie wektor�w:
			delete[] l;
			delete[] d;
			delete[] u;
			delete[] b;
		}
		error_three.close();


		

		cout << "Numerow:" << endl;
		i = 0;
		for (__int64 N = 5; N < (_b - a_) / h_; N += 100) {

			type h = (_b - a_) / (N - 1);

			//__int64 N = (_b - a_)/h;
			std::cout << "Obliczenia dla h: " << h << "  Wektor o rozmiarze: " << N + 1 << endl;

			// Warunek do zapisywwania wynik�w (tylko wyniki dla poszczeg�lnych h):
			bool cond = N == 5 || N == 105 || N == 1005;

			// Inicjalizacja wektor�w dla kolejnych punkt�w siatki do algorytmu Thomas'a:
			type_pointer l = new type[N];
			type_pointer d = new type[N];
			type_pointer u = new type[N];
			type_pointer b = new type[N];

			d[0] = beta - alfa / h;
			u[0] = alfa / h;
			b[0] = -gamma;

			type xi = a_;
			for (__int64 k = 1; k < N - 1; ++k) {
				xi += h;

				l[k - 1] = p(xi) / (h*h) + 1./12.;
				d[k] = (-2.*p(xi)) / (h*h) + r(xi) * 10./12.;
				u[k] = p(xi) / (h*h) + 1./12.;
				b[k] = -(s(xi - h) + 10.*s(xi) + s(xi + h))/12.;
			}
			l[N - 2] = (-fi / h);
			d[N - 1] = (-fi / h + psi);
			b[N - 1] = (-theta);

			// Rozwi�zanie uk�adu algorytmem Thomas'a:
			SLS<type> solver(l, d, u, N);
			solver.setb(b).solveThomas();
			b = solver.getSolutions();

			// Zapisywanie b��d�w:
			type max_err = -1.;
			type tmp = 0.;
			xi = a_;
			for (__int64 k = 0; k < N; k++) {
				tmp = error(b[k], U(xi));
				if (tmp > max_err)
					max_err = tmp;
				xi += h;
			}
			error_numerow << log10(h) << " " << log10(max_err) << " ";

			// Zapisywanie wynik�w w formacie: (x0 y0 x1 y1 ... xi yi ... xn yn):
			if (cond) {
				memset((void*)file_name, 0, 32);
				sprintf_s(file_name, 32, "results_numerow%d.dat", i);

				ofstream file;
				file.open(file_name, ofstream::out);

				if (file) {
					int j = 0;
					for (type xi = a_; xi <= _b; xi += h, ++j)
						if (j < N)
							file << xi << " " << b[j] << " ";
					file.close();
				}
				++i;
			}

			// Czyszczenie wektor�w:
			delete[] l;
			delete[] d;
			delete[] u;
			delete[] b;
		}
		error_numerow.close();
	}

	cout << "Press any button to finish...";
	_getch();
	return EXIT_SUCCESS;
}// end main