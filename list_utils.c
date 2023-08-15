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
