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

void	redirect_input_single(t_redirect *redirect, t_data data)
{
	data.fd0 = open(redirect->file, O_RDONLY, 0644);
	dup2(data.fd0, STDIN_FILENO);
	close(data.fd0);
	//$?
}

void	redircet_input_double(t_redirect *redir, t_data data)
{
	unlink("./temp/tmp");
	data.fd1 = open("./temp/tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (42)
	{
		if (data.idx > 0)
			dup2(data.fd_in, STDIN_FILENO);
		data.new = readline("");
		if (ft_strncmp(data.new, redir->file, ft_strlen(redir->file)) == 0
			&& ft_strncmp(data.new, redir->file, ft_strlen(data.new)) == 0)
			break ;
		ft_putendl_fd(data.new, data.fd1);
		free(data.new);
	}
	close(data.fd1);
	data.fd1 = open("./temp/tmp", O_RDONLY, 0644);
	dup2(data.fd1, STDIN_FILENO);
	close(data.fd1);
}

void	redirect_ouput_single(t_redirect *redirect, t_data data)
{
	data.fd1 = open(redirect->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(data.fd1, STDOUT_FILENO);
	close(data.fd1);
}

void	redirect_output_double(t_redirect *redirect, t_data data)
{
	data.fd1 = open(redirect->file, O_RDWR | O_CREAT | O_APPEND, 0644);
	dup2(data.fd1, STDOUT_FILENO);
	close(data.fd1);
}

int	redirect_change(t_redirect *redirect, t_env *env_lst)
{
	t_data	data;

	init_data(&data);
	while (redirect)
	{	
		if (redirect->type == REDIRECT_INPUT_SINGLE) // <
		{
			if (input_file_check(redirect, env_lst))
				return (1);
			redirect_input_single(redirect, data);
		}
		else if (redirect->type == REDIRECT_INPUT_DOUBLE) // <<
			redircet_input_double(redirect, data);
		else if (redirect->type == REDIRECT_OUTPUT_SINGLE) // >>
			redirect_ouput_single(redirect, data);
		else if (redirect->type == REDIRECT_OUTPUT_DOUBLE) // >
			redirect_output_double(redirect, data);
		++data.idx;
		redirect = redirect->next;
	}
	return (0);
}
