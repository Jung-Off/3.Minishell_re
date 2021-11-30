/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jji <jji@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 20:28:24 by jji               #+#    #+#             */
/*   Updated: 2021/11/30 20:28:25 by jji              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	echo_option_chk(char *option)
{
	int	i;

	i = 2;
	if (option[0] == '-' && option[1] == 'n')
	{
		while (option[i])
		{
			if (option[i] != 'n')
				return (0);
			++i;
		}
		return (1);
	}
	return (0);
}

void	exe_echo(t_cmd *cmd)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	printf("%s %s\n", cmd->argv[0], cmd->argv[1]);
	if (cmd->argv[1])
		option = echo_option_chk(cmd->argv[1]);
	if (option)
		i = 2;
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], 1);
		++i;
		if (cmd->argv[i])
			ft_putstr_fd(" ", 1);
	}
	if (!option)
		ft_putstr_fd("\n", 1);
}
