#include <iostream>

using namespace std;

template <class T>
T someFunction(T a, T b) {
	return a+b;
}

int main() {
	std::cout << someFunction(2,2) << endl;
	std::cout << someFunction(3,8) << endl;

	return 0;
}