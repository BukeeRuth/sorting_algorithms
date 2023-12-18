#include "sort.h"

/**
 * exchange_values - Swap two integers within an array.
 * @first: The first integer to exchange.
 * @second: The second integer to exchange.
 */
void exchange_values(int *first, int *second)
{
	int temporary;

	temporary = *first;
	*first = *second;
	*second = temporary;
}

/**
 * find_maximum - Find the maximum value in an array of integers.
 * @array: An array of integers.
 * @size: The size of the array.
 *
 * Return: The maximum integer in the array.
 */
int find_maximum(int *array, int size)
{
	int maximum, index;

	for (maximum = array[0], index = 1; index < size; index++)
	{
		if (array[index] > maximum)
			maximum = array[index];
	}

	return (maximum);
}

/**
 * counting_sort_radix - Sort the significant digits of an array of integers
 *                       in ascending order using the counting sort algorithm.
 * @array: An array of integers.
 * @size: The size of the array.
 * @significant_digit: The significant digit to sort on.
 * @buffer: A buffer to store the sorted array.
 */
void counting_sort_radix(int *array, size_t size, int significant_digit, int *buffer)
{
	int count[10] = {0};
	size_t index;

	for (index = 0; index < size; index++)
		count[(array[index] / significant_digit) % 10] += 1;

	for (index = 1; index < 10; index++)
		count[index] += count[index - 1];

	for (index = size; index > 0; index--)
	{
		buffer[count[(array[index - 1] / significant_digit) % 10] - 1] = array[index - 1];
		count[(array[index - 1] / significant_digit) % 10] -= 1;
	}

	for (index = 0; index < size; index++)
		array[index] = buffer[index];
}

/**
 * radix_sort - Sort an array of integers in ascending
 *              order using the radix sort algorithm.
 * @array: An array of integers.
 * @size: The size of the array.
 *
 * Description: Implements the LSD radix sort algorithm. Displays
 * the array after each increase in significant digit.
 */
void radix_sort(int *array, size_t size)
{
	int maximum_value, significant_digit, *temporary_buffer;

	if (array == NULL || size < 2)
		return;

	temporary_buffer = malloc(sizeof(int) * size);
	if (temporary_buffer == NULL)
		return;

	maximum_value = find_maximum(array, size);
	for (significant_digit = 1; maximum_value / significant_digit > 0; significant_digit *= 10)
	{
		counting_sort_radix(array, size, significant_digit, temporary_buffer);
		print_array(array, size);
	}

	free(temporary_buffer);
}
