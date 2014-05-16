/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/15 20:51:58 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/16 17:04:49 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	update_data(t_data **data)
{
	t_fd	*tmp;

	tmp = (*data)->fildes;
	if ((*data)->fildes)
	{
		while (tmp)
		{
			if (close(tmp->fd) == -1)
				ft_putjoin_fd("update_data: close error: ", tmp->file, 2);
			tmp = tmp->next;
		}
		del_fildes(&(*data)->fildes);
	}
	if ((*data)->tmp_fd != -1)
	{
		if (close((*data)->tmp_fd) == -1)
			ft_putendl_fd("update_data: close error on temporary input", 2);
		(*data)->tmp_fd = -1;
		remove_temporary();
	}
}

t_data	*init_data(void)
{
	static t_data	*data = NULL;

	if (!data)
	{
		if (!(data = (t_data *)malloc(sizeof(t_data))))
			ft_error("init_data: memory allocation failed");
		data->error = -1;
		data->tmp_fd = -1;
		data->fildes = NULL;
	}
	return (data);
}

void	del_fildes(t_fd **fildes)
{
	t_fd	*tmp;

	tmp = *fildes;
	if (*fildes)
	{
		if (tmp->next)
			del_fildes(&tmp->next);
		ft_strdel(&tmp->file);
		free(tmp);
		*fildes = NULL;
	}
}

void	del_data(void)
{
	t_data	*data;

	data = init_data();
	if (data)
	{
		del_fildes(&data->fildes);
		free(data);
		data = NULL;
	}
}
