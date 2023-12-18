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
 * heapify - Convert a binary tree into a complete binary heap.
 * @array: An array of integers representing a binary tree.
 * @size: The size of the array/tree.
 * @base: The index of the base row of the tree.
 * @root: The root node of the binary tree.
 */
void heapify(int *array, size_t size, size_t base, size_t root)
{
	size_t left_child, right_child, largest_node;

	left_child = 2 * root + 1;
	right_child = 2 * root + 2;
	largest_node = root;

	if (left_child < base && array[left_child] > array[largest_node])
		largest_node = left_child;

	if (right_child < base && array[right_child] > array[largest_node])
		largest_node = right_child;

	if (largest_node != root)
	{
		exchange_values(array + root, array + largest_node);
		print_array(array, size);
		heapify(array, size, base, largest_node);
	}
}

/**
 * heap_sort - Arrange an array of integers in ascending order
 *             using the heap sort algorithm.
 * @array: An array of integers.
 * @size: The size of the array.
 *
 * Description: Implements the sift-down heap sort
 * algorithm. Displays the array after each exchange.
 */
void heap_sort(int *array, size_t size)
{
	int index;

	if (array == NULL || size < 2)
		return;

	for (index = (size / 2) - 1; index >= 0; index--)
		heapify(array, size, size, index);

	for (index = size - 1; index > 0; index--)
	{
		exchange_values(array, array + index);
		print_array(array, size);
		heapify(array, size, index, 0);
	}
}

