/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jji <jji@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:51:17 by jji               #+#    #+#             */
/*   Updated: 2021/12/02 15:51:17 by jji              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_code_change(t_cmd *cmd)
{
	g_exit_code = ft_atoi(cmd->argv[1]);
	exit(g_exit_code % 256);
}

void	exit_utils(int exit_exe, char *err_msg, int exit_code)
{
	ft_putstr_fd("exit\n", 1);
	ft_error(exit_exe, "exit", err_msg, exit_code);
	if (exit_code == 255)
	{
		ft_putstr_fd(": numeric argument required\n", 1);
		exit(g_exit_code);
	}
}

void	just_exit(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(0);
}

void	exe_exit(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 1;
	if (cmd->argv[1] == NULL)
		just_exit();
	while (cmd->argv[i])
	{
		j = 0;
		if (i >= 2)
		{
			exit_utils(0, " too many arguments\n", 1);
			return ;
		}
		while (cmd->argv[i][j])
		{
			if (ft_isdigit(cmd->argv[i][j]) == 0)
				exit_utils(0, cmd->argv[i], 255);
			++j;
		}
		++i;
	}
	exit_code_change(cmd);
}
