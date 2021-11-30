/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jji <jji@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 20:37:37 by jji               #+#    #+#             */
/*   Updated: 2021/11/30 20:37:39 by jji              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_list(t_env **lst)
{
	*lst = malloc(sizeof(t_env));
	(*lst)->key = NULL;
	(*lst)->value = NULL;
	(*lst)->next = NULL;
	(*lst)->env_flag = 0;
}

void	add_node(t_env *add_lst, t_env **env_lst)
{
	t_env	*move;

	move = *env_lst;
	if (*env_lst == NULL)
		*env_lst = add_lst;
	else
	{
		while (move->next)
			move = move->next;
		move->next = add_lst;
	}
}
