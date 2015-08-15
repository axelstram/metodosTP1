/***** A 2-D Matrix *****/

#include <iostream>
#include <cassert>

using namespace std;


class Mat {

	public:
	    Mat(size_t rows, size_t cols);
	    double& operator()(size_t i, size_t j);
	    double operator()(size_t i, size_t j) const;
	    Mat& operator=(const Matrix& anotherMat);
	    Mat& operator+(const Matrix& anotherMat);
	    Mat& operator-(const Matrix& anotherMat);
	    Mat& operator*(const Matrix& anotherMat);
	    size_t rows() const;
	    size_t cols() const;

	private:

	    size_t rows_;
	    size_t cols_;
	    std::vector<double> data_;
};
 
