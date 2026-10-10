#include "vector.h"
#include "mathvector.h"
#include "matrix.h"
#include "trianglematrix.h"
int main() {
    std::initializer_list<std::initializer_list<double>> init_A = {
    {1.0, -1.0,  2.0,  3.0},
    {0.0,  2.0, -2.0,  1.0},
    {0.0,  0.0, -3.0,  4.0},
    {0.0,  0.0,  0.0,  5.0}
    };

    std::initializer_list<std::initializer_list<double>> init_B = {
        {3.0,  2.0,  0.0, -1.0},
        {0.0,  1.0,  4.0,  2.0},
        {0.0,  0.0,  2.0, -3.0},
        {0.0,  0.0,  0.0, -1.0}
    };
	TriangleMatrix<double> matrix1(init_A);
	TriangleMatrix<double> matrix2(init_B);
	TriangleMatrix<double> matrix3 = matrix1 * matrix2;
	std::cout << matrix3;

	return 0;
}