/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/23 05:42:41 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*char	**ft_tenv_to_envp(t_env *env)
{
	t_env	*tmp;
	char	**ret;
	int		size;
	int		i;
	int		j;

	if (!env)
		return (NULL);
	size = ft_size_list_env(env);
	if (ft_malloc_dblchar(&ret, size + 1))
		return (NULL);
	tmp = env;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (tmp->name[++j])
			ret[i] = ft_realloc(&ret[i], tmp->name[j]);
		ret[i] = ft_realloc(&ret[i], '=');
		j = -1;
		while (tmp->value[++j])
			ret[i] = ft_realloc(&ret[i], tmp->value[j]);
		tmp = tmp->nxt;
	}
	return (ret);
}

t_env	*ft_envp_to_tenv(char **env_p)
{
	t_env	*ret;
	char	*name;
	char	*value;
	int		i;
	int		j;

	ret = NULL;
	name = NULL;
	value = NULL;
	i = -1;
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
}*/

int	ft_unset(t_env **env, char *name)
{
	t_env	*tmp;
	int		i;

	if (!*env)
		return (0);
	i = 1;
	tmp = *env;
	while (tmp && ft_strcomp(name, tmp->name) != 0)
	{
		tmp = tmp->nxt;
		i++;
	}
	if (i == 1)
	{
		*env = (*env)->nxt;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		return (0);
	}
	*env = ft_ndelete_env(*env, i);
	return (0);
}
