/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jji <jji@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:44:55 by jji               #+#    #+#             */
/*   Updated: 2021/12/02 15:44:56 by jji              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_process(t_cmd **cmd, char **env, t_env **env_list, t_exe exe_data)
{
	if (!(cmd_ok(env, (*cmd)->argv[0]) || is_built((*cmd)->argv[0])))
		ft_error(1, (*cmd)->argv[0], "command not found", 127);
	if ((*cmd)->redirect > 0)
	{
		if (redirect_change((*cmd)->redirect, *env_list))
			exit(0);
	}
	if (exe_data.in != 0)
	{	
		dup2(exe_data.in, 0);
		close(exe_data.in);
	}
	if (exe_data.out != 1 && (*cmd)->next != NULL)
	{
		dup2(exe_data.out, 1);
		close(exe_data.out);
	}
	if (is_built((*cmd)->argv[0]))
	{
		exe_builtin(*cmd, env_list);
		exit(g_exit_code);
	}
	else
		execve(exe_data.env_path, (*cmd)->argv, NULL);
}

void	pipe_setting(t_cmd **cmd, t_exe *exe_data)
{
	if ((*cmd)->next != NULL)
	{
		pipe((*cmd)->fd);
		exe_data->out = (*cmd)->fd[1];
	}
}

void	ready_next_process(t_cmd **cmd, t_exe *exe_data)
{
	if ((*cmd)->next != NULL)
		close(exe_data->out);
	exe_data->in = (*cmd)->fd[0];
}

void	exe_process(t_cmd **cmd, char **env, t_env **env_list)
{
	t_exe	exe_data;

	init_exe(&exe_data, *cmd);
	redirect_signal(cmd);
	while (*cmd)
	{	
		if (is_built((*cmd)->argv[0]) && exe_data.n == 1 && !(*cmd)->redirect)
			exe_builtin(*cmd, env_list);
		else
		{
			pipe_setting(cmd, &exe_data);
			exe_data.env_path = exe_parse(env, (*cmd)->argv[0]);
			exe_data.pid = fork();
			if (exe_data.pid == 0)
				child_process(cmd, env, env_list, exe_data);
			else if (exe_data.pid > 0)
			{	
				waitpid(exe_data.pid, &exe_data.status, 0);
				g_exit_code = WEXITSTATUS(exe_data.status);
			}
			ready_next_process(cmd, &exe_data);
		}
		(*cmd) = (*cmd)->next;
	}
}
