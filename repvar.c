#include "main.h"
/**
 * check_env - Helps to check if  typed var. is an environ var.
 *
 * @h: The Head of the Linked List.
 * @in: The Input str.
 * @data: The data struct.
 * Return: nothing
 */
void check_env(r_var **h, char *in, data_shell *data)
{
	int mcb, chi, j, uwa;
	char **_envr;

	_envr = data->_environ;
	for (mcb = 0; _envr[mcb]; mcb++)
	{
		for (j = 1, chi = 0; _envr[mcb][chi]; chi++)
		{
			if (_envr[mcb][chi] == '=')
			{
				uwa = _strlen(_envr[mcb] + chi + 1);
				add_rvar_node(h, j, _envr[mcb] + chi + 1, uwa);
				return;
			}

			if (in[j] == _envr[mcb][chi])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	add_rvar_node(h, j, NULL, 0);
}

/**
 * check_vars - Helps to check if typed var is one of these $$ or $?.
 *
 * @h: The linked_list head.
 * @in: The Input str.
 * @st: Shell's last status.
 * @data: The data struct.
 * Return: nothing
 */
int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int x, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (x = 0; in[x]; x++)
	{
		if (in[x] == '$')
		{
			if (in[x + 1] == '?')
				add_rvar_node(h, 2, st, lst), x++;
			else if (in[x + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpd), x++;
			else if (in[x + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[x + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[x + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[x + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[x + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + x, data);
		}
	}

	return (x);
}

/**
 * replaced_input - It helps to replace str into var.
 *
 * @head: The Head oflinked_list
 * @input: The Input str.
 * @new_input: New Input str.
 * @nlen: The New Length.
 * Return: already replaced str.
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int a, b, c;

	indx = *head;
	for (b = a = 0; a < nlen; a++)
	{
		if (input[b] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[a] = input[b];
				b++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (c = 0; c < indx->len_var; c++)
					b++;
				a--;
			}
			else
			{
				for (c = 0; c < indx->len_val; c++)
				{
					new_input[a] = indx->val[c];
					a++;
				}
				b += (indx->len_var);
				a--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[a] = input[b];
			b++;
		}
	}

	return (new_input);
}

/**
 * rep_var - Helps to call fxns to replace str. into vars.
 *
 * @input: The Input str.
 * @datash: The data struct
 * Return: already replaced str.
 */
char *rep_var(char *input, data_shell *datash)
{
	r_var *head, *indx;
	int olen, nlen;
	char *status, *new_input;

	status = aux_itoa(datash->status);
	head = NULL;

	olen = check_vars(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}
