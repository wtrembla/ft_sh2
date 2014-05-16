/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfouquet <lfouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 18:00:43 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/14 21:36:01 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int		place_node(int pos, int prev_pos)
{
	if (pos == prev_pos * 2 + 1)
		return (1);
	else if (pos == prev_pos * 2)
		return (0);
	if ((pos % 2) != 0)
		pos = pos - 1;
	pos = pos / 2;
	return (place_node(pos, prev_pos));
}

t_node			*new_node(char *type, char *word, int pos)
{
	t_node		*elem;

	if (!(elem = (t_node *)malloc(sizeof(t_node))))
		ft_error("new_node: memory allocation failed");
	elem->type = ft_strdup(type);
	elem->word = ft_strdup(word);
	elem->pos = pos;
	elem->left = NULL;
	elem->right = NULL;
	return (elem);
}

void			add_node(t_node **tree, t_node *elem)
{
	t_node		*tmp_tree;
	t_node		*tmp_node;

	tmp_tree = *tree;
	if (tmp_tree)
	{
		while (tmp_tree)
		{
			tmp_node = tmp_tree;
			if (place_node(elem->pos, tmp_tree->pos))
			{
				tmp_tree = tmp_tree->right;
				if (!tmp_tree)
					tmp_node->right = elem;
			}
			else
			{
				tmp_tree = tmp_tree->left;
				if (!tmp_tree)
					tmp_node->left = elem;
			}
		}
	}
	else
		*tree = elem;
}

void			del_tree(t_node **tree)
{
	t_node		*tmp;

	tmp = *tree;
	if (tree)
	{
		if (tmp->left)
			del_tree(&tmp->left);
		ft_strdel(&tmp->type);
		ft_strdel(&tmp->word);
		free(tmp);
		if (tmp->right)
			del_tree(&tmp->right);
		*tree = NULL;
	}
}

void			print_tree(t_node *tree, int i)
{
	if (tree->left)
		print_tree(tree->left, 2 * i);
	printf("node = %d, type = %s, word = %s\n", i, tree->type, tree->word);
	if (tree->right)
		print_tree(tree->right, 2 * i + 1);
}
