#include "Mat.h"


Mat::Mat(size_t n, size_t m) : rows_(n), cols_(n), n_(n), m_(m), data_((n) * (m))
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



void Mat::LoadMatrix(double delta_r, double delta_theta, double ri)
{
	Mat& thisMat = *this;

	for (int row = 0; row < rows_; row++) {
		if (row < n_ || row > rows_ - n_ - 1) { /// para los primeros n o los ultimos n relleno con los Ti y Te (caso base)
			thisMat(row, row) = 1.0;
		} else {
			int j = row / n_;
			int k = (row + n_) % n_;
			double r = j * delta_r + ri;
			thisMat(row, j * n_ + k) = Coefficient_j_minus_one_k(delta_r, r);
			thisMat(row, ((j - 1 + m_) % m_) * n_ + k) = Coefficient_j_k(delta_r, delta_theta, r);
			thisMat(row, ((j + 1 + m_) % m_) * n_ + k) = Coefficient_j_plus_one_k(delta_r);
			thisMat(row, j * n_ + (k - 1 + n_) % n_) = Coefficient_j_k_minus_one(delta_theta, r);
			thisMat(row, j * n_ + (k + 1 + n_) % n_) = Coefficient_j_k_plus_one(delta_theta, r);
		}
	}
	
}



double Mat::Coefficient_j_minus_one_k(double delta_r, double r)
{
	return ( (1.0 / (delta_r * delta_r)) - (1.0 / (r * delta_r)) );
}



double Mat::Coefficient_j_k(double delta_r, double delta_theta, double r)
{
	return ( (-2.0 / (delta_r * delta_r)) + (1.0 / (r * delta_r)) - (2.0 / ((r * r * delta_theta * delta_theta))) );
}



double Mat::Coefficient_j_plus_one_k(double delta_r)
{
	return (1.0 / (delta_r * delta_r));
}



double Mat::Coefficient_j_k_minus_one(double delta_theta, double r)
{
	return (1.0  / (r * r * delta_theta * delta_theta));
}



double Mat::Coefficient_j_k_plus_one(double delta_theta, double r)
{
	return (1.0  / (r * r * delta_theta * delta_theta));
}



void Mat::GaussianElimination()
{

	Mat& thisMat = *this;
	double coefficient;
	//for (int actual_row = 0; actual_row < thisMat.rows()-1 /*n*m-1*/; ++actual_row)
	//{
		int actual_row = 0;
		if(thisMat(actual_row, actual_row) == 0){
			cout << "el elemento " << actual_row << " de la diagonal es cero" << endl;
		}
		for (int row = actual_row + 1; row < thisMat.rows(); ++row)
		{	
			coefficient=thisMat(row, actual_row);
			for (int col = actual_row; col < thisMat.cols(); ++col)
			{	
				//cout << "pre: ["<< row << "][" << col << "] = " << thisMat(row, col) << endl;
				//cout << "cuenta: " << thisMat(row, col) << " - " <<  thisMat(row, actual_row) << " / " << thisMat(actual_row,actual_row) << " * " << thisMat(actual_row, col) << endl;
				thisMat(row, col) = thisMat(row, col) - ((coefficient / (thisMat(actual_row,actual_row))) * thisMat(actual_row, col));
				//cout << "post: ["<< row << "][" << col << "] = " << thisMat(row, col) << endl;
			}
		}
	//}



}
	


void Mat::LUElimination()
{

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
