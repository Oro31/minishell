/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/26 00:04:21 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*ft_set_path(char *path, char *value)
{
	char	*ret;
	int		i;

	ret = NULL;
	i = -1;
	while (path[++i])
		ret = ft_realloc(&ret, path[i]);
	ret = ft_realloc(&ret, '/');
	i = -1;
	while (value[++i])
		ret = ft_realloc(&ret, value[i]);
	return (ret);
}

static int	ft_print_error(char *error, char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	return (127);
}

static char	*ft_find_valid_path(char ***path_split, char *cmd)
{
	char	*path;
	int		i;

	path = NULL;
	i = -1;
	while ((*path_split)[++i])
	{
		path = ft_set_path((*path_split)[i], cmd);
		if (!access(path, X_OK))
		{
			i = -1;
			while ((*path_split)[++i])
			{
				free((*path_split)[i]);
				(*path_split)[i] = NULL;
			}
			free(*path_split);
			*path_split = NULL;
			return (path);
		}
		free(path);
		path = NULL;
	}
	return (NULL);
}

int	ft_hdl_arg_execve(t_env **env, char **argv)
{
	char	**path_split;
	char	*path;

	path = ft_get_env(*env, "PATH");
	if (!path)
		return (ft_print_error("No such file or directory", argv[0]));
	path_split = ft_split(&path, ':');
	path = ft_find_valid_path(&path_split, argv[0]);
	if (path)
	{
		ft_execve(&path, argv, env);
		free(path);
	}
	else
		return (ft_print_error("command not found", argv[0]));
	return (0);
}

int	ft_execve(char **path, char **argv, t_env **env)
{
	pid_t	pid;
	char	**env_p;
	int		status;

	env_p = NULL;
	pid = fork();
	if (!pid)
	{
		env_p = ft_tenv_to_envp(*env);
		if (execve(*path, argv, env_p) < 0)
		{
			ft_free_ctab(&env_p);
			perror(argv[0]);
			return (-1);
		}
	}
	else if (pid < 0)
		write(2, "error pid\n", 10);
	wait(&status);
	return (0);
}
