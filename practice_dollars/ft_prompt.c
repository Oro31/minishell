/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 12:33:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/21 18:39:33 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_init_pointers(t_cmd **cmd, char **line)
{
	*cmd = NULL;
	*line = NULL;
}

static int	ft_is_eof(char *line)
{
	if (!line)
	{
		free(line);
		return (1);
	}
	return (0);
}

static void	ft_parse_readline(t_cmd **cmd, char **line)
{
	char	**cmd_char;
	char	**pipe_char;
	int		i;

	cmd_char = NULL;
	pipe_char = NULL;
	pipe_char = ft_pipe_split(line);
	i = -1;
	while (pipe_char[++i])
	{
		cmd_char = ft_cmdline_split(&pipe_char[i]);
		cmd_char = ft_clean_cmdchar(cmd_char);
		cmd_char = ft_dollar_parse(cmd_char);
		*cmd = ft_eadd_tolist_cmd(*cmd, cmd_char, i);
	}
	free(pipe_char);
}

int	ft_prompt(void)
{
	t_cmd	*cmd;
	char	*line;

	ft_init_pointers(&cmd, &line);
	line = readline("$>");
	if (ft_is_eof(line))
		return (1);
	if (ft_strlen(line) > 0)
	{
		add_history(line);
		if (!ft_parse_error(line))
		{
			free(line);
			printf("syntax error\n");
			return (0);
		}
		ft_parse_readline(&cmd, &line);
		ft_print_list_cmd(cmd);
	}
	if (!cmd)
		free(line);
	else
		ft_free_list_cmd(&cmd);
	return (0);
}
