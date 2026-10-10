#pragma once
#include "mathvector.h"

template <typename T>
class Matrix :public MathVector<MathVector<T>> {
public:
	inline size_t getN()const noexcept {
		return (*this).MathVector<MathVector<T>>::size();
	}
	inline size_t getM()const noexcept {
		if (getN() == 0) { return 0; }
		return (*this)[0].MathVector<T>::size();
	}
	Matrix();
	Matrix(size_t, size_t);
	Matrix(std::initializer_list<std::initializer_list<T>>);
	Matrix(const Matrix&);
	Matrix(const MathVector<MathVector<T>>&);
	Matrix<T> operator*(const Matrix<T>&)const;
	Matrix<T> Transposition()const noexcept;

	bool operator==(const Matrix<T>& other)const noexcept;
	bool operator!=(const Matrix<T>& other)const noexcept;
};

template <typename T>
std::ostream& operator<< (std::ostream& out, Matrix<T>& matrix) {
	for (size_t i = 0;i < matrix.getN();++i) {
		out << matrix[i];
	}
	return out;
}

template <typename T>
Matrix<T>::Matrix() :MathVector<MathVector<T>>() {}

template <typename T>
Matrix<T>::Matrix(size_t N, size_t M) : MathVector<MathVector<T>>(N) {
	for (size_t i = 0;i < N;++i) {
		(*this)[i] = MathVector<T>(M);
	}
}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list) :MathVector<MathVector<T>>(list.size()) {
	size_t i = 0;
	for (auto row : list) {
		(*this)[i] = MathVector<T>(row);
		++i;
	}
}

template <typename T>
Matrix<T>::Matrix(const Matrix& other):MathVector<MathVector<T>>(other) {}

template <typename T>
Matrix<T>::Matrix(const MathVector<MathVector<T>>& other) :MathVector<MathVector<T>>(other) {}

template <typename T>
Matrix<T> Matrix<T>::Transposition()const noexcept {
	size_t this_N = (*this).getN();
	size_t this_M = (*this).getM();
	Matrix<T> res(this_M, this_N);
	for (size_t i = 0;i < this_M;++i) {
		for (size_t j = 0;j < this_N;++j) {
			res[i][j] = (*this)[j][i];
		}
	}
	return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other)const{
	size_t this_N = (*this).getN();
	size_t this_M = (*this).getM();
	if (this_M != other.getN()) { throw std::logic_error("No way dimension"); }
	Matrix<T> otherT = other.Transposition();
	size_t otherM = other.getM();
	Matrix<T> res((*this).getN(), otherM);
	for (size_t i = 0;i < this_N;++i) {
		for (size_t j = 0;j < otherM;++j) {
			res[i][j] = (*this)[i] * otherT[j];
		}
	}
	return res;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T>& other)const noexcept {
	if ((*this).getM() != other.getM() || (*this).getN() != other.getN()) { return false; }
	for (size_t i = 0;i < other.getN();++i) {
		if ((*this)[i] != other[i]) { return false; }
	}
	return true;
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix<T>& other)const noexcept {
	return !((*this) == other);
}