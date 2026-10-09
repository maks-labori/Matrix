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
		return this->Vector<T>::size();
	}
	inline void setStart(size_t value) {
		this->_start_index = value;
	}
	inline size_t getStart()const noexcept {
		return _start_index;
	}
	MathVector<T> operator* (const double& value)const noexcept;
	MathVector<T>& operator*=(const double& value)noexcept;

	MathVector<T> operator+ (const MathVector<T>& other)const;
	MathVector<T> operator- (const MathVector<T>& other)const;
	double operator* (const MathVector<T>& other)const;

	MathVector<T>& operator+=(const MathVector<T>& other);
	MathVector<T>& operator-=(const MathVector<T>& other);
	MathVector<T>& operator=(const MathVector<T>& other)noexcept;

	const T& operator[](size_t index)const;
	T& operator[](size_t index);

	bool operator==(const MathVector<T>& other)const noexcept;
	bool operator!=(const MathVector<T>& other)const noexcept;

	template <class friendT>
	friend MathVector<T> operator*(const double& value, const MathVector<T>& other)noexcept;
};

template <typename T>
std::ostream& operator<< (std::ostream& out, const MathVector<T>& vec) {
	out << "{";
	if (vec.isEmpty()) {
		out << "}\n";
		return out;
	}
	size_t index = vec.getStart();
	while (index > 0) {
		out << "0 ";
		index--;
	}
	out << vec[0];
	for (size_t i = 1;i < vec.size();++i) {
		out << " " << vec[i];
	}
	out << "}\n";
	return out;
}

template <typename T>
MathVector<T> operator*(const double& value, const MathVector<T>& other)noexcept {
	MathVector<T> res(other);
	res *= value;
	return res;
}

template <typename T>
MathVector<T>::MathVector(size_t s, const T* data): Vector<T>(s,data), _start_index(0) {
	this->Vector<T>::realloc(s);
}

template <typename T>
MathVector<T>::MathVector(std::initializer_list<T> data): Vector<T>(data), _start_index(0){
	this->Vector<T>::realloc(data.size());
}

template <typename T>
MathVector<T>::MathVector(const MathVector<T>& other): Vector<T>(other), _start_index(0) {
	this->Vector<T>::realloc(other.size());
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
MathVector<T> MathVector<T>::operator+(const MathVector<T>& other)const{
	if (this->size() != other.size()) { throw std::logic_error("different size"); }
	MathVector<T> res(*this);
	for (int i = 0;i < this->size();++i) {
		res[i] = (*this)[i] + other[i];
	}
	return res;
}

template <typename T>
MathVector<T> MathVector<T>::operator-(const MathVector<T>& other)const{
	if (this->size() != other.size()) { throw std::logic_error("different size"); }
	MathVector<T> res(*this);
	for (int i = 0;i < this->size();++i) {
		res[i] = (*this)[i] - other[i];
	}
	return res;
}

template <typename T>
double MathVector<T>::operator* (const MathVector<T>& other)const{
	if ((*this).size() != other.size()) { throw std::logic_error("different dimension"); }
	double res = 0.0;
	for (int i = 0;i < this->size();++i) {
		res += (*this)[i] * other[i];
	}
	return res;
}

template <typename T>
MathVector<T>& MathVector<T>::operator+=(const MathVector<T>& other){
	(*this) = (*this) + other;
	return *this;
}

template <typename T>
MathVector<T>& MathVector<T>::operator-=(const MathVector<T>& other){
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
bool MathVector<T>::operator==(const MathVector<T>& other)const noexcept{
	return ((*this).Vector<T>::operator==(other) && _start_index == other._start_index);
}

template <typename T>
bool MathVector<T>::operator!=(const MathVector<T>& other)const noexcept{
	return !((*this) == other);
}
