#include "aux.h"


extern int ri;
extern int re;
extern int m;
extern int n;
extern int iso;
extern int ninst;



void LoadMatrix(Mat& thisMat, double delta_r, double delta_theta, double ri, int n, int m)
{
	for (int row = 0; row < thisMat.rows(); row++) {
		if (row < n || row > thisMat.rows() - n - 1) { /// para los primeros n o los ultimos n relleno con los Ti y Te (caso base)
			thisMat(row, row) = 1.0;
		} else {
			int j = row / n;
			int k = (row + n) % n;
			double r = j * delta_r + ri;
			thisMat(row, j * n + k) = Coefficient_j_minus_one_k(delta_r, r);
			thisMat(row, ((j - 1 + m) % m) * n + k) = Coefficient_j_k(delta_r, delta_theta, r);
			thisMat(row, ((j + 1 + m) % m) * n + k) = Coefficient_j_plus_one_k(delta_r);
			thisMat(row, j * n + (k - 1 + n) % n) = Coefficient_j_k_minus_one(delta_theta, r);
			thisMat(row, j * n + (k + 1 + n) % n) = Coefficient_j_k_plus_one(delta_theta, r);
		}
	}
	
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



void LoadMatrixFromFile(Mat& A, Mat& b, string file_path)
{
	ifstream f(file_path);
	string s;
	
	f >> s;
	int dim = stoi(s);

	assert(dim == A.rows() && "Dimensiones incorrectas");

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
	double coefficient;

	for (int actual_row = 0; actual_row < U.rows() - 1 /*n*m-1*/; ++actual_row)
	{
		if (U(actual_row, actual_row) == 0) {
			cout << "El elemento " << actual_row << " de la diagonal es cero" << endl;
			exit(1);
		}

		for (int row = actual_row + 1; row < U.rows(); ++row)
		{	
			coefficient = U(row, actual_row);
			double division = (double)coefficient / (double)(U(actual_row, actual_row));

			for (int col = actual_row; col < U.cols(); ++col)
			{	
				//cout << "pre: ["<< row << "][" << col << "] = " << thisMat(row, col) << endl;
				//cout << "cuenta: " << thisMat(row, col) << " - " <<  thisMat(row, actual_row) << " / " << thisMat(actual_row,actual_row) << " * " << thisMat(actual_row, col) << endl;
				if (col == actual_row) {  
					//si es el primer elemento de la fila , se que tiene que dar 0 la cuenta
				 	U(row,col) = 0.;
				} else {
					//paranoid mode on
					double multiplication = (double)( division * (double)U(actual_row, col));
					double res = (double)U(row, col) - (double)multiplication;

					U(row, col) = (double)res;
					//paranoid mode off
				}
				//cout << "post: ["<< row << "][" << col << "] = " << thisMat(row, col) << endl;
			}

			b(row, 0) = b(row, 0) - (double)(division * b(actual_row, 0));
		}
	}

	cout << "Matriz triangulada" << endl;
	U.Show();
	cout << endl << endl;

	return BackwardSubstitution(U, b);
}



Mat BackwardSubstitution(Mat& U, Mat& b)
{
	Mat X(U.rows(), 1);

	for (int i = U.rows() - 1; i >= 0; i--) {
		double acum = 0.0;
		for (int j = i+1; j < U.rows(); j++)
			acum += U(i, j) * X(j, 0);
		
		X(i, 0) = (double) ((double)(1. / U(i, i)) * (b(i, 0) - acum)); 
	}

	return X;
}
