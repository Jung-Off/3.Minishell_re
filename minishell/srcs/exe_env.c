/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jji <jji@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 20:29:49 by jji               #+#    #+#             */
/*   Updated: 2021/11/30 20:29:50 by jji              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**find_envp_path(void)
{
	char	**envp_path;
	char	*path;

	path = getenv("PATH");
	if (path == NULL)
		printf("Failed to get path\n");
	envp_path = ft_split(path, ':');
	return (envp_path);
}

void	free_double(char **env_oneline)
{
	int	i;

	i = 0;
	while (env_oneline[i])
	{
		free(env_oneline[i]);
		++i;
	}
	free(env_oneline);
}

void	env_split(t_env *lst, char *env)
{
	char	**env_oneline;

	env_oneline = ft_split(&env[0], '=');
	lst->key = ft_strdup(env_oneline[0]);
	lst->value = ft_strdup(env_oneline[1]);
	free_double(env_oneline);
	lst->env_flag = 1;
}

void	print_env(t_env *env_lst, t_cmd *cmd)
{
	if (cmd->argv[1])
	{	
		ft_error(0, cmd->argv[0], " No such file or directory\n", 127);
		return ;
	}
	while (env_lst)
	{
		if (env_lst->env_flag)
		{
			ft_putstr_fd(env_lst->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(env_lst->value, 1);
			ft_putstr_fd("\n", 1);
		}
		env_lst = env_lst->next;
	}
	g_exit_code = 0;
}

void	make_envlst(char **envp, t_env **env_lst)
{
	t_env	*lst;

	while (*envp)
	{
		create_list(&lst);
		env_split(lst, envp[0]);
		add_node(lst, env_lst);
		++envp;
	}
}
