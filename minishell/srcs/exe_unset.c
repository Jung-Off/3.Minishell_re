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



t_env	*exe_unset(t_env **env_lst, t_cmd *cmd)
{
	t_env	*prev_env;
	t_env	*m;
	t_env	*first;
	t_env	*temp;
	int		i;

	temp = NULL;
	first = *env_lst;
	prev_env = NULL;
	i = 1;
	while (cmd->argv[i])
	{
		m = *env_lst;
		while (m)
		{	
			if (ft_strncmp(m->key, cmd->argv[i], ft_strlen(cmd->argv[i])) == 0 \
	&& ft_strncmp(m->key, cmd->argv[i], ft_strlen(m->key)) == 0)
			{
				if (prev_env == NULL)
				{
					temp = *env_lst;
					*env_lst = (*env_lst)->next;
					first = *env_lst;
					free(temp->key);
					free(temp->value);
					free(temp);
				}
				else
				{
					temp = prev_env->next;
					prev_env->next = m->next;
					free(temp->key);
					free(temp->value);
					free(temp);
				}
				break;
			}
			prev_env = m;
			m = m->next;
		}
		i++;
	}
	(*env_lst) = first;
	return (first);
}
