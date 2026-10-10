#include "vector.h"
#include "mathvector.h"
#include "matrix.h"
#include "trianglematrix.h"
int main() {
	TriangleMatrix<int> matrix1 = { {1,2,3},{0,2,3},{0,0,3} };
	TriangleMatrix<int> matrix2 = { {1,2,3},{0,2,3},{0,0,3} };
	matrix1 = matrix1.Transposition();
	std::cout << matrix1;


	return 0;
}