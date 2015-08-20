#include "Mat.h"
#include "aux.h"
#include <string>
#include <fstream>

#define EG 0
#define LU 1


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
void showB(vector<double> B){
	cout << "B: ";
	for (int i = 0; i < B.size(); ++i)
	{
		cout << B[i] << " ";
	}
	cout << endl;
}

int main(int argc, char* argv[])
{
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

	Mat A(n, m); //crea una matriz de n*m x n*m
	vector<double> B(n*m);
	
	// Relleno de B
	for (int i = 0; i < n*m; ++i)
	{
		if(i < n || ((n*m)-n) <= i) {
			input_file >> s;
			B[i]=stod(s);
		}else{			
			B[i]=0.0;
		}
	}

	showB(B);
	A.LoadMatrix(delta_r, delta_theta, ri); //delta_r * j + ri
	A.Show();

	//PRUEBA PARA GAUSS
	/*
	Mat prueba(2,2);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			prueba(i,j)=i*i+1+j*j+4*9;
		}
	}
	prueba.Show();
	prueba.GaussianElimination();
	prueba.Show();
	*/

	/*
	for (int i = 0; i < ninst; i++) {
		Mat B = LoadInstance(input_file, n);

		if (method == EG)
			A.GaussianElimination(B,output_file);
		else
			A.LUElimination(B,output_file);
	}
	*/
}

