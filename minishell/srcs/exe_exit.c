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

int exit_function(char *line)
{
	if (ft_strncmp(line, "exit", 4) == 0 && ft_strlen(line) == 4)
	{	
		free(line);
		exit (1);
	}
	return (0);
}

void exe_exit(t_cmd *cmd)
{
	if (cmd->argv[1])
	{
		write(1, cmd->argv[1], ft_strlen(cmd->argv[1]));
		write(1, "\n", 1);
	}
}