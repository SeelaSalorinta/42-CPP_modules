#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
	private:
		int					_fixedPoint;
		static const int	_fractBits = 8;

	public:
		Fixed();
		Fixed(const int valueInt);
		Fixed(const float valueFloat);
		Fixed(const Fixed& other);
		Fixed&	operator=(const Fixed& other);
		~Fixed();
		float	toFloat(void) const;
		int		toInt(void) const;
		int		getRawBits(void) const;
		void	setRawBits(int const raw);
};

std::ostream&	operator<<(std::ostream& out, const Fixed& value);

#endif