/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/24 02:07:34 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_unset(t_env **env, char *name)
{
	t_env	*tmp;
	int		i;

	g_exit_status = 0;
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
