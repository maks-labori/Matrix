#pragma once
#include "vector.h"

template <typename T>
class MathVector : public Vector<T> {
private:
	size_t _start_index;
public:
	explicit MathVector(size_t s = 0,const T* data = nullptr);
	MathVector(std::initializer_list<T> data );
	MathVector(const MathVector<T>& other);
	~MathVector() = default;
	inline size_t size()const noexcept {
		return this->Vector<T>::getSize();
	}

	MathVector<T> operator* (const double& value)const noexcept;
	MathVector<T>& operator*=(const double& value)noexcept;

	MathVector<T> operator+ (const MathVector<T>& other)const noexcept;
	MathVector<T> operator- (const MathVector<T>& other)const noexcept;
	double operator* (const MathVector<T>& other)const noexcept;

	MathVector<T>& operator+=(const MathVector<T>& other)noexcept;
	MathVector<T>& operator-=(const MathVector<T>& other)noexcept;
	MathVector<T>& operator=(const MathVector<T>& other)noexcept;

	const T& operator[](size_t index)const;
	T& operator[](size_t index);

	bool operator==(MathVector<T>& other)const noexcept;
	bool operator!=(MathVector<T>& other)const noexcept;

	template <class friendT>
	friend MathVector<T> operator*(const double& value, const MathVector<T>& other)noexcept;
};

template <typename T>
MathVector<T> operator*(const double& value, const MathVector<T>& other)noexcept {
	MathVector<T> res(other);
	res *= value;
	return res;
}

template <typename T>
MathVector<T>::MathVector(size_t s, const T* data): Vector<T>(s,data), _start_index(0) {
	this->Vector<T>::reserve(s);
}

template <typename T>
MathVector<T>::MathVector(std::initializer_list<T> data): Vector<T>(data), _start_index(0){
	this->Vector<T>::reserve(data.size());
}

template <typename T>
MathVector<T>::MathVector(const MathVector<T>& other): Vector<T>(other), _start_index(0) {
	this->Vector<T>::reserve(other.size());
}

template <typename T>
MathVector<T> MathVector<T>::operator*(const double& value)const noexcept{
	MathVector<T> res(*this);
	res *= value;
	return res;
}

template <typename T>
MathVector<T>& MathVector<T>::operator*=(const double& value)noexcept{
	for (int i = 0;i < this->size();++i) {
		(*this)[i] *= value;
	}
	return (*this);
}

template <typename T>
MathVector<T> MathVector<T>::operator+(const MathVector<T>& other)const noexcept{
	MathVector<T> res(*this);
	for (int i = 0;i < this->size();++i) {
		res[i] = (*this)[i] + other[i];
	}
	return res;
}

template <typename T>
MathVector<T> MathVector<T>::operator-(const MathVector<T>& other)const noexcept{
	MathVector<T> res(*this);
	for (int i = 0;i < this->size();++i) {
		res[i] = (*this)[i] - other[i];
	}
	return res;
}

template <typename T>
double MathVector<T>::operator* (const MathVector<T>& other)const noexcept {
	if ((*this).size() != other.size()) { throw std::logic_error("different dimension"); }
	double res = 0.0;
	for (int i = 0;i < this->size();++i) {
		res += (*this)[i] * other[i];
	}
	return res;
}

template <typename T>
MathVector<T>& MathVector<T>::operator+=(const MathVector<T>& other)noexcept {
	(*this) = (*this) + other;
	return *this;
}

template <typename T>
MathVector<T>& MathVector<T>::operator-=(const MathVector<T>& other)noexcept{
	(*this) = (*this) - other;
	return *this;
}

template <typename T>
MathVector<T>& MathVector<T>::operator=(const MathVector<T>& other)noexcept{
	if (&other != this) {
		(*this).Vector<T>::operator=(other);
		_start_index = other._start_index;
	}
	return (*this);
}

template <typename T>
const T& MathVector<T>::operator[](size_t index)const {
	return (*this).Vector<T>::operator[](index);
}

template <typename T>
T& MathVector<T>::operator[](size_t index) {
	return (*this).Vector<T>::operator[](index);
}

template <typename T>
bool MathVector<T>::operator==(MathVector<T>& other)const noexcept{
	return ((*this).Vector<T>::operator==(other) && _start_index == other._start_index);
}

template <typename T>
bool MathVector<T>::operator!=(MathVector<T>& other)const noexcept{
	return !((*this) == other);
}
