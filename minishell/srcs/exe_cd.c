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
		{
			ft_putstr_fd(env_lst->key, 1);
			ft_putstr_fd("\n", 1);
			return (env_lst->value);
		}
		env_lst = env_lst->next;
	}
	return (0);
}

void	exe_cd(t_cmd *cmd, t_env *env_lst)
{
	int		result;
	char	*home;
	char	*path;
	char	*joins;

	result = 0;
	home = getenv("HOME");
	path = ft_strjoin(home, "/");
	if (!cmd->argv[1])
	{
		if (!search_home(env_lst))
		{
			ft_error(0, "cd ", "HOME not set\n", 1);
			return ;
		}
		chdir(search_home(env_lst));
	}
	if (cmd->argv[1])
	{
		if (ft_strchr(cmd->argv[1], '~'))
		{
			if (ft_strlen(cmd->argv[1]) > 1)
			{
				joins = ft_strjoin(path, &cmd->argv[1][2]);
				printf("\t%s\n", joins);
				chdir(joins);
			}
			else
				chdir(home);
		}
		else
		{
			result = chdir(cmd->argv[1]);
			if (result == -1 )
				ft_error(0, "cd ", "No such file or directory\n", 1);
		}
	}
	g_exit_code = 0;
}
