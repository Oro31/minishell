/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/22 01:33:20 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*the function ft_split_env_p is used to create a list t_env 
which will be the environnement of our minishell
it takes as argument the argument from the main envp directly
and returns the first element of the list
which will contain name and value from envp[0]
(we add new element at the end of the list so we conserv the order of envp)
the function return a list that you will have 
to free before the end of your program*/

static void	ft_init_split(char **name, char **value, int *i)
{
	*name = NULL;
	*value = NULL;
	*i = -1;
}

t_env	*ft_split_env_p(char **env_p)
{
	t_env	*ret;
	char	*name;
	char	*value;
	int		i;
	int		j;

	ret = NULL;
	ft_init_split(&name, &value, &i);
	while (env_p[++i])
	{
		j = -1;
		while (env_p[i][++j] != '=')
			name = ft_realloc(&name, env_p[i][j]);
		while (env_p[i][++j])
			value = ft_realloc(&value, env_p[i][j]);
		if (name)
			ret = ft_eadd_tolist_env(ret, name, value);
		name = NULL;
		value = NULL;
	}
	return (ret);
}
