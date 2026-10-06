#include "vector.h"
#include "mathvector.h"
#include "matrix.h"
int main() {
	std::initializer_list<std::initializer_list<int>> list = { {1,2,3},{4,5,6},{7,8,9} };
	Matrix<int> matrix(list);
	Matrix<int> mat(matrix);
	Matrix<int> new_matr = mat * matrix;
	std::cout << mat << "\n" << new_matr;
	return 0;
}