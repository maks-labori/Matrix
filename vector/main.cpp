#include "vector.h"
#include "mathvector.h"
int main() {
	std::cout << "Start";
	MathVector<double> vec1 = { 1,1,1 };
	std::cout << vec1;
	//MathVector<double> vec2{ 0,0,0 };
	//MathVector<double> vec3{ 0,0,0 };
	//vec3 = vec1 + vec2;
	//std::cout << vec3;
	return 0;
}