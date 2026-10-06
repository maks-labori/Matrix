#include "vector.h"
#include "mathvector.h"
#include "matrix.h"
int main() {
	std::cout << "Start\n";
	MathVector<double> vec1 = { 2,2,2 };
	MathVector<double> vec2{ 1,2,3,4,5 };
	std::cout << vec1.size() << " " << vec2.size();
	double b = 5.0;
	MathVector<double>vec3;
	vec3 = b * vec2;
	std::cout << vec3;
	//Matrix<int> matrix(2,2);
	return 0;
}