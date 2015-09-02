#include "aux.h"


extern int ri;
extern int re;
extern int m;
extern int n;
extern int iso;
extern int ninst;



void LoadMatrix(Mat& thisMat, double delta_r, double delta_theta, double ri, int n, int m)
{
	//m = j (radios)
	//n =  k (radios)
	for (int row = 0; row < thisMat.rows(); row++) {
		if (row < n || row > thisMat.rows() - n - 1) { /// para los primeros n o los ultimos n relleno con los Ti y Te (caso base)
			thisMat(row, row) = 1.0;
		} else {
			int j = row / n;
			int k = (row + n) % n;
			double r = j * delta_r + ri;
			thisMat(row, j * n + k) = Coefficient_j_k(delta_r, delta_theta, r);
			thisMat(row, ((j - 1 + m % m)) * n + k) = Coefficient_j_minus_one_k(delta_r, r);
			thisMat(row, ((j + 1 + (m+2)) % (m+2)) * n + k) = Coefficient_j_plus_one_k(delta_r); 
 			thisMat(row, j * n + (k - 1 + n) % n) = Coefficient_j_k_minus_one(delta_theta, r);
			thisMat(row, j * n + (k + 1 + n) % n) = Coefficient_j_k_plus_one(delta_theta, r);
		}
	}
	
}



 void LoadInstanceOfB(ifstream& opened_file, int size_of_b, int n, Mat& b)
 {
 	string s;

	for (int i = 0; i < size_of_b; ++i)
	{
		if(i < n || (b.rows() - n) <= i) {
			opened_file >> s;
			b(i, 0) = stod(s);
		}else{			
			b(i, 0) = 0.0;
		}
	}
 }



void SaveResult(ofstream& output_file, Mat& X)
{
	for (int i = 0; i < X.rows(); i++)
		output_file << std::fixed << std::setprecision(6) << X(i, 0) << endl;
}



double Coefficient_j_minus_one_k(double delta_r, double r)
{
	return ( (1.0 / (delta_r * delta_r)) - (1.0 / (r * delta_r)) );
}



double Coefficient_j_k(double delta_r, double delta_theta, double r)
{
	return ( (-2.0 / (delta_r * delta_r)) + (1.0 / (r * delta_r)) - (2.0 / ((r * r * delta_theta * delta_theta))) );
}



double Coefficient_j_plus_one_k(double delta_r)
{
	return (1.0 / (delta_r * delta_r));
}



double Coefficient_j_k_minus_one(double delta_theta, double r)
{
	return (1.0  / (r * r * delta_theta * delta_theta));
}



double Coefficient_j_k_plus_one(double delta_theta, double r)
{
	return (1.0  / (r * r * delta_theta * delta_theta));
}



/* Nuestro load */
void LoadMatrixFromFile(Mat& A, Mat& b, string file_path)
{
	ifstream f(file_path);
	string s;
	
	f >> s;
	int dim = stoi(s);

	if (dim != A.rows()) {
		cout << "Dimensiones incorrectas al cargar " << endl << "dim " << dim << endl << "rows(A) " << A.rows() << endl;
		exit(1);
	}

	//Cargo A
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			f >> s;
			A(i,j) = stoi(s);
		}
	}

	//Cargo b
	for (int i = 0; i < dim; i++) {
		f >> s;
		b(i, 0) = stoi(s);
	}
}



Mat GaussianElimination(Mat& A, Mat& b)
{
	Mat U = A.clone(); /* Matriz triangulada */

	for (int actual_row = 0; actual_row < U.rows() - 1 /*n*m-1*/; ++actual_row)
	{
		if (U(actual_row, actual_row) == 0) {
			cout << "El elemento " << actual_row << " de la diagonal es cero" << endl;
			exit(1);
		}

		for (int row = actual_row + 1; row < U.rows(); row++)
		{	
			double coefficient = (double)U(row, actual_row) / (double)(U(actual_row, actual_row));

			for (int col = actual_row; col < U.cols(); col++)
			{	
				//cout << "pre: ["<< row << "][" << col << "] = " << thisMat(row, col) << endl;
				//cout << "cuenta: " << thisMat(row, col) << " - " <<  thisMat(row, actual_row) << " / " << thisMat(actual_row,actual_row) << " * " << thisMat(actual_row, col) << endl;
				if (col == actual_row) {  
					//si es el primer elemento de la fila , se que tiene que dar 0 la cuenta
				 	U(row,col) = 0.;
				} else {
					U(row, col) -= coefficient * U(actual_row, col);
				}
				//cout << "post: ["<< row << "][" << col << "] = " << thisMat(row, col) << endl;
			}

			b(row, 0) = b(row, 0) - (double)(coefficient * b(actual_row, 0));
		}
	}

	//cout << "Matriz triangulada" << endl;
	//U.Show();
	//cout << endl << endl;

	return BackwardSubstitution(U, b);
}



