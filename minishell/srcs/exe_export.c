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

int	env_rank(t_env *env_lst, t_env *move_lst)
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
			env_lst->idx += env_rank(env_lst, move_lst);
			move_lst = move_lst->next;
		}
		env_lst = env_lst->next;
	}
}

void	print_export(t_env *print_lst)
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

void	before_print_export(t_env *env_lst)
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
				print_export(print_lst);
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
			if (add_export(env_lst, cmd->argv[i]))
				break;
			++i;
		}
	}
	else
		before_print_export(*env_lst);
}
