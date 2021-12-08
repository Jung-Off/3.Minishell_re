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
	char *temp;
	if (lst->env_flag == 0)
		return (1);
	else
	{
		free(lst->key);
		temp = ft_strdup(lst->value);
		free(lst->value);
		env_lst->value = temp;
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

int	export_split(t_env *lst, char *argv)
{
	char	**export_oneline;
	int		i;

	i = 0;
	if (ft_strncmp(argv, "=", 1) == 0) //=weee
	{	
		ft_error(0, "export: `='", "not a valid identifier\n", 1);
		//free(argv);
		// printf("hello\n");
		return (1);
	}
	export_oneline = ft_split(argv, '=');
	// int idx = 0;
	// printf("export cmd : %s\n", argv);
	// while(export_oneline[idx])
	// {
	// 	printf("---%s : %d\n", export_oneline[idx], i);
	// 	++idx;
	// }
	if (export_oneline == NULL || export_oneline[0] == NULL) // c = d
	{	
		ft_error(0, "export: `='", "not a valid identifier\n", 1);

		free_double(export_oneline);
		free(argv);
		return (1);
	}
	else
	{
		lst->key = ft_strdup(export_oneline[0]);
		if (ft_strchr(argv, '='))
		{
			lst->env_flag = 1;
			if (export_oneline[1] == NULL)
			{	
				free_double(export_oneline);
				printf("hello\n");
				return (0);
			}
			lst->value = ft_strdup(export_oneline[1]);
			
		}
		free_double(export_oneline);
	}
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
	{	
		free(lst);
		return (1);
	}
	add_node(lst, env_lst);
	return (0);
}
