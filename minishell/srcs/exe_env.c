/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jji <jji@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 20:29:49 by jji               #+#    #+#             */
/*   Updated: 2021/11/30 20:29:50 by jji              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_split(t_env *lst, char *env)
{
	char	**env_oneline;

	env_oneline = ft_split(&env[0], '=');
	lst->key = env_oneline[0];
	lst->value = env_oneline[1];
	lst->env_flag = 1;
}

void	exe_env(char **envp, t_env **env_lst)
{
	t_env	*lst;

	while (*envp)
	{
		create_list(&lst);
		env_split(lst, envp[0]);
		add_node(lst, env_lst);
		++envp;
	}
}

void	print_env(t_env *env_lst)
{
	while (env_lst)
	{
		if (env_lst->env_flag)
		{
			ft_putstr_fd(env_lst->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(env_lst->value, 1);
			ft_putstr_fd("\n", 1);
		}	
		env_lst = env_lst->next;
	}
}
