/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 12:33:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/24 06:05:07 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>

# include <signal.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <sys/types.h>
# include <sys/select.h>
# include <sys/wait.h>

# define S_QUOTE 39
# define D_QUOTE 34

extern unsigned int		g_exit_status;

typedef struct s_cmd	t_cmd;
typedef struct s_env	t_env;

struct	s_env
{
	char	*name;
	char	*value;
	t_env	*nxt;
};

struct	s_cmd
{
	char	**argv;
	int		is_cmd_after_pipe;
	t_cmd	*nxt;
};

int		ft_is_alpha(char c);
int		ft_is_digit(char c);
int		ft_is_redir(char c);

char	*ft_itoa(int nb);
int		ft_atoi(const char *nptr);

int		ft_parse_error(char *rdline);
int		ft_wrong_exit_arg(char *code);

int		ft_prompt(t_env **env);

t_env	*ft_hadd_tolist_env(t_env *list, char *name, char *value);
t_env	*ft_eadd_tolist_env(t_env *list, char *name, char *value);
t_env	*ft_ndelete_env(t_env *list, int n);
void	ft_free_list_env(t_env **list);

char	**ft_tenv_to_envp(t_env *env);
t_env	*ft_envp_to_tenv(char **env_p);

int		ft_strcomp(char *str1, char *str2);
char	*ft_get_env(t_env *env, char *name);

int		ft_unset(t_env **env, char *name);
int		ft_export(t_env **env, char *arg);
int		ft_pwd(void);
int		ft_exit(t_env **env, t_cmd **cmd, char *code);
void	ft_echo(char **argv);

t_cmd	*ft_hadd_tolist_cmd(t_cmd *list, char **split, int is_pipe);
t_cmd	*ft_eadd_tolist_cmd(t_cmd *list, char **split, int is_pipe);
void	ft_free_list_cmd(t_cmd **list);

int		ft_malloc_dblchar(char ***tmp, int size);
int		ft_malloc_splchar(char **tmp, int size);
int		ft_malloc_dblint(int ***tmp, int size);
int		ft_malloc_splint(int **tmp, int size);

char	**ft_double_realloc(char **str, char ***split);
char	*ft_realloc(char **str, char c);

int		ft_size_list_cmd(t_cmd *list);
void	ft_print_list_cmd(t_cmd *list);
int		ft_size_list_env(t_env *list);
void	ft_print_list_env(t_env *list);

void	ft_print_str(char *str);
int		ft_strlen(char *str);
char	*ft_str_copy(char **str);
char	*ft_str_copy_nofree(char *str);
int		ft_strncomp(char *str, char *comp, int n);

int		ft_is_quote(char c);
int		ft_is_quote_needed(char *arg, int i);

int		ft_is_char_quoted(char *line, int i, int j, char c);

char	**ft_pipe_split(char **rdline);
char	**ft_set_redir(char **pipe_char);

char	**ft_cmdline_split(char **line);

char	**ft_clean_cmdchar(char **cmd_char);

int		ft_is_dollar(char *line, int i);
char	*ft_get_dollar_value(t_env *env, char *str, int i);
int		ft_size_dollar(t_env *env, char *str, int i);

char	**ft_dollar_parse(t_env *env, char **cmd_char);

#endif
