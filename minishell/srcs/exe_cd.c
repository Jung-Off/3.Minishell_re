/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jji <jji@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 20:23:01 by jji               #+#    #+#             */
/*   Updated: 2021/11/30 20:23:02 by jji              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*search_home(t_env *env_lst)
{
	while (env_lst)
	{
		if (ft_strncmp(env_lst->key, "HOME", ft_strlen("HOME")) == 0
			&& ft_strncmp(env_lst->key, "HOME", ft_strlen(env_lst->key)) == 0)
			return (env_lst->value);
		env_lst = env_lst->next;
	}
	return (0);
}

void	exe_cd_space(t_env *env_lst, t_cd cd)
{
	if (!search_home(env_lst))
	{
		free(cd.path);
		ft_error(0, "cd ", "HOME not set\n", 1);
		return ;
	}
	chdir(search_home(env_lst));
	free(cd.path);
}

void	init_cd(t_cd *cd)
{
	char	*temp;

	cd->result = 0;
	cd->home = getenv("HOME");
	temp = ft_strdup(cd->home);
	cd->path = ft_strjoin(temp, "/");
	free(temp);
	cd->joins = NULL;
	cd->result = 0;
}

void	go_to_path(t_cmd *cmd, t_cd cd)
{
	if (ft_strlen(cmd->argv[1]) > 1)
	{
		cd.joins = ft_strjoin(cd.path, &cmd->argv[1][2]);
		free(cd.path);
		chdir(cd.joins);
		free(cd.joins);
	}
	else
	{
		chdir(cd.home);
		free(cd.path);
	}
}

void	exe_cd(t_cmd *cmd, t_env *env_lst)
{
	t_cd	cd;

	init_cd(&cd);
	if (!cmd->argv[1])
		exe_cd_space(env_lst, cd);
	if (cmd->argv[1])
	{
		if (ft_strchr(cmd->argv[1], '~'))
			go_to_path(cmd, cd);
		else
		{
			cd.result = chdir(cmd->argv[1]);
			free(cd.path);
			if (cd.result == -1 )
			{	
				ft_error(0, "cd", cmd->argv[1], 1);
				ft_putstr_fd(": No such file or directory\n", 1);
				return ;
			}
		}
	}
	g_exit_code = 0;
}
