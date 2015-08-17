#include "Mat.h"


Mat::Mat(size_t rows, size_t cols, int n, int m) : rows_(rows), cols_(cols), n_(n), m_(m), data_(rows * cols)
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



Mat& Mat::operator=(const Mat& anotherMat)
{

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



void LoadMatrix(double delta_r, double delta_theta)
{

	for(int row = 0 ; row < rows_; row++){
		for(int col = 0 ; col < cols_; col++){
			if(row < n_ || row > cols_-1-n_){ /// para los primeros n o los ultimos n relleno con los Ti y Te
				Mat& thisMat = *this;
				thisMat(col, col) = 1.0;
			}else{

			}

			
		}
	}

}



void Mat::GaussianElimination()
{

}
	


void Mat::LUElimination()
{

}



void Show(const Mat& mat)
{

	for (int j = 0; j < mat.rows(); j++) {
		for (int k = 0; k < mat.cols(); k++) {
			cout << mat(j,k) << " ";
		}
		cout << endl;
	}
}
// Redefinir operador <<