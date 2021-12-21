/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 08:36:54 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/21 19:30:00 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*this static function try to know if the special char 
$ is between double quotes,
at these stage we already know thaat $ is between quotes*/

static int	ft_is_double_quoted(char *line, int i)
{
	int	dq_open;
	int	j;

	dq_open = 0;
	j = -1;
	while (++j < i)
	{
		if (line[j] == D_QUOTE && !dq_open)
			dq_open = 1;
		else if (line[j] == D_QUOTE && dq_open)
			dq_open = 0;
	}
	if (!dq_open)
		return (0);
	while (line[++j] && line[j] != D_QUOTE)
		;
	if (line[j] == D_QUOTE)
		return (1);
	else
		return (0);
}

/*this function try to know if the special char $ will be interpret as
a special char or as a normal char*/

int	ft_is_dollar(char *line, int i)
{
	if (line[i] == '$')
	{
		if (!ft_is_char_quoted(line, i, 0, line[i])
			|| ft_is_double_quoted(line, i))
			return (1);
	}
	return (0);
}

/*this function try to find the value of the environnement
variable refered by the str stuck to the secial char $
at these stage we know that the special char $ need to be interpreted*/

char	*ft_get_dollar_value(char *str, int i)
{
	char	*env_name;
	int		j;

	env_name = NULL;
	printf("let's get dollar value\n");
	j = i;
	if (str[j + 1] == '?')
		return (ft_itoa(g_exit_status));
	while (ft_is_digit(str[++j]) || ft_is_alpha(str[j]) || str[j] == '_')
		;
	if (!ft_malloc_splchar(&env_name, j - i + 1))
		return (NULL);
	j = i;
	while (ft_is_digit(str[++j]) || ft_is_alpha(str[j]) || str[j] == '_')
		env_name[j - i - 1] = str[j];
	return (getenv(env_name));
}

/*this function try to find the size of value of the environnement
 variable refered by the str stuck to the special char $
at these stage we know that the special char $ need to be interpreted*/

int	ft_size_dollar(char *str, int i)
{
	char	*dollar_value;
	int		size;

	dollar_value = NULL;
	if (str[i + 1] == '?')
	{
		dollar_value = ft_itoa(g_exit_status);
		size = ft_strlen(dollar_value);
		free(dollar_value);
		return (size);
	}
	dollar_value = ft_get_dollar_value(str, i);
	size = ft_strlen(dollar_value);
	free(dollar_value);
	return (size);
}
