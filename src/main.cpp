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
void prueba(){

	//PRUEBA NUESTRA

	int tam = 3;

	Mat A(tam, tam);
	Mat b(tam, 1);
	LoadMatrixFromFile(A, b, "./tests/nuestros/test1_3x3");

	cout << "A" << endl;
	A.Show();
	cout << endl << "b" << endl;
	b.Show();
	cout << endl;

	/*
	Mat X2 = GaussianElimination(A, b);
	cout << endl;
	cout << "X con gauss" << endl;
	X2.Show();
	*/

	//Mat LU(tam, tam);
/*
	GetLU(A, LU);
	cout << endl << "LU:" << endl;
	LU.Show();
	//Mat X = LUElimination(LU, b);
*/
	Mat X = GaussianElimination(A,b);
	X.Show();
}

int main(int argc, char* argv[])
{
	//prueba();


	string input_file_path = argv[1];
	string output_file_path = argv[2];
	int method = stoi(argv[3]);

	//Load input parameters
	ifstream input_file(input_file_path);
	ofstream output_file(output_file_path);
	string s;

	input_file >> s;
	ri = stod(s);
	input_file >> s;
	re = stod(s);
	input_file >> s;
	m = stoi(s); // lee m + 1 
	input_file >> s;
	n = stoi(s);
	input_file >> s;
	iso = stod(s);
	input_file >> s;
	ninst = stoi(s);

//cout << " r_e: " << re << "\n r_i: " << ri << "\n m: " << m << "\n n: " << n << "\n iso: " << iso << "\n ninst: " << ninst << endl;
	double pi = 3.141592653589793;
	double delta_r = (re-ri)/(double)m;
	double delta_theta = 2*pi/(double)n;
	//cout << "delta_r " << delta_r << endl; 
	//cout << "delta_theta " << delta_theta << endl;

	Mat A(n*m, n*m); //crea una matriz de n*m x n*m
	Mat b(n*m, 1);
	Mat LU(n*m, n*m);
	Mat X (n*m, 1);

	LoadMatrix(A,delta_r, delta_theta, ri, n, m);

	//A.Show();

	if (method == LU_METHOD)
		GetLU(A, LU);

	for (int i = 0; i < ninst; i++) {
		LoadInstanceOfB(input_file, n*m, n, b);	

		if (method == EG_METHOD)		
			X = GaussianElimination(A, b);
	    else
			X = LUElimination(LU, b);
		
		SaveResult(output_file, X);	
	}	
	
}
