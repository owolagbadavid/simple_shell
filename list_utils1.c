#include "main.h"

/**
 * free_line_list - frees line_list
 * @head: head
 */
void free_line_list(cline_listt **head)
{
	cline_listt *temp;
	cline_listt *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * free_sep_list - frees sep_list
 * @head: head
 */
void free_sep_list(sep_listt **head)
{
	sep_listt *temp;
	sep_listt *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * next_node - next node
 *
 * @sep_l: sep list
 * @line_l: cline list
 * @data: shell data
 */
void next_node(sep_listt **sep_l, cline_listt **line_l, shell_dt *data)
{
	int loop_sep;
	sep_listt *ls_s;
	cline_listt *ls_l;

	loop_sep = 1;
	ls_s = *sep_l;
	ls_l = *line_l;

	while (ls_s != NULL && loop_sep)
	{
		if (data->stat == 0)
		{
			if (ls_s->sep == '&' || ls_s->sep == ';')
				loop_sep = 0;
			if (ls_s->sep == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->sep == '|' || ls_s->sep == ';')
				loop_sep = 0;
			if (ls_s->sep == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*sep_l = ls_s;
	*line_l = ls_l;
}
