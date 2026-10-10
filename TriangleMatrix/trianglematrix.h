#pragma once

#include "matrix.h"
#include "mathvector.h"
#include <initializer_list>
#include <fstream>
template <typename T>
class TriangleMatrix : public MathVector<MathVector<T>> {
public:
    inline size_t getN()const noexcept {
        return (*this).MathVector<MathVector<T>>::size();
    }
    TriangleMatrix();
    TriangleMatrix(size_t);
    TriangleMatrix(const Matrix<T>&);
    TriangleMatrix(std::initializer_list<std::initializer_list<T>>);
    TriangleMatrix(const MathVector<MathVector<T>>&);
    TriangleMatrix(const TriangleMatrix&);

    double calcDeterminant()const noexcept;

    bool operator==(const TriangleMatrix<T>&)const noexcept;
    bool operator!=(const TriangleMatrix<T>&)const noexcept;

    TriangleMatrix<T> operator*(const TriangleMatrix<T>&)const;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const TriangleMatrix<T>& other) {
    for (size_t i = 0;i < other.getN();++i) {
        out << other[i];
    }
    return out;
}
template <typename T>
TriangleMatrix<T>::TriangleMatrix(): MathVector<MathVector<T>>() {}


template <typename T>
TriangleMatrix<T>::TriangleMatrix(size_t N):MathVector<MathVector<T>>(N){
    for (size_t i = 0;i < N;++i) {
        (*this)[i] = MathVector<T>(N - i);
        (*this)[i].MathVector<T>::setStart(i);
    }
}

template <typename T>
TriangleMatrix<T>::TriangleMatrix(std::initializer_list<std::initializer_list<T>> list):MathVector<MathVector<T>>(list.size()) {
    size_t start = 0, j = 0; 
    for (auto row : list) {
        size_t count = row.size() - (start);
        (*this)[j] = MathVector<T>(count);
        (*this)[j].MathVector<T>::setStart(start);
        const T* row_elem = row.begin();
        for (size_t ind = 0;ind < count;++ind) {
            (*this)[j][ind+start] = row_elem[start + ind];
        }
        j++;start++;
    }
}

template <typename T>
TriangleMatrix<T>::TriangleMatrix(const MathVector<MathVector<T>>& other):MathVector<MathVector<T>>(other.size()) {
    size_t other_size = other.size(); 
    for (size_t i = 0;i < other_size;++i) {
        (*this)[i] = MathVector<T>(other.size() - i);
        (*this)[i].MathVector<T>::setStart(i);
        (*this)[i] = other[i];
    }
}

template <typename T>
TriangleMatrix<T>::TriangleMatrix(const TriangleMatrix& other):MathVector<MathVector<T>>(other) {}


template <typename T>
bool TriangleMatrix<T>::operator==(const TriangleMatrix<T>& other)const noexcept {
    if ((*this).getN() != other.getN()) { return false; }
    for (size_t i = 0;i < other.getN();++i) {
        if ((*this)[i] != other[i]) { return false; }
    }
    return true;
}

template <typename T>
bool TriangleMatrix<T>::operator!=(const TriangleMatrix<T>& other)const noexcept {
    return !((*this) == other);
}

template <typename T>
TriangleMatrix<T>::TriangleMatrix(const Matrix<T>& other):MathVector<MathVector<T>>(other.getN()) {
    Matrix<T> res(other);
    size_t other_N = res.getN();
    if (other_N == 0) { return; }
    for (size_t j = 0;j < other_N - 1;j++) { //опорная строка
        T Op = res[j][j];
        if (Op == 0) { throw std::logic_error("division by zero"); }
        for (size_t i = j+1;i < other_N;++i) { //строка,которую меняем
            double Mn = -(static_cast<double>(res[i][j]) / static_cast<double>(Op));
            for (size_t z = j;z < other_N;++z) { //элемент этой строки
                res[i][z] += (res[j][z]*Mn);
            }
        }
    }
    for (size_t i = 0;i < other_N;++i) {
        (*this)[i] = MathVector<T>(other_N-i);
        (*this)[i].MathVector<T>::setStart(i);
        for (size_t j = i;j < other_N;++j) {
            (*this)[i][j] = res[i][j];
        }
    }

}

template <typename T>
double TriangleMatrix<T>::calcDeterminant()const noexcept {
    if ((*this).getN() == 0) { return 0; }
    double res = (*this)[0][0];
    for (size_t i = 1;i < (*this).getN();++i) {
        res *= (*this)[i][i];
    }
    return res;
}


template <typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(const TriangleMatrix<T>& other)const {
    if ((*this).getN() != other.getN()) { throw std::logic_error("deferent dimension"); }
    size_t size = other.getN();
    TriangleMatrix<T> res(size);
    for (size_t i = 0;i < size;++i) {
        size_t start = (*this)[i].MathVector<T>::getStart();
        for (size_t j = 0;j < size;++j) {
            for (size_t z = start;z < size+start;++z) {
                if (z < (*this)[i].MathVector<T>::getStart() || j < other[z].MathVector<T>::getStart()) { continue; }
                res[i][j] += (*this)[i][z] * other[z][j];
            }
        }
    }
    return res;
}