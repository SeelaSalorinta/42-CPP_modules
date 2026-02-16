#include "Fixed.hpp"

Fixed::Fixed() : _fixedPoint(0) {}

Fixed::Fixed(const int valueInt)
{
	_fixedPoint = valueInt << _fractBits;
}

Fixed::Fixed(const float valueFloat)
{
	_fixedPoint = roundf(valueFloat * (1 << _fractBits));
}

Fixed::Fixed(const Fixed& other)
{
	_fixedPoint = other.getRawBits();
}

Fixed&	Fixed::operator=(const Fixed& other)
{
	if (this != &other)
		_fixedPoint = other.getRawBits();
	return (*this);
}

Fixed::~Fixed() {}

int	Fixed::getRawBits() const
{
	return (_fixedPoint);
}

void	Fixed::setRawBits(int const raw)
{
	_fixedPoint = raw;
}

float	Fixed::toFloat( void ) const
{
	return ((float)_fixedPoint / (1 << _fractBits));
}

std::ostream&	operator<<(std::ostream& out, const Fixed& value)
{
	out << value.toFloat();
	return (out);
}

bool	Fixed::operator>(const Fixed& rhs) const
{
	return (this->_fixedPoint > rhs._fixedPoint);
}

bool	Fixed::operator<(const Fixed& rhs) const
{
	return (this->_fixedPoint < rhs._fixedPoint);
}

bool	Fixed::operator>=(const Fixed& rhs) const
{
	return (this->_fixedPoint >= rhs._fixedPoint);
}

bool	Fixed::operator<=(const Fixed& rhs) const
{
	return (this->_fixedPoint <= rhs._fixedPoint);
}

bool	Fixed::operator==(const Fixed& rhs) const
{
	return (this->_fixedPoint == rhs._fixedPoint);
}

bool	Fixed::operator!=(const Fixed& rhs) const
{
	return (this->_fixedPoint != rhs._fixedPoint);
}

Fixed	Fixed::operator+(Fixed const& rhs) const//right hand side so b
{
	return (Fixed(this->toFloat() + rhs.toFloat()));
}

Fixed	Fixed::operator-(Fixed const& rhs) const
{
	return (Fixed(this->toFloat() - rhs.toFloat()));
}

Fixed	Fixed::operator*(Fixed const& rhs) const
{
	return (Fixed(this->toFloat() * rhs.toFloat()));
}

Fixed	Fixed::operator/(Fixed const& rhs) const
{
	return (Fixed(this->toFloat() / rhs.toFloat()));
}

Fixed&	Fixed::operator++() //pre-increment ++a
{
	this->_fixedPoint += 1; //// add smallest amount (ϵ)
	return (*this);
}

Fixed	Fixed::operator++(int) //post-increment a++
{
	Fixed	temp = *this;
	this->_fixedPoint += 1;
	return (temp); //return the orignal value (not the updated value)
}

Fixed&	Fixed::operator--() //pre-decrement --a
{
	this->_fixedPoint -= 1; //// add smallest amount (ϵ)
	return (*this);
}

Fixed	Fixed::operator--(int) //post-decrement a--
{
	Fixed	temp = *this;
	this->_fixedPoint -= 1;
	return (temp); //return the orignal value (not the updated value)
}

Fixed&	Fixed::min(Fixed& a, Fixed& b)
{
	if (a._fixedPoint < b._fixedPoint)
		return (a);
	return (b);
}

const Fixed&	Fixed::min(const Fixed& a, const Fixed& b)
{
	if (a._fixedPoint < b._fixedPoint)
		return (a);
	return (b);
}

Fixed&	Fixed::max(Fixed& a, Fixed& b)
{
	if (a._fixedPoint > b._fixedPoint)
		return (a);
	return (b);
}

const Fixed&	Fixed::max(const Fixed& a, const Fixed& b)
{
	if (a._fixedPoint > b._fixedPoint)
		return (a);
	return (b);
}