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
 * bitonic_merge - Sort a bitonic sequence within an array of integers.
 * @array: An array of integers.
 * @size: The size of the array.
 * @start: The starting index of the sequence to sort.
 * @sequence_size: The size of the sequence to sort.
 * @flow_direction: The direction to sort in.
 */
void bitonic_merge(int *array, size_t size, size_t start, size_t sequence_size, char flow_direction)
{
	size_t i, jump = sequence_size / 2;

	if (sequence_size > 1)
	{
		for (i = start; i < start + jump; i++)
		{
			if ((flow_direction == 'U' && array[i] > array[i + jump]) ||
					(flow_direction == 'D' && array[i] < array[i + jump]))
				exchange_values(array + i, array + i + jump);
		}
		bitonic_merge(array, size, start, jump, flow_direction);
		bitonic_merge(array, size, start + jump, jump, flow_direction);
	}
}

/**
 * bitonic_sequence - Convert an array of integers into a bitonic sequence.
 * @array: An array of integers.
 * @size: The size of the array.
 * @start: The starting index of a block of the building bitonic sequence.
 * @block_size: The size of a block of the building bitonic sequence.
 * @flow_direction: The direction to sort the bitonic sequence block in.
 */
void bitonic_sequence(int *array, size_t size, size_t start, size_t block_size, char flow_direction)
{
	size_t cut = block_size / 2;
	const char *direction_str = (flow_direction == 'U') ? "UP" : "DOWN";

	if (block_size > 1)
	{
		printf("Merging [%lu/%lu] (%s):\n", block_size, size, direction_str);
		print_array(array + start, block_size);

		bitonic_sequence(array, size, start, cut, 'U');
		bitonic_sequence(array, size, start + cut, cut, 'D');
		bitonic_merge(array, size, start, block_size, flow_direction);

		printf("Result [%lu/%lu] (%s):\n", block_size, size, direction_str);
		print_array(array + start, block_size);
	}
}

/**
 * bitonic_sort - Sort an array of integers in ascending
 *                order using the bitonic sort algorithm.
 * @array: An array of integers.
 * @size: The size of the array.
 *
 * Description: Prints the array after each swap. Only works for
 * size = 2^k where k >= 0 (i.e., size equal to powers of 2).
 */
void bitonic_sort(int *array, size_t size)
{
	if (array == NULL || size < 2)
		return;

	bitonic_sequence(array, size, 0, size, 'U');
}

