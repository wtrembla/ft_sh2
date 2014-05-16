/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 15:47:16 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/16 17:11:34 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void		improper_command(int ret, char *command)
{
	if (ret == -1 && (!ft_strncmp(command, "./", 2)
					|| !ft_strncmp(command, "../", 3) || command[0] == '/'))
		ft_putjoin_fd("ft_sh1: no such file or directory: ", command, 2);
	else if (ret == -1)
		ft_putjoin_fd("ft_sh1: command not found: ", command, 2);
	else if (ret == -2)
		ft_putjoin_fd("ft_sh1: permission denied: ", command, 2);
}

char			*check_command(char *command)
{
	char	*tmp;
	int		i;
	int		ret;
	t_env	*env;

	ret = 0;
	env = init_env(NULL);
	tmp = NULL;
	if ((!ft_strncmp(command, "./", 2) || !ft_strncmp(command, "../", 3)
		|| command[0] == '/') && !(ret = check_path(command)))
		return (ft_strdup(command));
	else if (!ret)
	{
		i = -1;
		while (env->path[++i])
		{
			ft_strdel(&tmp);
			tmp = build_path(env->path[i], command);
			if (!(ret = check_path(tmp)))
				return (tmp);
		}
	}
	improper_command(ret, command);
	ft_strdel(&tmp);
	return (NULL);
}

void			command_proc(char *command)
{
	char	**av;
	char	*tmp1;
	t_data	*data;
	t_fd	*tmp2;

	init_pid();
	av = ft_split(command);
	data = init_data();
	if (av && (tmp1 = check_command(av[0])))
	{
		ft_strdel(&av[0]);
		av[0] = tmp1;
		tmp2 = data->fildes;
		if (tmp2)
		{
			while (tmp2)
			{
				exec_command(av, tmp2->fd);
				tmp2 = tmp2->next;
			}
		}
		else
			exec_command(av, 1);
	}
	update_data(&data);
	del_av(av);
}
