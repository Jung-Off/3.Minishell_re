/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jji <jji@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:50:02 by jji               #+#    #+#             */
/*   Updated: 2021/12/02 15:50:03 by jji              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_built(char *cmd)
{
	if ((ft_strncmp((cmd), "pwd", 3) == 0 && ft_strlen(cmd) == 3) \
	|| (ft_strncmp((cmd), "env", 3) == 0 && ft_strlen(cmd) == 3) \
	|| (ft_strncmp((cmd), "export", 6) == 0 && ft_strlen(cmd) == 6) \
	|| (ft_strncmp((cmd), "unset", 5) == 0 && ft_strlen(cmd) == 5) \
	|| (ft_strncmp((cmd), "cd", 2) == 0 && ft_strlen(cmd) == 2) \
	|| (ft_strncmp((cmd), "echo", 4) == 0 && ft_strlen(cmd) == 4) \
	|| (ft_strncmp((cmd), "exit", 4) == 0 && ft_strlen(cmd) == 4))
		return (1);
	return (0);
}

void	exe_builtin(t_cmd *cmd, t_env **env_lst)
{
	if (ft_strncmp((cmd->argv[0]), "pwd", 3) == 0 \
	&& ft_strlen(cmd->argv[0]) == 3)
		exe_pwd();
	else if (ft_strncmp((cmd->argv[0]), "env", 3) == 0 \
	&& ft_strlen(cmd->argv[0]) == 3)
		print_env(*env_lst, cmd);
	else if (ft_strncmp((cmd->argv[0]), "export", 6) == 0 \
	&& ft_strlen(cmd->argv[0]) == 6)
		exe_export(env_lst, cmd);
	else if (ft_strncmp((cmd->argv[0]), "unset", 5) == 0 \
	&& ft_strlen(cmd->argv[0]) == 5)
		exe_unset(env_lst, cmd);
	else if (ft_strncmp((cmd->argv[0]), "cd", 2) == 0 \
	&& ft_strlen(cmd->argv[0]) == 2)
		exe_cd(cmd, *env_lst);
	else if (ft_strncmp((cmd->argv[0]), "echo", 4) == 0 \
	&& ft_strlen(cmd->argv[0]) == 4)
		exe_echo(cmd);
	else if (ft_strncmp((cmd->argv[0]), "exit", 4) == 0 \
	&& ft_strlen(cmd->argv[0]) == 4)
		exe_exit(cmd);
}
