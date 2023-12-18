#include "sort.h"

/**
 * swap_node_ahead - Swap a node in a doubly-linked list of integers
 *                   with the node ahead of it.
 * @list: A pointer to the head of the doubly-linked list.
 * @tail: A pointer to the tail of the doubly-linked list.
 * @shaker: A pointer to the current node being swapped.
 */
void swap_node_ahead(listint_t **list, listint_t **tail, listint_t **shaker)
{
	listint_t *next_node = (*shaker)->next;

	if ((*shaker)->prev != NULL)
		(*shaker)->prev->next = next_node;
	else
		*list = next_node;

	next_node->prev = (*shaker)->prev;
	(*shaker)->next = next_node->next;

	if (next_node->next != NULL)
		next_node->next->prev = *shaker;
	else
		*tail = *shaker;

	(*shaker)->prev = next_node;
	next_node->next = *shaker;
	*shaker = next_node;
}

/**
 * swap_node_behind - Swap a node in a doubly-linked list of integers
 *                    with the node behind it.
 * @list: A pointer to the head of the doubly-linked list.
 * @tail: A pointer to the tail of the doubly-linked list.
 * @shaker: A pointer to the current node being swapped.
 */
void swap_node_behind(listint_t **list, listint_t **tail, listint_t **shaker)
{
	listint_t *prev_node = (*shaker)->prev;

	if ((*shaker)->next != NULL)
		(*shaker)->next->prev = prev_node;
	else
		*tail = prev_node;

	prev_node->next = (*shaker)->next;
	(*shaker)->prev = prev_node->prev;

	if (prev_node->prev != NULL)
		prev_node->prev->next = *shaker;
	else
		*list = *shaker;

	(*shaker)->next = prev_node;
	prev_node->prev = *shaker;
	*shaker = prev_node;
}

/**
 * cocktail_sort_list - Sort a doubly-linked list of integers in
 *                      ascending order using the cocktail shaker algorithm.
 * @list: A pointer to the head of the doubly-linked list.
 */
void cocktail_sort_list(listint_t **list)
{
	listint_t *tail, *shaker;
	bool shaken_not_stirred = false;

	if (list == NULL || *list == NULL || (*list)->next == NULL)
		return;

	for (tail = *list; tail->next != NULL;)
		tail = tail->next;

	while (!shaken_not_stirred)
	{
		shaken_not_stirred = true;

		for (shaker = *list; shaker != tail; shaker = shaker->next)
		{
			if (shaker->n > shaker->next->n)
			{
				swap_node_ahead(list, &tail, &shaker);
				print_list((const listint_t *)*list);
				shaken_not_stirred = false;
			}
		}

		for (shaker = shaker->prev; shaker != *list; shaker = shaker->prev)
		{
			if (shaker->n < shaker->prev->n)
			{
				swap_node_behind(list, &tail, &shaker);
				print_list((const listint_t *)*list);
				shaken_not_stirred = false;
			}
		}
	}
}

