/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/23 21:56:33 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_export_already_exist(t_env **tmp, char **name, char *value)
{
	free(*name);
	free((*tmp)->value);
	(*tmp)->value = value;
}

static void	ft_init_export(t_env **tmp, char **name, char **value, int *i)
{
	*tmp = NULL;
	*name = NULL;
	*value = NULL;
	*i = -1;
}

int	ft_export(t_env **env, char *arg)
{
	t_env	*tmp;
	char	*name;
	char	*value;
	int		i;

	if (!arg)
		return (0);
	ft_init_export(&tmp, &name, &value, &i);
	while (arg[++i] && arg[i] != '=')
		name = ft_realloc(&name, arg[i]);
	if (!arg[i])
	{
		free(name);
		return (0);
	}
	while (arg[++i])
		value = ft_realloc(&value, arg[i]);
	tmp = *env;
	while (tmp && ft_strcomp(name, tmp->name) != 0)
		tmp = tmp->nxt;
	if (!tmp)
		*env = ft_eadd_tolist_env(*env, name, value);
	else
		ft_export_already_exist(&tmp, &name, value);
	return (0);
}