bool DescendingOrder(double i, double j) { return (i>j); }



//Para el caso que la matriz U sea triangular superior
Mat BackwardSubstitution(Mat& U, Mat& b)
{
	Mat X(U.rows(), 1);

	for (int i = U.rows() - 1; i >= 0; i--) {
		double acum = 0.0;

		for (int j = i+1; j < U.rows(); j++) 
			acum += U(i, j) * X(j, 0);
		
		X(i, 0) = (double)(b(i, 0) - acum) / U(i, i);
	}

	return X;	
}



//Para el caso que la matriz sea LU (y suponiendo que la diagonal son todos 1)
Mat BackwardSubstitutionLU(Mat& LU, Mat& b)
{
	Mat X(LU.rows(), 1);
	//hardcodeamos el primer valor porq la formula no funca para el j = 0
	X(0,0) = b(0,0);

	for (int i = 1; i < LU.rows(); i++) {
		X(i,0) = b(i,0);

		for (int j = 0; j < i; j++)
			X(i, 0) -= (double) (LU(i,j)*X(j,0)); 
	}

	return X;
}



Mat LUElimination(Mat& LU, Mat& b)
{
	Mat Y = BackwardSubstitutionLU(LU, b);
	Mat X = BackwardSubstitution(LU, Y);

	return X;
}



void GetLU(Mat& A, Mat& LU)
{
	LU = A.clone(); /* Matriz triangulada */

	for (int actual_row = 0; actual_row < LU.rows() - 1 /*n*m-1*/; ++actual_row)
	{
		if (LU(actual_row, actual_row) == 0) {
			cout << "El elemento " << actual_row << " de la diagonal es cero" << endl;
			exit(1);
		}

		for (int row = actual_row + 1; row < LU.rows(); ++row)
		{	
			double coefficient = (double)LU(row, actual_row) / (double)LU(actual_row, actual_row);

			for (int col = actual_row; col < LU.cols(); ++col)
			{
				if (col == actual_row) {  
					//si es el primer elemento de la fila , se que tiene que dar 0 la cuenta
				 	LU(row, col) = coefficient;
				} else {
					LU(row, col) -= coefficient * LU(actual_row, col);
				}
				//cout << "post: ["<< row << "][" << col << "] = " << thisMat(row, col) << endl;
			}
		}
	}

}

void getIsotermRadiusValues(Mat& X, int angles, double isoterm, double delta_r, double ri, ofstream& output_file)
{	
	/* 
	* Guardo en el vector istermRadius, en la posicion i el radio de la isterma 500 para cada angulo.
	*/
	vector<double> isotermRadius(angles);

	for (int i = 0; i < angles; ++i)
	{
		isotermRadius[i]=-1;
	}

	for (int i = 0; i < X.rows() - angles; ++i)
	{
		// Encontre la isoterma cuando el punto actual es menor a la isoterma y el siguiente es mayor. El || es para el caso en que esten invertidos los valores (mas frio adentro)
		if( (X(i,0) >= isoterm && X(i+angles,0) <= isoterm) || (X(i,0) <= isoterm && X(i+angles,0) >= isoterm) )
			isotermRadius[i % angles] = ( ri + (i / angles)*delta_r + (((X(i,0) - isoterm) * delta_r)/ (X(i,0) - X(i+angles,0)) )); // regla de tres simple
	}

	for (int i = 0; i < angles; ++i)
	{
		output_file << std::fixed << std::setprecision(6) << isotermRadius[i] << endl;
	}

}

