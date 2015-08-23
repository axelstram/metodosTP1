#include "Mat.h"
#include "aux.h"
#include <string>
#include <fstream>

#define EG_METHOD 0
#define LU_METHOD 1


double ri;
double re;
int m;
int n;
double iso;
int ninst;


/*  

La primera lınea contendra los valores r i , r e , m + 1, n, iso, ninst, donde iso representa el valor
de la isoterma buscada y ninst es la cantidad de instancias del problema a resolver para los
parametros dados.
A continuacion, el archivo contendra ninst lıneas, cada una de ellas con 2n valores, los primeros
n indicando los valores de la temperatura en la pared interna, i.e., T i (θ 0 ), T i (θ 1 ), . . . , T i (θ n−1 ),
seguidos de n valores de la temperatura en la pared externa, i.e., T e (θ 0 ),Te (θ 1 ),. . . ,T e (θ n−1 ).

*/


int main(int argc, char* argv[])
{
	/*
	string input_file_path = argv[1];
	string output_file_path = argv[2];
	int method = stoi(argv[3]);

	//Load input parameters
	ifstream input_file(input_file_path);
	ofstream output_file(output_file_path);
	string s;


	input_file >> s;
	re = stod(s);
	input_file >> s;
	ri = stod(s);
	input_file >> s;
	m = stoi(s) - 1; // lee m + 1 
	input_file >> s;
	n = stoi(s);
	input_file >> s;
	iso = stod(s);
	input_file >> s;
	ninst = stoi(s);

//cout << " r_e: " << re << "\n r_i: " << ri << "\n m: " << m << "\n n: " << n << "\n iso: " << iso << "\n ninst: " << ninst << endl;
	double delta_r = (re-ri)/(double)m;
	double delta_theta = 360.0/(double)n;

	Mat A(n*m, n*m); //crea una matriz de n*m x n*m
	Mat b(n*m, 1);
	
	LoadMatrix(A,delta_r, delta_theta, ri, n, m); //delta_r * j + ri
*/
	//PRUEBA NUESTRA

	int tam = 3;

	Mat A(tam, tam);
	Mat b(tam, 1);
	LoadMatrixFromFile(A, b, "prueba");

	cout << "A" << endl;
	A.Show();
	cout << endl << "b" << endl;
	b.Show();
	cout << endl;

	Mat LU(tam, tam);


	GetLU(A, LU);

	cout << endl << "LU:" << endl;
	LU.Show();

	Mat X = LUElimination(LU, b);
	cout << endl << "X:" << endl;
	X.Show();

	/*
	Mat X2 = GaussianElimination(A, b);
	cout << endl;
	cout << "X con gauss" << endl;
	X2.Show();
	*/

	/*
	if (method == EG_METHOD) {		
		for (int i = 0; i < ninst; i++) {
			LoadInstanceOfB(input_file, n*m, n, b);	
			Mat X = GaussianElimination(A, b);
			cout << "A:" << endl;
			A.Show();
			cout << "X:" << endl;
			X.Show();
		}
	} else {
		Mat L(n*m, n*m);
		Mat U(n*m, n*m);

		GetLU(A, L, U);

		for (int i = 0; i < ninst; i++) {
			LoadInstanceOfB(input_file, n*m, n, b);

			LUElimination(L, U, b);
		}
	}
	
	*/	
}
