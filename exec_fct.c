/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/15 21:09:35 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/16 18:06:20 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	exec_command(char **av, int fd_out)
{
	t_data	*data;

	data = init_data();
	if (data->tmp_fd != -1)
		get_tmpfd(&data->tmp_fd);
	if ((g_pid.father = fork()) == -1)
		ft_putendl_fd("command_proc: no child process created", 2);
	else
	{
		if (g_pid.father)
			wait(&g_pid.id);
		if (!g_pid.father)
		{
			if (data->tmp_fd != -1)
				dup2(data->tmp_fd, 0);
			dup2(fd_out, 1);
			if (execve(av[0], av, init_env(NULL)->env) == -1)
				ft_errjoin("ft_sh2: command not found: ", av[0]);
		}
	}
}
