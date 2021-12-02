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

void	exe_unset(t_env **env_lst, t_cmd *cmd)
{
	t_env	*prev_env;
	t_env	*m;
	int		i;

	prev_env = NULL;
	i = 0;
	while (cmd->argv[i])
	{
		m = *env_lst;
		while (m)
		{	
			if (ft_strncmp(m->key, cmd->argv[i], ft_strlen(cmd->argv[i])) == 0 \
	&& ft_strncmp(m->key, cmd->argv[i], ft_strlen(m->key)) == 0)
			{
				if (prev_env == NULL)
					(*env_lst) = (*env_lst)->next;
				else
					prev_env->next = m->next;
				break ;
			}
			prev_env = m;
			m = m->next;
		}
		i++;
	}
}
