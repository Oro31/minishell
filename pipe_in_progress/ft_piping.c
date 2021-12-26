/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_piping.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/26 01:29:03 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_piping(t_env **env, t_cmd **cmd)
{
	t_cmd	*tmp;
	pid_t	pid;
	int		pipe_fd[2];
	int		oldfd;
	int		ret;
	int		status;
	int		i;

	i = 0;
	tmp = *cmd;
	oldfd = dup(STDIN_FILENO);
	while (tmp)
	{
		pipe(pipe_fd);
		pid = fork();
		if (!pid)
		{
			if (i != 0)
				dup2(oldfd, STDIN_FILENO);
			if (tmp->nxt)
				dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			close(oldfd);
			ret = ft_hdl_arg_execve(env, tmp->argv);
			if (ret < 0 || ret == 127)
				perror(tmp->argv[0]);
			exit(ret);
		}
		else if (pid < 0)
			write(2, "error pid\n", 10);
		dup2(pipe_fd[0], oldfd);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		tmp = tmp->nxt;
		i++;
	}
	close(oldfd);
	i = -1;
	while (++i < ft_size_list_cmd(*cmd))
		wait(&status);
	return (0);
}
