/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:49:15 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/12/09 13:50:09 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	envlst_change(t_env *env_lst, t_env *lst)
{
	if (lst->value)
	{	
		if (env_lst->value == NULL)
		{
			env_lst->value = ft_strdup(lst->value);
			free(lst->value);
		}
		else
		{
			free(env_lst->value);
			env_lst->value = ft_strdup(lst->value);
			free(lst->value);
		}
	}
	else
	{
		if (env_lst->value != NULL)
		{
			free(env_lst->value);
			env_lst->value = NULL;
		}
	}
}

int	init_envlst(t_env *env_lst, t_env *lst)
{
	if (lst->env_flag == 0)
	{
		free(lst->key);
		free(lst);
		return (1);
	}
	else
	{
		free(lst->key);
		envlst_change(env_lst, lst);
		free(lst);
		env_lst->env_flag = 1;
		return (1);
	}
}

int	duplicate_search(t_env *env_lst, t_env *lst)
{
	while (env_lst)
	{	
		if (ft_strlen(env_lst->key) <= ft_strlen(lst->key))
		{
			if (ft_strncmp(env_lst->key, lst->key, ft_strlen(lst->key)) == 0)
				return (init_envlst(env_lst, lst));
		}
		else
		{
			if (ft_strncmp(lst->key, env_lst->key,
					ft_strlen(env_lst->key)) == 0)
				return (init_envlst(env_lst, lst));
		}
		env_lst = env_lst->next;
	}
	return (0);
}
