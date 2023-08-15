#include "main.h"

/**
 * vars_sub - var substitution
 *
 * @input: input
 * @data: shell data
 * Return: str
 */
char *vars_sub(char *input, shell_dt *data)
{
	var_listt *head, *temp;
	char *status, *new_input;
	int old_len, new_len;

	status = _itoa(data->stat);
	head = NULL;

	old_len = vars_check(&head, input, status, data);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	temp = head;
	new_len = 0;

	while (temp != NULL)
	{
		new_len += (temp->val_len - temp->var_len);
		temp = temp->next;
	}

	new_len += old_len;

	new_input = malloc(sizeof(char) * (new_len + 1));
	new_input[new_len] = '\0';

	new_input = var_val_sub(&head, input, new_input, new_len);

	free(input);
	free(status);
	free_var_list(&head);

	return (new_input);
}

/**
 * vars_check - check vars
 *
 * @head: head of linked list
 * @input: input
 * @status: shell status
 * @data: shell data
 *
 * Return: int
 */
int vars_check(var_listt **head, char *input, char *status, shell_dt *data)
{
	int i, stat_len, pid_len;

	stat_len = _strlen(status);
	pid_len = _strlen(data->pid);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == '$')
		{
			if (input[i + 1] == '?')
				add_var_list_node(head, 2, status, stat_len), i++;
			else if (input[i + 1] == '$')
				add_var_list_node(head, 2, data->pid, pid_len), i++;
			else if (input[i + 1] == '\n')
				add_var_list_node(head, 0, NULL, 0);
			else if (input[i + 1] == '\0')
				add_var_list_node(head, 0, NULL, 0);
			else if (input[i + 1] == ' ')
				add_var_list_node(head, 0, NULL, 0);
			else if (input[i + 1] == '\t')
				add_var_list_node(head, 0, NULL, 0);
			else if (input[i + 1] == ';')
				add_var_list_node(head, 0, NULL, 0);
			else
				check_env(head, input + i, data);
		}
	}

	return (i);
}

/**
 * check_env - checks for env variable
 *
 * @head: head of linked list
 * @input: input
 * @data: shell data
 */
void check_env(var_listt **head, char *input, shell_dt *data)
{
	int row, col, j, val_len;
	char **_envar;

	_envar = data->_env;
	for (row = 0; _envar[row]; row++)
	{
		for (j = 1, col = 0; _envar[row][col]; col++)
		{
			if (_envar[row][col] == '=')
			{
				val_len = _strlen(_envar[row] + col + 1);
				add_var_list_node(head, j, _envar[row] + col + 1, val_len);
				return;
			}

			if (input[j] == _envar[row][col])
				j++;
			else
				break;
		}
	}

	for (j = 0; input[j]; j++)
	{
		if (input[j] == ' ' || input[j] == ';'
				|| input[j] == '\t' || input[j] == '\n')
			break;
	}

	add_var_list_node(head, j, NULL, 0);
}

/**
 * var_val_sub - sub var and val
 *
 * @head: head
 * @input: input
 * @replc_str: str
 * @new_len: new length
 * Return: str
 */
char *var_val_sub(var_listt **head, char *input, char *replc_str, int new_len)
{
	var_listt *temp;
	int i, j, k;

	temp = *head;
	for (j = i = 0; i < new_len; i++)
	{
		if (input[j] == '$')
		{
			if (!(temp->var_len) && !(temp->val_len))
			{
				replc_str[i] = input[j];
				j++;
			}
			else if (temp->var_len && !(temp->val_len))
			{
				for (k = 0; k < temp->var_len; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < temp->val_len; k++)
				{
					replc_str[i] = temp->val[k];
					i++;
				}
				j += (temp->var_len);
				i--;
			}
			temp = temp->next;
		}
		else
		{
			replc_str[i] = input[j];
			j++;
		}
	}

	return (replc_str);
}
