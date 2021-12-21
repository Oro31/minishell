/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 12:33:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/21 15:59:34 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

struct	s_cmd
{
	char	**argv;
	int		is_cmd_after_pipe;
	t_cmd	*nxt;
};

int		ft_parse_error(char *rdline);

int		ft_prompt(void);

t_cmd	*ft_hadd_tolist_cmd(t_cmd *list, char **split, int is_pipe);
t_cmd	*ft_eadd_tolist_cmd(t_cmd *list, char **split, int is_pipe);
void	ft_free_list_cmd(t_cmd **list);

int		ft_malloc_dblchar(char ***tmp, int size);
int		ft_malloc_splchar(char **tmp, int size);

char	**ft_double_realloc(char **str, char ***split);
char	*ft_realloc(char **str, char c);

int		ft_size_list_cmd(t_cmd *list);
void	ft_print_list_cmd(t_cmd *list);

void	ft_print_str(char *str);
int		ft_strlen(char *str);
char	*ft_str_copy(char **str);
int		ft_strncomp(char *str, char *comp, int n);

int		ft_is_quote(char c);
int		ft_is_quote_needed(char *arg, int i);

int		ft_is_char_quoted(char *line, int i, int j, char c);

char	**ft_pipe_split(char **rdline);

char	**ft_cmdline_split(char **line);

char	**ft_clean_cmdchar(char **cmd_char);

int		ft_is_dollar(char *line, int i);
char	*ft_get_dollar_value(char *str, int i);
int		ft_size_dollar(char *str, int i);

char	**ft_dollar_parse(char **cmd_char);

#endif
