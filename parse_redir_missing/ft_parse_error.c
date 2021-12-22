/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/22 03:43:23 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ft_is_redir(char c)
{
	return (c == '<' || c == '>');
}

static int	ft_is_dbl_pipe(char *rdline, int i)
{
	if (i == 0)
		return (1);
	i++;
	while (rdline[i] == ' ')
		i++;
	if (rdline[i] == '|' || rdline[i] == '\0')
		return (1);
	return (0);
}

static int	ft_is_redir_valid(char *rdline, int i)
{
	int	j;

	j = i;
	if (ft_is_dbl_pipe(rdline, i))
		return (0);
	j++;
	while (rdline[j] == ' ')
		j++;
	if (ft_is_redir(rdline[j]) && j > i + 1)
		return (0);
	else if (ft_is_redir(rdline[j]) && rdline[j] != rdline[i])
		return (0);
	else if (rdline[j] == '\0')
		return (0);
	return (1);
}

int	ft_parse_error(char *rdline)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (rdline[++i])
	{
		if (rdline[i] == '|' && !ft_is_char_quoted(rdline, i, j, rdline[i])
			&& ft_is_dbl_pipe(rdline, i))
			return (0);
		else if (ft_is_redir(rdline[i])
			&& !ft_is_char_quoted(rdline, i, j, rdline[i])
			&& !ft_is_redir_valid(rdline, i))
			return (0);
	}
	return (1);
}
