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

void redirect_change(t_redirect *redirect)
{
	int i = 0;
	char *new_input;
	int fd_in = dup(STDIN_FILENO);
	
	while(redirect)
	{
		int fd0;
		if (redirect->type == REDIRECT_INPUT_SINGLE)
		{
			fd0 = open(redirect->file, O_RDONLY, 0644);
			dup2(fd0, STDIN_FILENO);
			close(fd0);
		}
		else if (redirect->type == REDIRECT_INPUT_DOUBLE) // <<
		{
			unlink("./temp/tmp");
			int fd1 = open("./temp/tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
			while (42)
			{
				if (i > 0)
					dup2(fd_in, STDIN_FILENO);
				new_input = readline("");
				if (ft_strncmp(new_input, redirect->file, ft_strlen(redirect->file)) == 0 
					&& ft_strncmp(new_input, redirect->file, ft_strlen(new_input)) == 0)
					break ;
				ft_putendl_fd(new_input, fd1);
				free(new_input);
			}
			close(fd1);
			fd1 = open("./temp/tmp", O_RDONLY, 0644);
			dup2(fd1, STDIN_FILENO);
			close(fd1);
		}
		else if (redirect->type == REDIRECT_OUTPUT_SINGLE)
		{
			int fd1 = open(redirect->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			dup2(fd1, STDOUT_FILENO);
			close(fd1);
		}
		else if (redirect->type == REDIRECT_OUTPUT_DOUBLE)
		{
			int fd1 = open(redirect->file, O_RDWR | O_CREAT | O_APPEND, 0644);
			dup2(fd1, STDOUT_FILENO);
			close(fd1);
		}
		++i;
		redirect = redirect->next;
	}
}
