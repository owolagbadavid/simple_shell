#include "main.h"

/**
 * add_var_list_node - adds var to list end
 *
 * @head: head
 * @var_len: varlen
 * @val: value
 * @val_len: vallen
 *
 * Return: list add
 */
var_listt *add_var_list_node(var_listt **head,
		int var_len, char *val, int val_len)
{
	var_listt *new, *tmp;

	new = malloc(sizeof(var_listt));
	if (new == NULL)
		return (NULL);

	new->var_len = var_len;
	new->val = val;
	new->val_len = val_len;

	new->next = NULL;
	tmp = *head;

	if (tmp == NULL)
	{
		*head = new;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}

	return (*head);
}

/**
 * free_var_list - free list
 * @head: head
 */
void free_var_list(var_listt **head)
{
	var_listt *tmp, *cur;

	if (head != NULL)
	{
		cur = *head;
		while ((tmp = cur) != NULL)
		{
			cur = cur->next;
			free(tmp);
		}
		*head = NULL;
	}
}

/**
 * add_nodes - add seps and clines
 *
 * @sep_head: head sep
 * @line_head: head cmd line
 * @input: input
 */
void add_nodes(sep_listt **sep_head, cline_listt **line_head, char *input)
{
	int i;
	char *line;

	input = swap_chars(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_sep_node(sep_head, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_sep_node(sep_head, input[i]);
			i++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swap_chars(line, 1);
		add_line_node(line_head, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);
}

/**
 * add_sep_node - adds sep to tail
 * @head: head
 * @sep: sep
 * Return: head
 */
sep_listt *add_sep_node(sep_listt **head, char sep)
{
	sep_listt *new, *temp;

	new = malloc(sizeof(sep_listt));
	if (new == NULL)
		return (NULL);

	new->sep = sep;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * add_line_node - adds cline to tail
 * @head: head
 * @line: cline
 * Return: head
 */
cline_listt *add_line_node(cline_listt **head, char *line)
{
	cline_listt *new, *temp;

	new = malloc(sizeof(cline_listt));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}
