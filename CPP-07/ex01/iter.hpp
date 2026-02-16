#pragma once

#include <cstddef>

template <typename T, typename F>
void	iter(T *array, std::size_t length, F function)
{
	if (!array)
		return;
	for (std::size_t i = 0; i < length; i++)
		function(array[i]);
}