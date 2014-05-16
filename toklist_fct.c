/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toklist_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 15:12:19 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/16 15:20:00 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	create_toklist(t_token **toklist, char *line)
{
	char	*new_line;
	int		i;
	t_ope	operand;

	i = 0;
	operand = init_operand(-1, NULL);
	while (line[i] && !(operand = check_operand(line + i)).name)
		i++;
	if (operand.name
		&& (!ft_strcmp(operand.name, ">") || !ft_strcmp(operand.name, "<")
			|| !ft_strcmp(operand.name, ">>")))
		new_line = tokenize_redir(toklist, line);
	else if (line)
		new_line = tokenize_other(toklist, line);
	if (new_line && *new_line)
		create_toklist(toklist, new_line);
	else
		ft_strdel(&new_line);
}

void	organize_toklist(t_node **tree, t_token **toklist, int pos, int prio)
{
	t_ope	operand;
	t_token	*tmp;

	tmp = *toklist;
	operand = init_operand(-1, NULL);
	while (tmp && tmp->next && tmp->next->type)
	{
		if ((operand = check_operand(tmp->type)).name && operand.prio == prio)
			break ;
		tmp = tmp->next;
	}
	if (operand.name && operand.prio == prio)
	{
		add_node(tree, new_node(tmp->type, tmp->word, pos));
		ft_strdel(&tmp->type);
		organize_toklist(tree, toklist, pos * 2, operand.prio);
		organize_toklist(tree, &tmp->next, pos * 2 + 1, operand.prio);
	}
	else if (prio < 4)
		organize_toklist(tree, toklist, pos, prio + 1);
	else if (tmp && !ft_strcmp(tmp->type, "com"))
		add_node(tree, new_node("com", tmp->word, pos));
}

void	del_toklist(t_token **toklist)
{
	t_token		*tmp;

	tmp = *toklist;
	if (toklist)
	{
		if (tmp->next)
			del_toklist(&tmp->next);
		ft_strdel(&tmp->type);
		ft_strdel(&tmp->word);
		free(tmp);
		*toklist = NULL;
	}
}
