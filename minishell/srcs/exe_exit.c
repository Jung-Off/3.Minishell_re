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

void	parse_error(int is_exit, int exit_code)
{
	g_exit_code = exit_code;
	if (is_exit)
		exit (g_exit_code);
}

void	ft_error(int is_exit, char *cmd, char *err_msg, int exit_code)
{
	write(1, "minishell: ", 11);
	write(1, cmd, ft_strlen(cmd));
	write(1, ":", 1);
	write(1, err_msg, ft_strlen(err_msg));
	g_exit_code = exit_code;
	if (is_exit)
		exit (g_exit_code);
}

void	exit_code_change(t_cmd *cmd)
{
	g_exit_code = ft_atoi(cmd->argv[1]);
	exit(g_exit_code % 256);
}

void	exit_utils(int exit_exe, char *err_msg, int exit_code)
{
	ft_putstr_fd("exit\n", 1);
	ft_error(exit_exe, "exit ", err_msg, exit_code);
}

void	exe_exit(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 1;
	if (cmd->argv[1] == NULL)
		exit(0);
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
				exit_utils(1, " numeric argument required\n", 255);
			++j;
		}
		++i;
	}
	exit_code_change(cmd);
}
