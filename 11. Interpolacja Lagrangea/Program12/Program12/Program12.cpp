#include<iostream>
#include <conio.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<fstream>

/* Napisz program w j�zyku �C/C++�, demonstruj�cy zjawisko Rungego w interpolacji wielomianowej Lagrange�a, 
na przyk�adzie interpolacji funkcji f(x) = x/(1 + 25|x|^3), okre�lonej w przedziale [-1, 1]. 
Por�wnaj wyniki interpolacji na w�z�ach r�wnoodleg�ych z wynikami interpolacji na w�z�ach Czebyszewa.*/

using type = double;

type f(type x) { return (x / (1. + (25. * x*x*abs(x)))); }

type lagrange(type* x, type* y, long n, type a) {
	type Y = 0.;
	type li;

	for(long i = 0; i < n; i++) {
		li = 1.;
		for (long j = 0; j < n; j++)
			if (j != i)
				li = li * ((a - x[j]) / (x[i] - x[j]));
		Y += li * y[i];
	}

	return Y;
}// end lagrange


int main(int argc, char** argv) {
	
	using namespace std;

	// Parametry zadania:
	type a, b, h, ksi;		// okre�lenie przedzia�u
	type step, x, y;		// g�sto�� interpolacji
	long N;					// liczba w�z��w
	int j;
	type *xi, *yi;			// w�z�y
	char fn1[32], fn2[32];	// nazwy plik�w
	fstream file1, file2;	// pliki z wynikami

	a = -1.;
	b = 1.;
	step = 1.e-3;
	j = 0;

	// Dla jakiej liczby w�z��w generowa� wyniki:
	long arr[10] = {4, 6, 10, 12, 14, 16, 20, 50, 100, 300};

	for (long k = 0; k < 10; k++) {
		N = arr[k]; // liczba w�z��w

		xi = new type[N];
		yi = new type[N];

		cout << "Przedzial: [" << a << ", " << b << "]," << endl
			<< "Gestosc interpolacji: " << step << "," << endl
			<< "Liczba wezlow: " << N << endl;

		// Generowanie w�z��w r�wnoodleg�ych:
		h = (b - a) / ((type)N - 1.);
		for (long i = 0; i < N; ++i) {
			xi[i] = a + i * h;
			yi[i] = f(xi[i]);
		}

		// Interpolacja Lagrange'a dla w�z��w r�wnoodleg�ych w przedziale [-1, 1]:
		memset((void*)fn1, 0, 32);
		sprintf_s(fn1, 32, "r_%d.dat", j);

		file1.open(fn1, fstream::out);
		if (file1) {
			x = a;
			while (x <= (b + step)) {
				// Interpolacja:
				y = lagrange(xi, yi, N, x);

				// Zapis wyniku:
				file1 << x << " " << y << " ";

				x += step;
			}
			file1.close();
		}

		// Generowanie w�z��w Czebyszewa:
		for (long i = 0; i < N; ++i) {
			ksi = cos(((type)(2 * i + 1)) / ((type)(2 * N + 2)) * M_PI);
			xi[i] = (type)(b + a) / 2. - (type)(b - a) / 2. * ksi;
			yi[i] = f(xi[i]);
		}

		// Interpolacja Lagrange'a dla w�z��w Czebyszewa w przedziale [-1, 1]:
		memset((void*)fn2, 0, 32);
		sprintf_s(fn2, 32, "c_%d.dat", j);

		file2.open(fn2, fstream::out);
		if (file2) {
			x = a;
			while (x <= (b + step)) {
				// Interpolacja:
				y = lagrange(xi, yi, N, x);

				// Zapis wyniku:
				file2 << x << " " << y << " ";

				x += step;
			}
			file2.close();
		}

		++j;
		delete[] xi;
		delete[] yi;
	}

	cout << "Press any button to finish...";
	_getch();
	return EXIT_SUCCESS;
}// end main