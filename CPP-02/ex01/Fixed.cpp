#include "Fixed.hpp"

Fixed::Fixed() : _fixedPoint(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int valueInt)
{
	std::cout << "Int constructor called" << std::endl;
	_fixedPoint = valueInt << _fractBits;
}

Fixed::Fixed(const float valueFloat)
{
	std::cout << "Float constructor called" << std::endl;
	_fixedPoint = roundf(valueFloat * (1 << _fractBits));
}

Fixed::Fixed(const Fixed& other)
{
	std::cout << "Copy constructor called" << std::endl;
	_fixedPoint = other.getRawBits();
}

Fixed&	Fixed::operator=(const Fixed& other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
		_fixedPoint = other.getRawBits();
	return (*this);
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

float	Fixed::toFloat() const
{
	return ((float)_fixedPoint / (1 << _fractBits));
}

int	Fixed::toInt() const
{
	return (_fixedPoint >> _fractBits);
}

int	Fixed::getRawBits() const
{
	return (_fixedPoint);
}

void	Fixed::setRawBits(int const raw)
{
	_fixedPoint = raw;
}

std::ostream&	operator<<(std::ostream& out, const Fixed& value)
{
	out << value.toFloat();
	return (out);
}