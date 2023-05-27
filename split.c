#include "main.h"
/**
 * swap_char - Helps to swaps | and & for unprinted chars.
 *
 * @input: The Input str.
 * @bool: The typ of Swap.
 * Return: already swapped str.
 */
char *swap_char(char *input, int bool)
{
	int j;

	if (bool == 0)
	{
		for (j = 0; input[j]; j++)
		{
			if (input[j] == '|')
			{
				if (input[j + 1] != '|')
					input[j] = 16;
				else
					j++;
			}

			if (input[j] == '&')
			{
				if (input[j + 1] != '&')
					input[j] = 12;
				else
					j++;
			}
		}
	}
	else
	{
		for (j = 0; input[j]; j++)
		{
			input[j] = (input[j] == 16 ? '|' : input[j]);
			input[j] = (input[j] == 12 ? '&' : input[j]);
		}
	}
	return (input);
}

/**
 * add_nodes - It Add separators & command lines in d lists.
 *
 * @head_s: The Head of The separat list.
 * @head_l: HEAD of the command line lists.
 * @input: the Input str.
 * Return: nothing
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int b;
	char *line;

	input = swap_char(input, 0);

	for (b = 0; input[b]; b++)
	{
		if (input[b] == ';')
			add_sep_node_end(head_s, input[b]);

		if (input[b] == '|' || input[b] == '&')
		{
			add_sep_node_end(head_s, input[b]);
			b++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swap_char(line, 1);
		add_line_node_end(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * go_next - Helps go to next stored command line.
 *
 * @list_s: The Separator list.
 * @list_l: The Command Line List.
 * @datash: the Data struct.
 * Return: nothing
 */
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	sep_list *ls_s;
	line_list *ls_l;
	int loop_sep;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_commands - It divides (splits) command lines according to
 * their separators ;, | and &, and execute them all
 *
 * @datash: The Data struct.
 * @input: The Input str.
 * Return: 0 to exit, and  1 to continue...
 */
int split_commands(data_shell *datash, char *input)
{

	line_list *head_l, *list_l;
	int loop;
	sep_list *head_s, *list_s;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = split_line(datash->input);
		loop = exec_line(datash);
		free(datash->args);

		if (loop == 0)
			break;

		go_next(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&head_s);
	free_line_list(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_line - This helps to tokenize the input str.
 *
 * @input: The Input str.
 * Return: The string (tokenized)splitted.
 */
char **split_line(char *input)
{
	size_t bsize;
	char **tokens;
	char *token;
	size_t x;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (x = 1; token != NULL; x++)
	{
		if (x == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, x, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[x] = token;
	}

	return (tokens);
}
