#include "Mat.h"

 Mat LoadInstance(const ifstream& opened_file, int n);

 
void LoadMatrix(Mat& thisMat, double delta_r, double delta_theta, double r, int n_, int m_);
void LoadMatrixFromFile(Mat& A, Mat& b, string file); /*nuestro load*/
	    
Mat GaussianElimination(Mat& A, Mat& b);
void LUElimination(Mat& A, Mat& b, Mat L = Mat(0, 0), Mat U = Mat(0,0));
Mat BackwardSubstitution(Mat& A, Mat& b);


double Coefficient_j_minus_one_k(double delta_r, double r);
double Coefficient_j_k(double delta_r, double delta_theta, double r);
double Coefficient_j_plus_one_k(double delta_r);
double Coefficient_j_k_minus_one(double delta_theta, double r);
double Coefficient_j_k_plus_one(double delta_theta, double r);