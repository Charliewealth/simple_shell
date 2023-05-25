#include "shell.h"
/**
 * list_len - This code Determines linked list lenght
 * @a: The pointer to the first node.
 *
 * Return: The size of the linked list
 */
size_t list_len(const list_t *a)
{
	size_t j = 0;

	while (a)
	{
		a = a->next;
		j++;
	}
	return (j);
}
/**
 * list_to_strings - It returns an Array of Strings of the list->str
 * @head: The Pointer to the 1st node
 *
 * Return: Array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), y;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; y < i; y++)
				free(strs[y]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}
/**
 * print_list - This code prints all the elements of a list_t (linked list).
 * @a: The pointer to 1st node.
 *
 * Return: The list size.
 */
size_t print_list(const list_t *a)
{
	size_t i = 0;

	while (a)
	{
		_puts(convert_number(a->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		a = a->next;
		i++;
	}
	return (i);
}
/**
 * node_starts_with - This code returns node whose string begin with prefix.
 * @node: The pointer to the head of list.
 * @prefix: The string to be matched.
 * @c: the next char after the prefix to be matched.
 *
 * Return: matched node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
/**
 * get_node_index - This code gets the node index.
 * @head: Pointer to the list head
 * @node: Pointer to the Node.
 *
 * Return: Index of Node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
