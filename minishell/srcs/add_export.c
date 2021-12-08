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

void	export_put_value(char **export_oneline, t_env *lst, char *argv)
{
	lst->key = ft_strdup(export_oneline[0]);
	if (ft_strchr(argv, '='))
	{
		lst->env_flag = 1;
		if (export_oneline[1] == NULL)
		{	
			free_double(export_oneline);
			return ;
		}
		lst->value = ft_strdup(export_oneline[1]);
	}
	free_double(export_oneline);
}

int	export_split(t_env *lst, char *argv)
{
	char	**export_oneline;
	int		i;

	i = 0;
	if (ft_strncmp(argv, "=", 1) == 0)
	{	
		ft_error(0, "export: `='", "not a valid identifier\n", 1);
		return (1);
	}
	export_oneline = ft_split(argv, '=');
	export_put_value(export_oneline, lst, argv);
	return (0);
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
		ft_error(0, cmd, " not a valid identifier", 1);
		ft_putstr_fd("\n", 1);
		return (1);
	}
	create_list(&lst);
	if (export_split(lst, cmd))
	{
		free(lst);
		return (1);
	}
	if (duplicate_search(*env_lst, lst))
		return (1);
	add_node(lst, env_lst);
	return (0);
}
