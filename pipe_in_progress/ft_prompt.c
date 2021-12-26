/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 12:33:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/26 01:30:39 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_init(t_cmd **cmd, char **line)
{
	*cmd = NULL;
	*line = NULL;
}

static int	ft_is_eof(t_env **env, t_cmd **cmd, char **line)
{
	if (!*line)
	{
		free(*line);
		ft_free_list_cmd(cmd);
		ft_free_list_env(env);
		return (1);
	}
	return (0);
}

static void	ft_parse_readline(t_env *env, t_cmd **cmd, char **line)
{
	char	**cmd_char;
	char	**pipe_char;
	int		i;

	pipe_char = NULL;
	pipe_char = ft_pipe_split(line);
	pipe_char = ft_set_redir(pipe_char);
	i = -1;
	while (pipe_char[++i])
	{
		cmd_char = NULL;
		cmd_char = ft_cmdline_split(&pipe_char[i]);
		cmd_char = ft_dollar_parse(env, cmd_char);
		cmd_char = ft_clean_cmdchar(cmd_char);
		*cmd = ft_eadd_tolist_cmd(*cmd, cmd_char, i);
	}
	free(pipe_char);
}

int	ft_prompt(t_env **env)
{
	t_cmd	*cmd;
	char	*line;

	ft_init(&cmd, &line);
	line = readline("$>");
	if (ft_is_eof(env, &cmd, &line))
		return (1);
	if (ft_strlen(line) > 0)
	{
		add_history(line);
		if (!ft_parse_error(line))
		{
			free(line);
			g_exit_status = 2;
			write(2, "syntax error\n", 13);
			return (0);
		}
		ft_parse_readline(*env, &cmd, &line);
		if (cmd->nxt)
			g_exit_status = ft_piping(env, &cmd);
		else if (ft_strcomp("env", cmd->argv[0]) == 0)
			ft_env(*env, cmd->argv);
		else if (ft_strcomp("cd", cmd->argv[0]) == 0)
			ft_hdl_arg_cd(env, cmd->argv);
		else if (ft_strcomp("unset", cmd->argv[0]) == 0)
			ft_hdl_arg_unset(env, cmd->argv);
		else if (ft_strcomp("export", cmd->argv[0]) == 0)
			ft_hdl_arg_export(env, cmd->argv);
		else if (ft_strcomp("pwd", cmd->argv[0]) == 0)
			ft_pwd();
		else if (ft_strcomp("exit", cmd->argv[0]) == 0)
			ft_exit(env, &cmd, &line, cmd->argv[1]);
		else if (ft_strcomp("echo", cmd->argv[0]) == 0)
			ft_echo(cmd->argv);
		else
			g_exit_status = ft_hdl_arg_execve(env, cmd->argv);
	}
	free(line);
	ft_free_list_cmd(&cmd);
	return (0);
}
