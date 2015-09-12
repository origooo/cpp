#include <iostream>

using namespace std;

template <class T, int multiplier> void multiply(T &val) {
	val *= multiplier;
}

int main() {
	int a = 2;
	double b = 2.12345;

	std::cout << a << endl;
	multiply<decltype(a),2>(a);
	std::cout << a << endl;

	std::cout << b << endl;
	multiply<decltype(b),2>(b);
	std::cout << b << endl;

	return 0;
}