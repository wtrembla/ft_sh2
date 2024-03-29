/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_setenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 19:10:27 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/13 17:47:40 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int		var_isvalid(char *var)
{
	if (ft_strchr(var, '='))
	{
		ft_putendl_fd("setenv: syntax error", 2);
		return (0);
	}
	return (1);
}

static void		add_var(char **av, t_env **env)
{
	char	**senv;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((*env)->env && (*env)->env[i])
		i++;
	if (!(senv = (char **)malloc(sizeof(char *) * (i + 2))))
	{
		ft_putendl_fd("add_var: memory allocation failed", 2);
		return ;
	}
	while ((*env)->env && (*env)->env[j])
	{
		senv[j] = ft_strdup((*env)->env[j]);
		j++;
	}
	tmp = ft_strjoin(av[1], "=");
	senv[j] = av[2] != NULL ? ft_strjoin(tmp, av[2]) : ft_strdup(tmp);
	ft_strdel(&tmp);
	senv[++j] = NULL;
	del_av((*env)->env);
	(*env)->env = senv;
}

int				update_var(t_env **env, char *var, char *value)
{
	char	*tmp;
	int		i;

	i = 0;
	while ((*env)->env && (*env)->env[i]
			&& ft_strncmp((*env)->env[i], var, ft_strlen(var)))
		i++;
	if ((*env)->env[i])
	{
		ft_strdel(&(*env)->env[i]);
		tmp = ft_strjoin(var, "=");
		(*env)->env[i] = ft_strjoin(tmp, value);
		ft_strdel(&tmp);
		return (1);
	}
	return (0);
}

void			apply_setenv(char *command)
{
	char	**av;
	int		size;
	t_env	*env;

	av = ft_strsplit(command, ' ');
	size = av_size(av);
	env = init_env(NULL);
	if (size == 1)
		apply_env(command);
	else if (size > 3)
		ft_putendl_fd("setenv: too many arguments", 2);
	else
	{
		if (var_isvalid(av[1]) && !(update_var(&env, av[1], av[2])))
			add_var(av, &env);
	}
	del_av(av);
}
