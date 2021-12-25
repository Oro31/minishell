/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/25 01:27:34 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ft_is_nflag(char *arg)
{
	int	i;

	if (arg[0] == '-')
	{
		i = 1;
		while (arg[i] && arg[i] == 'n')
			i++;
		if (arg[i] == '\0' && i > 1)
			return (1);
		else
			return (0);
	}
	return (0);
}

void	ft_echo(char **argv)
{
	int		is_flag;
	int		i;

	g_exit_status = 0;
	if (!argv[1])
		write(1, "\n", 1);
	else
	{
		i = 1;
		while (argv[i] && ft_is_nflag(argv[i]))
			i++;
		if (i == 1)
			is_flag = 0;
		else
			is_flag = 1;
		i--;
		while (argv[++i])
		{
			ft_print_str(argv[i]);
			if (argv[i][0] != '\0')
				write(1, " ", 1);
		}
		if (!is_flag)
			write(1, "\n", 1);
	}
}
