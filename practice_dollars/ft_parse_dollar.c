/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 08:36:54 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/21 18:44:20 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*the function ft_dollar_parse is used to replace $abcd
by the value of the the environnement variable abcd
everything not returned is freed
the function return a table of strings
that you will have to free before the end of your program*/

static int	ft_moove_index(char *str, int i)
{
	int	j;

	j = i;
	if (str[i + 1] == '?')
		return (j + 2);
	while (ft_is_digit(str[++j]) || ft_is_alpha(str[j]) || str[j] == '_')
		;
	return (j);
}

static void	ft_fill_dollar(char **tmp, char *str)
{
	char	*dol;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = -1;
	while (str[++i])
	{
		if (ft_is_dollar(str, i))
		{
			dol = ft_get_dollar_value(str, i);
			k = -1;
			while (dol[++k])
				(*tmp)[++j] = dol[k];
			i = ft_moove_index(str, i);
		}
		(*tmp)[++j] = str[i];
		if (!str[i])
			i--;
	}
}

static char	*ft_interpret_dollar(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (ft_is_dollar(str, i))
		{
			printf("dollar found\n");
			j = j + ft_size_dollar(str, i);
		}
		else
			j++;
	}
	if (!ft_malloc_splchar(&tmp, j + 1))
		return (NULL);
	ft_fill_dollar(&tmp, str);
	return (tmp);
}

char	**ft_dollar_parse(char **cmd_char)
{
	char	**tmp;
	int		i;

	i = 0;
	while (cmd_char[i])
		i++;
	if (!ft_malloc_dblchar(&tmp, i + 1))
		return (NULL);
	i = -1;
	while (cmd_char[++i])
	{
		tmp[i] = ft_interpret_dollar(cmd_char[i]);
		free(cmd_char[i]);
	}
	free(cmd_char);
	return (tmp);
}
