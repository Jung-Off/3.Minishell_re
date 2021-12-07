/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jji <jji@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:52:23 by jji               #+#    #+#             */
/*   Updated: 2021/12/02 15:52:24 by jji              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_num(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		++i;
	}
	return (i);
}

char	*exe_parse(char **env, char *command_split)
{
	int			i;
	char		*env_path;
	char		*add_slash;
	struct stat	buf;

	i = 0;
	if (is_built(command_split))
		return (0);
	while (env[i])
	{
		env_path = ft_strdup(env[i]);
		add_slash = ft_strjoin(env_path, "/");
		free(env_path);
		env_path = ft_strjoin(add_slash, command_split);
		free(add_slash);
		if (stat(env_path, &buf) == 0)
			return (env_path);
		free(env_path);
		++i;
	}
	return (0);
}
