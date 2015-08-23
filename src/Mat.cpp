#include "Mat.h"


Mat::Mat(size_t n, size_t m) : rows_(n), cols_(m), data_((n) * (m))
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



Mat& Mat::operator+(const Mat& anotherMat)
{

}



Mat& Mat::operator-(const Mat& anotherMat)
{

}



Mat& Mat::operator*(const Mat& anotherMat)
{
	//assert(this->cols_ == anotherMat.rows_ && "Cols and Rows don't match");
}



size_t Mat::rows() const
{
	return rows_;
}



size_t Mat::cols() const
{
	return cols_;
}



Mat Mat::clone() const
{
	Mat res(rows_, cols_);
	const Mat& thisMat = *this;

	for (int i = 0; i < rows_; i++) {
		for (int j = 0; j < cols_; j++) {
			res(i, j) = thisMat(i, j);
		}
	}

	return res;
}



void Mat::Show()
{
	Mat& thisMat = *this;
	for (int j = 0; j < rows_; j++) {
		for (int k = 0; k < cols_; k++) {
			cout << thisMat(j,k) << " ";
		}
		cout << endl;
	}
}
// Redefinir operador <<
