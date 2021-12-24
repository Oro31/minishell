/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/24 01:44:42 by rvalton          ###   ########.fr       */
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

int	ft_exit(t_env **env, t_cmd **cmd, char *code)
{
	if (!code)
		;
	else if (ft_wrong_exit_arg(code))
	{
		g_exit_status = 2;
		perror("numeric argument required");
	}
	else
		g_exit_status = ft_atoi(code);
	ft_free_list_cmd(cmd);
	ft_free_list_env(env);
	exit(g_exit_status);
	return (1);
}
