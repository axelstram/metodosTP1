#include "mat.h"


Mat::Mat(size_t rows, size_t cols) : rows_(rows), cols_(cols), data_(rows * cols)
{
}



double& Mat::operator()(size_t i, size_t j)
{
    return data_[i * cols_ + j];
}



double Mat::operator()(size_t i, size_t j) const
{
    return data_[i * cols_ + j];
} 



Mat& Mat::operator=(const Matrix& anotherMat)
{

}



Mat& Mat::operator+(const Matrix& anotherMat)
{

}



Mat& Mat::operator-(const Matrix& anotherMat)
{

}



Mat& Mat::operator*(const Matrix& anotherMat)
{
	assert(this->cols_ == anotherMat.rows_ && "Cols and Rows don't match");
}



size_t Mat::rows() const
{
	return rows_;
}



size_t Mat::cols() const
{
	return cols_;
}


// Redefinir operador <<