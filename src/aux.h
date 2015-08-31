#include "Mat.h"
#include <iomanip>      // std::setprecision
#include <algorithm>

void LoadInstanceOfB(ifstream& opened_file, int size_of_b, int n, Mat& b);

 
void LoadMatrix(Mat& thisMat, double delta_r, double delta_theta, double r, int n_, int m_);
void LoadMatrixFromFile(Mat& A, Mat& b, string file); /*nuestro load*/
void SaveResult(ofstream& output_file, Mat& X);	

	    
Mat GaussianElimination(Mat& A, Mat& b);
Mat LUElimination(Mat& LU, Mat& b);

Mat BackwardSubstitution(Mat& U, Mat& b);// hace backward subtitution suponiendo que me llega una matriz triangular superior
Mat BackwardSubstitutionLU(Mat& LU, Mat& b);// hace backward substitution suponiendo que la entrada es la matriz LU y solo usa los coeficientes de la 

void GetLU(Mat& A, Mat& LU);

double Coefficient_j_minus_one_k(double delta_r, double r);
double Coefficient_j_k(double delta_r, double delta_theta, double r);
double Coefficient_j_plus_one_k(double delta_r);
double Coefficient_j_k_minus_one(double delta_theta, double r);
double Coefficient_j_k_plus_one(double delta_theta, double r);

void getIsotermRadiusValues(Mat& X, int angles, double isoterm, double delta_r, double ri);