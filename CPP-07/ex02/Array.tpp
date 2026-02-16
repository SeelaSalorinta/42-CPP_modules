#pragma once

template <typename T>
Array<T>::Array() : _array(nullptr), _size(0) {}

template <typename T>
Array<T>::Array(unsigned int size) : _array(nullptr), _size(size)
{
	if (_size > 0)
		_array = new T[_size]();
}

template <typename T>
Array<T>::Array(const Array &other) : _array(nullptr), _size(other._size)
{
	if (_size > 0)
	{
		_array = new T[_size];
		for (std::size_t i = 0; i < _size; i++)
			_array[i] = other._array[i];
	}
}

template <typename T>
Array<T>&	Array<T>::operator=(const Array &other)
{
	if (this != &other)
	{
		delete[] _array;
		_size = other._size;
		_array = nullptr;
		if (_size > 0)
		{
			_array = new T[_size];
			for (std::size_t i = 0; i < _size; i++)
				_array[i] = other._array[i];
		}
	}
	return *this;
}

template <typename T>
Array<T>::~Array()
{
	delete[] _array;
}

template <typename T>
T&	Array<T>::operator[](unsigned int index)
{
	if (index >= _size)
		throw std::out_of_range("Given index is out of range");
	return (_array[index]);
}

template <typename T>
const T&	Array<T>::operator[](unsigned int index) const
{
	if (index >= _size)
		throw std::out_of_range("Given index is out of range");
	return (_array[index]);
}

template <typename T>
unsigned int	Array<T>::size() const
{
	return _size;
}
