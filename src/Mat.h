/***** A 2-D Matrix *****/
#ifndef MATRIX_H_
#define MATRIX_H_


#include <iostream>
#include <vector>
#include <cassert>


using namespace std;


class Mat {
	public:
	    Mat(size_t n, size_t m);
	    double& operator()(size_t i, size_t j);
	    double operator()(size_t i, size_t j) const;
	    Mat& operator=(const Mat& anotherMat);
	    Mat& operator+(const Mat& anotherMat);
	    Mat& operator-(const Mat& anotherMat);
	    Mat& operator*(const Mat& anotherMat);
	    size_t rows() const;
	    size_t cols() const;
	    void GaussianElimination();
	    void LUElimination();
		void LoadMatrix(double delta_r, double delta_theta, double r);
		void Show();

	private:

		double Coefficient_j_minus_one_k(double delta_r, double r);
		double Coefficient_j_k(double delta_r, double delta_theta, double r);
		double Coefficient_j_plus_one_k(double delta_r);
		double Coefficient_j_k_minus_one(double delta_theta, double r);
		double Coefficient_j_k_plus_one(double delta_theta, double r);

	    size_t rows_;
	    size_t cols_;
	    int n_, m_; /// n = # angulos, m = # radios
	    vector<double> data_;
};
 




#endif
