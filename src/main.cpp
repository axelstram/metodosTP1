#include "Mat.h"
#include "aux.h"
#include <string>

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
	m = stoi(s) - 1; /* lee m + 1 */
	input_file >> s;
	n = stoi(s);
	input_file >> s;
	iso = stod(s);
	input_file >> s;
	ninst = stoi(s);

	double delta_r = (re-ri)/(double)m;

	double delta_theta = 360.0/(double)n;

	Mat A(n*m, n*m);

	A.LoadMatrix(delta_r, delta_theta);

	for (int i = 0; i < ninst; i++) {
		Mat B = LoadInstance(input_file, n);

		if (method == EG)
			A.GaussianElimination(B,output_file);
		else
			A.LUElimination(B,output_file);
	}

}