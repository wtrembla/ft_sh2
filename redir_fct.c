/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/15 20:01:14 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/16 15:30:39 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "ft_minishell.h"

static void		add_fd(t_fd **fildes, int fd, char *file)
{
	t_fd	*elem;
	t_fd	*tmp;

	if (!(elem = (t_fd *)malloc(sizeof(t_fd))))
		ft_error("add_fd: memory allocation failed");
	elem->fd = fd;
	elem->file = ft_strdup(file);
	elem->next = NULL;
	tmp = *fildes;
	if (*fildes)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
	}
	else
		*fildes = elem;
}

void			redir_proc(t_node *tree)
{
	char	*file;
	int		fd;
	t_data	*data;

	file = ft_strtrim(tree->left->word);
	data = init_data();
	if ((fd = open(file, O_WRONLY | O_CREAT, 0644)) == -1)
		ft_putjoin_fd("redir_proc: outfile not created: ", file, 2);
	else
		add_fd(&data->fildes, fd, file);
	ft_strdel(&file);
	read_tree(tree->right);
}
