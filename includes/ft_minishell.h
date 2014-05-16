/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/22 13:56:53 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/16 17:52:19 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

/*
** include
*/
# include "get_next_line.h"
# include "libft.h"

# include <stdio.h>

/*
** define
*/
# define BUILT_NUM 5
# define OPE_NUM 5

/*
** typedef
*/

typedef struct			s_built
{
	char				*name;
	void				(*apply_built)(char *);
}						t_built;

typedef struct			s_fd
{
	char				*file;
	int					fd;
	struct s_fd			*next;
}						t_fd;

typedef struct			s_data
{
	int					error;
	int					tmp_fd;
	t_fd				*fildes;
}						t_data;

typedef struct			s_env
{
	char				**env;
	char				**path;
	char				*pwd;
	char				*oldpwd;
	char				*home;
}						t_env;

typedef struct			s_id
{
	int					built;
	int					id;
	pid_t				child;
	pid_t				father;
}						t_id;

typedef struct			s_node
{
	char				*type;
	char				*word;
	int					pos;
	struct s_node		*left;
	struct s_node		*right;
}						t_node;

typedef struct			s_ope
{
	char				*name;
	int					prio;
}						t_ope;

typedef struct			s_proc
{
	char				*operand;
	void				(*apply_proc)(t_node *);
}						t_proc;

typedef struct stat		t_stat;

typedef struct			s_token
{
	char				*type;
	char				*word;
	int					prio;
	struct s_token		*next;
}						t_token;

/*
** global
*/
t_id					g_pid;

/*
** built_cd.c
*/
void					apply_cd(char *command);

/*
** built_env.c
*/
void					apply_env(char *command);

/*
** built_exit.c
*/
void					apply_exit(char *command);

/*
** built_setenv.c
*/
void					apply_setenv(char *command);
int						update_var(t_env **env, char *var, char *value);

/*
** built_unsetenv.c
*/
void					apply_unsetenv(char *command);

/*
** builtins.c
*/
int						check_builtin(char *command);
void					del_builtin(void);
t_built					*init_builtin(void);

/*
** command_fct.c
*/
char					*check_command(char *command);
void					command_proc(char *command);

/*
** data_fct.c
*/
void					del_data(void);
void					del_fildes(t_fd **fd);
t_data					*init_data(void);
void					update_data(t_data **data);

/*
** environ_fct.c
*/
char					**copy_env(char **environ);
char					*copy_home(char **environ);
char					*copy_oldpwd(char **environ);
char					**copy_path(char **environ);
char					*copy_pwd(char **environ);

/*
** exec_fct.c
*/
void					exec_command(char **av, int fd_out);

/*
** ft_error.c
*/
void					ft_error(char *str);

/*
** ft_errjoin.fr
*/
void					ft_errjoin(char *str1, char *str2);

/*
** ft_split.c
*/
char					**ft_split(char *str);

/*
** lexer_fct.c
*/
char					*tokenize_other(t_token **toklist, char *line);
char					*tokenize_redir(t_token **toklist, char *line);

/*
** main.c
*/
void					del_env(void);
void					display_prompt(void);
t_env					*init_env(char **environ);

/*
** minishell.c
*/
int						av_size(char **av);
void					del_av(char **av);
void					minishell(void);

/*
** operand_fct.c
*/
t_ope					check_operand(char *type);
void					del_opetab(void);
t_ope					init_operand(int prio, char *name);
t_ope					*init_opetab(void);

/*
** path_fct.c
*/
char					*build_path(char *path, char *command);
int						check_path(char *path);

/*
** pipe_fct.c
*/
void					pipe_proc(t_node *tree);

/*
** process_fct.c
*/
void					del_proctab(void);
t_proc					*init_proctab(void);
void					read_tree(t_node *tree);

/*
** redil_fct.c
*/
void					get_tmpfd(int *tmp_fd);
void					redil_proc(t_node *tree);
void					remove_temporary(void);

/*
** redir_fct.c
*/
void					redir_proc(t_node *tree);

/*
** redirr_fct.c
*/
void					redirr_proc(t_node *tree);

/*
** scolon_fct.c
*/
void					scolon_proc(t_node *tree);

/*
** signal_fct.c
*/
void					catch_signal(void);
void					init_pid(void);

/*
** toklist_fct.c
*/
void					create_toklist(t_token **toklist, char *line);
void					del_toklist(t_token **toklist);
void					organize_toklist(t_node **tree, t_token **toklist,
										 int pos, int prio);
/*
** tree_fct.c
*/
void					add_node(t_node **tree, t_node *elem);
void					del_tree(t_node **tree);
t_node					*new_node(char *type, char *word, int pos);
void					print_tree(t_node *tree, int i);

#endif
