/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jji <jji@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 20:32:47 by jji               #+#    #+#             */
/*   Updated: 2021/11/30 20:32:48 by jji              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	duplicate_search(t_env *env_lst, t_env *lst)
{
	while (env_lst)
	{	
		if (ft_strlen(env_lst->key) <= ft_strlen(lst->key))
		{
			if (ft_strncmp(env_lst->key, lst->key, ft_strlen(lst->key)) == 0)
			{
				printf("key ; %s  value : %s  env_flag :%d\n", lst->key, lst->value, lst->env_flag);
				if (lst->env_flag == 0)
					return (1);
				else
				{
					env_lst->value = lst->value;
					env_lst->env_flag = 1;
					return (1);
				}
			}
		}
		else
		{
			if (ft_strncmp(lst->key, env_lst->key, ft_strlen(env_lst->key)) == 0)
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
		}
		env_lst = env_lst->next;
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

int	ft_num(t_env *env_lst, t_env *move_lst)
{
	int	i;

	i = 0;
	if (env_lst == move_lst)
		return (0);
	while (env_lst->key[i] != 0 && move_lst->key[i] != 0)
	{
		if (env_lst->key[i] > move_lst->key[i])
			return (1);
		else if (env_lst->key[i] < move_lst->key[i])
			return (0);
		++i;
	}
	if (ft_strlen(env_lst->key) > ft_strlen(move_lst->key))
		return (1);
	return (0);
}

void	sort_export(t_env *env_lst)
{
	t_env	*move_lst;
	t_env	*print_lst;
	t_env	*first_lst;

	first_lst = env_lst;
	print_lst = env_lst;
	move_lst = env_lst;
	while (env_lst)
	{
		move_lst = first_lst;
		while (move_lst)
		{
			env_lst->idx += ft_num(env_lst, move_lst);
			move_lst = move_lst->next;
		}
		env_lst = env_lst->next;
	}
}

void	print_export(t_env *env_lst)
{
	int		i;
	t_env	*print_lst;
	t_env	*first_lst;

	i = 0;
	first_lst = env_lst;
	print_lst = env_lst;
	sort_export(env_lst);
	while (env_lst)
	{
		print_lst = first_lst;
		while (print_lst)
		{
			if (print_lst->idx == i)
			{
				ft_putnbr_fd(print_lst->idx, 1);
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(print_lst->key, 1);
				if (print_lst->env_flag == 1)
				{
					ft_putstr_fd("=", 1);
					if (print_lst->value == NULL)
						ft_putstr_fd("\"\"", 1);
					ft_putstr_fd(print_lst->value, 1);
				}
				ft_putstr_fd("\n", 1);
			}
			print_lst = print_lst->next;
		}
		++i;
		env_lst = env_lst->next;
	}
	while (first_lst)
	{
		first_lst->idx = 0;
		first_lst = first_lst->next;
	}
}

void	exe_export(t_env **env_lst, t_cmd *cmd)
{
	int	i;

	i = 1;
	if (cmd->argv[1])
	{
		while (cmd->argv[i])
		{
			add_export(env_lst, cmd->argv[i]);
			++i;
		}
	}
	else
		print_export(*env_lst);
}
