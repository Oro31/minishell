/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/24 22:04:11 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_wrong_exit_arg(char *code)
{
	int	i;

	i = 0;
	while (ft_is_digit(code[i]))
		i++;
	if (i > 3 || code[i] != '\0' || ft_atoi(code) > 255)
		return (1);
	else
		return (0);
}

int	ft_exit(t_env **env, t_cmd **cmd, char **line, char *code)
{
	write(1, "exit\n", 5);
	if (!code)
		;
	else if (ft_wrong_exit_arg(code))
	{
		g_exit_status = 2;
		write(2, "exit: ", 6);
		write(2, code, ft_strlen(code));
		write(2, ": numeric argument required\n", 28);
	}
	else
		g_exit_status = ft_atoi(code);
	free(*line);
	ft_free_list_cmd(cmd);
	ft_free_list_env(env);
	exit(g_exit_status);
	return (1);
}
