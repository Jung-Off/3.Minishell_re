/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jji <jji@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:16:06 by jji               #+#    #+#             */
/*   Updated: 2021/12/02 15:16:13 by jji              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_unset(t_unset *unset, t_env *env_lst)
{
	unset->temp = NULL;
	unset->m = NULL;
	unset->first = env_lst;
	unset->prev_env = NULL;
	unset->i = 1;
}

void	first_unset(t_unset *unset, t_env **env_lst)
{
	unset->temp = *env_lst;
	*env_lst = (*env_lst)->next;
	unset->first = *env_lst;
	free(unset->temp->key);
	free(unset->temp->value);
	free(unset->temp);
}

void	etc_unset(t_unset *unset)
{
	unset->temp = unset->prev_env->next;
	unset->prev_env->next = unset->m->next;
	free(unset->temp->key);
	free(unset->temp->value);
	free(unset->temp);
}

int	delete_unset(t_unset unset, t_cmd *cmd)
{
	if (ft_strncmp(unset.m->key, cmd->argv[unset.i], \
	ft_strlen(cmd->argv[unset.i])) == 0 \
	&& ft_strncmp(unset.m->key, cmd->argv[unset.i], \
	ft_strlen(unset.m->key)) == 0)
		return (1);
	return (0);
}

t_env	*exe_unset(t_env **env_lst, t_cmd *cmd)
{
	t_unset	unset;

	init_unset(&unset, *env_lst);
	while (cmd->argv[unset.i])
	{
		unset.m = *env_lst;
		while (unset.m)
		{	
			if (delete_unset(unset, cmd))
			{
				if (unset.prev_env == NULL)
					first_unset(&unset, env_lst);
				else
					etc_unset(&unset);
				break ;
			}
			unset.prev_env = unset.m;
			unset.m = unset.m->next;
		}
		unset.i++;
	}
	(*env_lst) = unset.first;
	return (unset.first);
}
