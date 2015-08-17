/***** A 2-D Matrix *****/
#ifndef MATRIX_H_
#define MATRIX_H_


#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


class Mat {

	public:
	    Mat(size_t rows, size_t cols);
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
		void LoadMatrix(double delta_r, double delta_theta);
	private:

	    size_t rows_;
	    size_t cols_;
	    int n_,m_; /// n = # angulos, m = # radios
	    vector<double> data_;
};
 


void Show(const Mat& mat);


#endif