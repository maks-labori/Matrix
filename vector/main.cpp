#include "vector.h"
#include "mathvector.h"
#include "matrix.h"
#include "trianglematrix.h"
int main() {
	std::initializer_list<std::initializer_list<int>> list = { {2,4,-2,4},{1,5,1,7},{-1,1,1,1},{2,4,2,1} };
	Matrix<int> matrix(list);
	TriangleMatrix<int> trianglematrix(matrix);

	std::cout << trianglematrix << "\n" << trianglematrix.calcDeterminant();


	return 0;
}