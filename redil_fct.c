/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redil_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 14:50:09 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/16 18:11:47 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "ft_minishell.h"

void			get_tmpfd(int *tmp_fd)
{
	char	*tmp_path;

	tmp_path = ft_strjoin(init_env(NULL)->home, "/.temporary");
	if ((*tmp_fd = open(tmp_path, O_RDWR | O_APPEND | O_CREAT, 0644)) == -1)
		ft_putendl_fd("get_tmpfd: temporary input not created", 2);
	ft_strdel(&tmp_path);
}

static void		write_redilfile(char *file, int fd_out)
{
	char	*line;
	int		fd_in;

	if ((fd_in = open(file, O_RDONLY)) == -1)
		ft_putjoin_fd("write_redilfile: open error: ", file, 2);
	else
	{
		while (get_next_line(fd_in, &line) > 0)
		{
			ft_putendl_fd(line, fd_out);
			ft_strdel(&line);
		}
		if (close(fd_in) == -1)
			ft_putjoin_fd("write_redilfile: close error: ", file, 2);
	}
}

void			remove_temporary(void)
{
	char	**cmd;
	char	*cmd_path;
	char	*tmp;
	char	*tmp_path;
	pid_t	father;

	tmp_path = ft_strjoin(init_env(NULL)->home, "/.temporary");
	tmp = ft_strjoin("rm -rf ", tmp_path);
	cmd = ft_split(tmp);
	ft_strdel(&tmp_path);
	ft_strdel(&tmp);
	if ((cmd_path = check_command(cmd[0])))
	{
		if ((father = fork()) == -1)
			ft_putendl_fd("remove_temporary: no child process created", 2);
		else
		{
			if (father)
				wait(0);
			if (father == 0)
			{
				if (execve(cmd_path, cmd, init_env(NULL)->env) == -1)
					ft_error("remove_temporary: temporary input not removed");
			}
		}
	}
	del_av(cmd);
	ft_strdel(&cmd_path);
}

void			redil_proc(t_node *tree)
{
	char	*file;
	t_data	*data;

	file = ft_strtrim(tree->left->word);
	data = init_data();
	get_tmpfd(&data->tmp_fd);
	if (data->tmp_fd != -1)
	{
		write_redilfile(file, data->tmp_fd);
		close(data->tmp_fd);
	}
	ft_strdel(&file);
	read_tree(tree->right);
}
