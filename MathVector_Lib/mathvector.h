#pragma once
#include "vector.h"

template <typename T>
class MathVector : public Vector<T> {
private:
	size_t _start_index;
public:
	MathVector(size_t s = 0,const T* data = nullptr);
	MathVector(std::initializer_list<T> data );
	MathVector(const MathVector<T>& other);
	~MathVector() = default;
	inline size_t size()const noexcept {
		return this->Vector<T>::getSize();
	}

	MathVector<T> operator* (double value)const noexcept;
	MathVector<T>& operator*=(double value)noexcept;

	MathVector<T> operator+ (const MathVector<T>& other);
	MathVector<T> operator- (const MathVector<T>& other);
	double operator* (const MathVector<T>& other);

	MathVector<T>& operator+=(const MathVector<T>& other);
	MathVector<T>& operator-=(const MathVector<T>& other);
	MathVector<T>& operator=(const MathVector<T>& other);

	const T& operator[](size_t index)const;
	T& operator[](size_t index);

	bool operator==(MathVector<T>& other)const;
	bool operator!=(MathVector<T>& other)const;

	//template <class friend_type>
	//friend std::istream& operator>> (std::istream& in, MathVector<friend_type>& vec);

	//template <class friend_type>
	//friend std::ostream& operator<< (std::ostream& out, const MathVector<friend_type>& vec);
};

template <typename T>
MathVector<T>::MathVector(size_t s, const T* data): Vector<T>(data, s), _start_index(0) {
	this->reserve(s);
}

template <typename T>
MathVector<T>::MathVector(std::initializer_list<T> data): Vector<T>(data), _start_index(0){
	this->reserve(data.size());
}

template <typename T>
MathVector<T>::MathVector(const MathVector<T>& other): Vector<T>(other), _start_index(0) {
	this->reserve(other.size());
}

template <typename T>
MathVector<T> MathVector<T>::operator*(double value)const noexcept{
	MathVector<T> res(*this);
	res *= value;
	return res;
}

template <typename T>
MathVector<T>& MathVector<T>::operator*=(double value)noexcept{
	for (int i = 0;i < this->size();++i) {
		(*this)[i] *= value;
	}
	return (*this);
}

template <typename T>
MathVector<T> MathVector<T>::operator+(const MathVector<T>& other){
	MathVector<T> res(*this);
	for (int i = 0;i < this->size();++i) {
		res[i] = (*this)[i] + other[i];
	}
	return res;
}

template <typename T>
MathVector<T> MathVector<T>::operator-(const MathVector<T>& other){
	MathVector<T> res(*this);
	for (int i = 0;i < this->size();++i) {
		res[i] = (*this)[i] - other[i];
	}
	return res;
}

template <typename T>
double MathVector<T>::operator* (const MathVector<T>& other) {
	double res = 0.0;
	for (int i = 0;i < this->size();++i) {
		res += (*this)[i] * other[i];
	}
	return res;
}

template <typename T>
MathVector<T>& MathVector<T>::operator+=(const MathVector<T>& other) {
	(*this) = (*this) + other;
	return *this;
}

template <typename T>
MathVector<T>& MathVector<T>::operator-=(const MathVector<T>& other){
	(*this) = (*this) - other;
	return *this;
}

template <typename T>
MathVector<T>& MathVector<T>::operator=(const MathVector<T>& other){
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
bool MathVector<T>::operator==(MathVector<T>& other)const {
	return ((*this).Vector<T>::operator==(other) && _start_index == other._start_index);
}

template <typename T>
bool MathVector<T>::operator!=(MathVector<T>& other)const {
	return !((*this) == other);
}

//template <typename T>
//std::istream& operator>> (std::istream& in, MathVector<T>& vec) {
//	T element;
//	while (in >> element) {
//		vec.pushBack(element);
//	}
//	return in;
//}
//
//template <typename T>
//std::ostream& operator<< (std::ostream& out, const MathVector<T>& vec) {
//	out << "{";
//	if (vec.isEmpty()) {
//		out << "}\n";
//		return out;
//	}
//	out << vec[0];
//	for (int i = 1;i < vec.size();++i) {
//		out << "," << vec[i];
//	}
//	out << "}\n";
//	return out;
//}