/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jji <jji@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:00:58 by jji               #+#    #+#             */
/*   Updated: 2021/12/02 15:01:10 by jji              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_envlst(t_env *env_lst, t_env *lst)
{
	if (lst->env_flag == 0)
		return (1);
	else
	{
		env_lst->value = lst->value;
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
			if (ft_strncmp(lst->key, \
env_lst->key, ft_strlen(env_lst->key)) == 0)
				return (init_envlst(env_lst, lst));
		}
		env_lst = env_lst->next;
	}
	return (0);
}

void	export_split(t_env *lst, char *argv)
{
	char	**export_oneline;
	int		i;

	i = 0;
	export_oneline = ft_split(argv, '=');
	while (export_oneline[i])
	{
		printf("____%s____%d\n", export_oneline[i], i);
		++i;
	}
	lst->key = export_oneline[0];
	if (ft_strchr(argv, '='))
	{
		lst->value = export_oneline[1];
		lst->env_flag = 1;
	}
}

int	judge_cmd(char *cmd_option)
{
	int	i;
	int	judge;

	judge = 0;
	i = 0;
	while (cmd_option[i] && !judge)
	{
		if (ft_isdigit(cmd_option[i]))
		{
			ft_putchar_fd(cmd_option[i], 1);
			judge = 1;
		}
		if (ft_isalpha(cmd_option[i]))
			break ;
		++i;
	}
	return (judge);
}

int	add_export(t_env **env_lst, char *cmd)
{
	t_env	*lst;

	if (judge_cmd(cmd))
	{
		ft_putstr_fd("export :", 1);
		ft_putstr_fd(cmd, 1);
		ft_putstr_fd(": not a valid identifier", 1);
		ft_putstr_fd("\n", 1);
		return (1);
	}
	create_list(&lst);
	export_split(lst, cmd);
	if (duplicate_search(*env_lst, lst))
		return (1);
	add_node(lst, env_lst);
	return (0);
}
