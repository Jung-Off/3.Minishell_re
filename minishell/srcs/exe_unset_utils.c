/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_unset_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jji <jji@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:37:39 by jji               #+#    #+#             */
/*   Updated: 2021/12/13 14:37:40 by jji              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset_utils(t_env **env_lst, t_cmd *cmd, t_unset unset)
{
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
}
