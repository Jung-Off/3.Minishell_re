/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jji <jji@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:45:35 by jji               #+#    #+#             */
/*   Updated: 2021/12/06 11:45:36 by jji              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_data(t_data *data)
{
	data->idx = 0;
	data->new = NULL;
	data->fd_in = dup(STDIN_FILENO);
	data->fd0 = 0;
	data->fd1 = 0;
}

void	file_error(t_redirect *redirect)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(redirect->file, 1);
	ft_putstr_fd(": No such file or directory\n", 1);
}

int	input_file_check(t_redirect *redirect, t_env *env_lst)
{
	struct stat	buf;
	char		*pwd;
	char		*add_slash;
	char		*env_path;

	while (env_lst)
	{
		if ((ft_strncmp(env_lst->key, "PWD", 3) \
	&& ft_strncmp("PWD", env_lst->key, 3)) == 0)
		{
			pwd = ft_strdup(env_lst->value);
			add_slash = ft_strjoin(pwd, "/");
			free(pwd);
			env_path = ft_strjoin(add_slash, redirect->file);
			if (stat(env_path, &buf))
			{
				file_error(redirect);
				free(env_path);
				return (1);
			}
		}
		env_lst = env_lst->next;
	}
	return (0);
}
