/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/22 02:57:37 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*the function ft_get_env is used to create a list t_env 
which will be the environnement of our minishell
it takes as argument the argument from the main envp directly
and returns the first element of the list
which will contain name and value from envp[0]
(we add new element at the end of the list so we conserv the order of envp)
the function return a list that you will have 
to free before the end of your program*/

static int	ft_strcomp(char *str1, char *str2)
{
	int	i;

	if (!str1)
		return (-999);
	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

char	*ft_get_env(t_env *env, char *name)
{
	t_env	*tmp;
	char	*value;

	tmp = NULL;
	value = NULL;
	if (!env)
		return (NULL);
	tmp = env;
	if (ft_strcomp(name, tmp->name) == -999)
		return (NULL);
	while (tmp && ft_strcomp(name, tmp->name) != 0)
		tmp = tmp->nxt;
	if (!tmp)
		return (value);
	value = ft_str_copy_nofree(tmp->value);
	return (value);
}
