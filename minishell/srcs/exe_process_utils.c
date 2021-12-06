/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_process_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jji <jji@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:50:37 by jji               #+#    #+#             */
/*   Updated: 2021/12/06 19:50:38 by jji              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_exe(t_exe *exe_data, t_cmd *cmd)
{
	exe_data->pid = 0;
	exe_data->in = 0;
	exe_data->out = 1;
	exe_data->env_path = NULL;
	exe_data->status = 0;
	exe_data->n = cmd_num(cmd);
}

void	redirect_signal(t_cmd **cmd)
{
	if (!(*cmd)->redirect)
		emit_signal(N_OMIT);
}

int	cmd_ok(char **env, char *cmd)
{
	int			i;
	char		*env_path;
	char		*add_slash;
	struct stat	buf;

	i = 0;
	while (env[i])
	{
		env_path = ft_strdup(env[i]);
		add_slash = ft_strjoin(env_path, "/");
		free(env_path);
		env_path = ft_strjoin(add_slash, cmd);
		if (stat(env_path, &buf) == 0)
			return (1);
		++i;
	}
	return (0);
}
