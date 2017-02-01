#include<iostream>
#include<conio.h>

#include "SolvingLinearSystem.h"

/*
Napisz program w j�zyku �C/C++�, realizuj�cy algorytm Thomasa dla macierzy tr�j-diagonalnej o
dowolnych rozmiarach N x N, a nast�pnie zastosuj ten program do rozwi�zania uk�adu r�wna�
Ax = b, w kt�rym

Macierz A:
	10   1/2
	1/3  20   1/4
	     1/5  30   1/6
	          1/7  30   1/8
	               1/9  20    1/10
					    1/11  10
Macierz b:
	31
	165/4
	917/30
	851/28
	3637/90
	332/11

Program nale�y zrealizowa� w postaci dw�ch oddzielnych funkcji: jednej, kt�ra korzysta wy��cznie
z danych dotycz�cych macierzy A, oraz drugiej, kt�ra korzysta z wektora b oraz wynik�w dzia�ania
pierwszej funkcji dla macierzy A. */

int main(int argc, char** argv) {

	using namespace std;
	using type = double;

	/* Diagonal vectors */
	vector<type> L{1./3., 1./5., 1./7., 1./9., 1./11.};
	vector<type> D{10., 20., 30., 30., 20., 10.};
	vector<type> U{1./2., 1./4., 1./6., 1./8., 1./10. };

	vector<type> b = {
		31.,
		165./4.,
		917./30.,
		851./28.,
		3637./90.,
		332./11.
	};

	/* Solving linear system */
	SLS<type> solver(L, D, U);
	b = solver.setb(b).solveThomas().getSolutions();

	/* Presentation of results */
	cout << endl << "Solutions of the system Ax = b:" << endl;
	for (long i = 0; i < b.size(); ++i) {
		cout.precision(6);
		cout << " x" << i + 1 << " = " << b[i] << endl;
	}

	cout << endl << endl << "Press any button to close...";
	_getch();
	return EXIT_SUCCESS;
}// end main