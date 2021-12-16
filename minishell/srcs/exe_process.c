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

void	path_find(t_cmd **cmd, char **env, t_env *env_lst)
{
	if ((*cmd)->argv[0] == NULL && (*cmd)->redirect)
		return ;
	if (*((*cmd)->argv[0]) == 0 && !(*cmd)->redirect)
		ft_error(1, (*cmd)->argv[0], "No such file or directory\n", 127);
	if (ft_strncmp((*cmd)->argv[0], "/", 1) == 0)
	{
		execve((*cmd)->argv[0], (*cmd)->argv, NULL);
		ft_error(1, (*cmd)->argv[0], "No such file or directory\n", 127);
	}
	else if (!search_path(env_lst))
		ft_error(1, (*cmd)->argv[0], "command not found\n", 127);
	else if (!(cmd_ok(env, (*cmd)->argv[0]) || is_built((*cmd)->argv[0])))
		ft_error(1, (*cmd)->argv[0], "command not found\n", 127);
}

void	child_process(t_cmd **cmd, char **env, t_env **env_list, t_exe exe_data)
{
	path_find(cmd, env, *env_list);
	if ((*cmd)->redirect > 0)
	{
		if (redirect_change((*cmd)->redirect, *env_list, *cmd))
			exit(1);
		if ((*cmd)->argv[0] == NULL)
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
		exe_builtin(*cmd, env_list, exe_data);
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

	ready_process(&exe_data, cmd);
	while (exe_data.n)
	{	
		if (is_built((*cmd)->argv[0]) && exe_data.n == 1 && !(*cmd)->redirect)
			exe_builtin(*cmd, env_list, exe_data);
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
				free(exe_data.env_path);
				g_exit_code = WEXITSTATUS(exe_data.status);
			}
			ready_next_process(cmd, &exe_data);
		}
		exe_data.n--;
		(*cmd) = (*cmd)->next;
	}
}
