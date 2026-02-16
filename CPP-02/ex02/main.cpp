/*#include "Fixed.hpp"
int main( void )
{
Fixed a;
Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
std::cout << a << std::endl;
std::cout << ++a << std::endl;
std::cout << a << std::endl;
std::cout << a++ << std::endl;
std::cout << a << std::endl;
std::cout << b << std::endl;
std::cout << Fixed::max( a, b ) << std::endl;
return 0;
}*/

#include <iostream>
#include "Fixed.hpp"

int main() {
	std::cout << std::fixed;

	// Construction
	Fixed a;
	Fixed b;
	a.setRawBits(256); // 1.0
	b.setRawBits(512); // 2.0

	std::cout << "\n--- Comparison Operators ---\n";
	std::cout << "a = " << a.toFloat() << ", b = " << b.toFloat() << "\n";
	std::cout << "a > b: " << (a > b) << "\n";
	std::cout << "a < b: " << (a < b) << "\n";
	std::cout << "a >= b: " << (a >= b) << "\n";
	std::cout << "a <= b: " << (a <= b) << "\n";
	std::cout << "a == b: " << (a == b) << "\n";
	std::cout << "a != b: " << (a != b) << "\n";

	std::cout << "\n--- Arithmetic Operators ---\n";
	Fixed c = a + b;
	std::cout << "a + b = " << c.toFloat() << "\n";
	c = b - a;
	std::cout << "b - a = " << c.toFloat() << "\n";
	c = a * b;
	std::cout << "a * b = " << c.toFloat() << "\n";
	c = b / a;
	std::cout << "b / a = " << c.toFloat() << "\n";

	std::cout << "\n--- Increment / Decrement Operators ---\n";
	Fixed d;
	d.setRawBits(256); // 1.0

	std::cout << "Original d: " << d.toFloat() << "\n";
	std::cout << "++d: " << (++d).toFloat() << "\n";
	std::cout << "d++: " << (d++).toFloat() << "\n";
	std::cout << "After d++: " << d.toFloat() << "\n";
	std::cout << "--d: " << (--d).toFloat() << "\n";
	std::cout << "d--: " << (d--).toFloat() << "\n";
	std::cout << "After d--: " << d.toFloat() << "\n";

	std::cout << "\n--- Min / Max Functions ---\n";
	Fixed& minVal = Fixed::min(a, b);
	std::cout << "min(a, b): " << minVal.toFloat() << "\n";

	Fixed& maxVal = Fixed::max(a, b);
	std::cout << "max(a, b): " << maxVal.toFloat() << "\n";

	const Fixed e = Fixed(3.14f);
	const Fixed f = Fixed(2.71f);
	const Fixed& minConst = Fixed::min(e, f);
	const Fixed& maxConst = Fixed::max(e, f);

	std::cout << "min(e, f): " << minConst.toFloat() << "\n";
	std::cout << "max(e, f): " << maxConst.toFloat() << "\n";

	return 0;
}
