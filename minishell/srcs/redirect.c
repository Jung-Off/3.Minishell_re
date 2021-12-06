/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jji <jji@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:46:07 by jji               #+#    #+#             */
/*   Updated: 2021/12/02 15:46:09 by jji              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct s_data
{
	int idx;
	char *new_input;
	int fd_in;
	int fd0;
	int fd1;
}			t_data;

void init_data(t_data *data)
{
	data->idx = 0;
	data->new_input = NULL;
	data->fd_in = dup(STDIN_FILENO);
	data->fd0 = 0;
	data->fd1 = 0;
}

void redirect_input_single(t_redirect *redirect, t_data data)
{
	data.fd0 = open(redirect->file, O_RDONLY, 0644);
	dup2(data.fd0, STDIN_FILENO);
	close(data.fd0);
	//$?
}

void redircet_input_double(t_redirect *redirect, t_data data)
{
	unlink("./temp/tmp");
	data.fd1 = open("./temp/tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (42)
	{
		if (data.idx > 0)
			dup2(data.fd_in, STDIN_FILENO);
		data.new_input = readline("");
		if (ft_strncmp(data.new_input, redirect->file, ft_strlen(redirect->file)) == 0 
			&& ft_strncmp(data.new_input, redirect->file, ft_strlen(data.new_input)) == 0)
			break ;
		ft_putendl_fd(data.new_input, data.fd1);
		free(data.new_input);
	}
	close(data.fd1);
	data.fd1 = open("./temp/tmp", O_RDONLY, 0644);
	dup2(data.fd1, STDIN_FILENO);
	close(data.fd1);
}

void redirect_ouput_single(t_redirect *redirect, t_data data)
{
	data.fd1 = open(redirect->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(data.fd1, STDOUT_FILENO);
	close(data.fd1);
}

void redirect_output_double(t_redirect *redirect, t_data data)
{
	data.fd1 = open(redirect->file, O_RDWR | O_CREAT | O_APPEND, 0644);
	dup2(data.fd1, STDOUT_FILENO);
	close(data.fd1);
}

int input_file_check(t_redirect *redirect, t_env *env_lst)
{
	struct stat	buf;
	while(env_lst)
	{
		if ((ft_strncmp(env_lst->key, "PWD", 3) && ft_strncmp("PWD", env_lst->key, 3)) == 0)
		{

			char *pwd = ft_strdup(env_lst->value);
			char *add_slash = ft_strjoin(pwd, "/");
			free(pwd);
			char *env_path = ft_strjoin(add_slash, redirect->file);
			if (stat(env_path, &buf)) //찾지 못했다.
			{
				ft_putstr_fd("minishell: ", 1);
				ft_putstr_fd(redirect->file, 1);
				ft_putstr_fd(": No such file or directory\n", 1);
				return (1);
			}
		}
		env_lst = env_lst->next;
	}
	return (0);
}

int redirect_change(t_redirect *redirect, t_env *env_lst)
{
	t_data data;

	init_data(&data);
	// int i = 0;
	// char *new_input;
	// int fd_in;
	// int fd0;
	// int fd1;
	//fd_in = dup(STDIN_FILENO);
	
	while(redirect)
	{	
		if (redirect->type == REDIRECT_INPUT_SINGLE) // <
		{
			// struct stat	buf;
			// while(env_lst)
			// {
			// 	if ((ft_strncmp(env_lst->key, "PWD", 3) && ft_strncmp("PWD", env_lst->key, 3)) == 0)
			// 	{

			// 		char *pwd = ft_strdup(env_lst->value);
			// 		char *add_slash = ft_strjoin(pwd, "/");
			// 		free(pwd);
			// 		char *env_path = ft_strjoin(add_slash, redirect->file);
			// 		if (stat(env_path, &buf)) //찾지 못했다.
			// 		{
			// 			ft_putstr_fd("minishell: ", 1);
			// 			ft_putstr_fd(redirect->file, 1);
			// 			ft_putstr_fd(": No such file or directory\n", 1);
			// 			return (1);
			// 		}
			// 	}
			// 	env_lst = env_lst->next;
			// }
			if (input_file_check(redirect, env_lst))
				return (1);
			redirect_input_single(redirect, data);
			// fd0 = open(redirect->file, O_RDONLY, 0644);
			// dup2(fd0, STDIN_FILENO);
			// close(fd0);
		}
		else if (redirect->type == REDIRECT_INPUT_DOUBLE) // <<
		{
			redircet_input_double(redirect, data);

			// unlink("./temp/tmp");
			// fd1 = open("./temp/tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
			// while (42)
			// {
			// 	if (i > 0)
			// 		dup2(fd_in, STDIN_FILENO);
			// 	new_input = readline("");
			// 	if (ft_strncmp(new_input, redirect->file, ft_strlen(redirect->file)) == 0 
			// 		&& ft_strncmp(new_input, redirect->file, ft_strlen(new_input)) == 0)
			// 		break ;
			// 	ft_putendl_fd(new_input, fd1);
			// 	free(new_input);
			// }
			// close(fd1);
			// fd1 = open("./temp/tmp", O_RDONLY, 0644);
			// dup2(fd1, STDIN_FILENO);
			// close(fd1);
		}
		else if (redirect->type == REDIRECT_OUTPUT_SINGLE) // >>
		{
			redirect_ouput_single(redirect, data);
			// fd1 = open(redirect->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			// dup2(fd1, STDOUT_FILENO);
			// close(fd1);
		}
		else if (redirect->type == REDIRECT_OUTPUT_DOUBLE) // >
		{
			redirect_output_double(redirect, data);
			// fd1 = open(redirect->file, O_RDWR | O_CREAT | O_APPEND, 0644);
			// dup2(fd1, STDOUT_FILENO);
			// close(fd1);
		}
		++data.idx;
		redirect = redirect->next;
	}
	return (0);
}
