#include "vector.h"
#include "mathvector.h"
#include "matrix.h"
#include "trianglematrix.h"
int main() {
	std::initializer_list<std::initializer_list<int>> list = { {1,1,1},{2,5,4},{1,4,6} };
	Matrix<int> matrix(list);
	TriangleMatrix<int> trianglematrix(matrix);
	std::cout << trianglematrix;
	//std::cout << trianglematrix[0][0] << " " << trianglematrix[0][1] << " " << trianglematrix[0][2] <<"\n";
	//std::cout << trianglematrix[1][0] << " " << trianglematrix[1][1] << " " << trianglematrix[1][2] << "\n";
	//std::cout << trianglematrix[2][0] << " " << trianglematrix[2][1] << " " << trianglematrix[2][2] << "\n";

	return 0;
}