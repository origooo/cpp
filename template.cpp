#include <iostream>

using namespace std;

template <typename T, typename M> void multiply(T val, M multiplier) {
	*val *= *multiplier;
}

int main() {
	double m = 2, *m_ptr = &m;;
	
	int a = 2, *a_ptr = &a;
	double b = 2.12345, *b_ptr = &b;

	std::cout << a << endl;
	multiply<decltype(a_ptr),decltype(m_ptr)>(a_ptr,m_ptr);
	std::cout << a << endl;

	std::cout << b << endl;
	multiply<decltype(b_ptr),decltype(m_ptr)>(b_ptr,m_ptr);
	std::cout << b << endl;

	return 0;
}